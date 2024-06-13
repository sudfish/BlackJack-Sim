#include "Simulation.hpp"
#include "Global.hpp"
#include "Participant.hpp"
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace blackjack_sim {
    Simulation::Simulation()
        : hands(0), game(0), win(0), loss(0), push(0), surrender(0) {
        }

    void Simulation::Run(){
        // system("clear");
        while(this->game < GAME_COUNT){
            if(this->game % 50000 == 0) std::cout << this->PrintGameStats();
            this->game++;
            if(this->deck.GetDealtPercentage() < DECK_SHUFFLE_THRESHOLD_PERCENTAGE){
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::shuffle(this->bin.begin(), this->bin.end(), std::default_random_engine(seed));
                this->deck.PutCards(this->bin);
                this->bin.clear();
                this->deck.Shuffle();
            }
            this->DealCards();
            this->HandlePlayerTurn();
            this->HandleDealerTurn();
            this->DetermineWinner();
            this->Reset();
        }
    }

    void Simulation::DealCards(){
        Card dealer_first = this->deck.DrawCard();
        Card player_first = this->deck.DrawCard();
        Card dealer_second = this->deck.DrawCard();
        Card player_second = this->deck.DrawCard();
        this->dealer.CreateHand(dealer_first, dealer_second);
        this->player.CreateHand(player_first, player_second);
    }

    void Simulation::HandlePlayerTurn(){
        std::string dealer_first = this->dealer.GetFirstCardString();
        for (int i=0; i<this->player.GetHands().size(); i++) {
            this->player.PlaceBet(i, this->bank);
            this->hands++;
            while(!this->player.HasBust(i)){
                std::string hand_string = this->player.GetHandString(i);
                std::string instruction = DEALER_STANDS_ON_SOFT_17.at(std::make_pair(hand_string, dealer_first));
                int choice = INSTRUCTION_TO_NUMBER.at(instruction);

                switch (choice) {
                    case 1:     // Hit
                        this->player.AddCard(i, this->deck.DrawCard());
                        break;
                    case 3:     // Split
                        if(this->player.GetHands().size() <= 4){
                            this->player.Split(i);
                        } else choice = 2;
                        break;
                    case 4:     // Double
                        if(this->player.GetHands().size() == 1){
                            this->player.PlaceBet(i, this->bank);
                            this->player.AddCard(i, this->deck.DrawCard());
                            choice = 2;
                        } else {
                            this->player.AddCard(i, this->deck.DrawCard());
                        }
                        break;
                    case 5:     // Surrender
                        if(this->player.GetHands().size()==1){
                            this->player.Surrender(i);
                            choice = 2;
                        } else {
                            this->player.AddCard(i, this->deck.DrawCard());
                        }
                        break;
                    default:
                        break;
                }

                if(choice == 2) break;  // Stand
            }
        }
    }

    void Simulation::HandleDealerTurn(){
        while(!this->dealer.HasReached17()){
            this->dealer.AddCard(this->deck.DrawCard());
        }
    }

    void Simulation::DetermineWinner(){
        int dealer_soft = this->dealer.GetHands().at(0).GetSoftPoints();
        int dealer_hard = this->dealer.GetHands().at(0).GetHardPoints();
        dealer_soft = dealer_soft > 21 ? 0 : dealer_soft;
        int dealer_points = std::max(dealer_soft, dealer_hard);
        bool dealer_busted = this->dealer.HasBust();
        for(int i=0; i<this->player.GetHands().size(); i++){
            if(this->player.GetHands().at(i).IsSurrendered()){
                this->surrender++;
                this->player.bankroll += this->bank[i] / 2.3;
            }
            else if (this->player.HasBust(i)) {
                this->loss++;
            } else if (dealer_busted){
                this->win++;
                this->player.bankroll += this->bank[i] * 2;
            } else {
                int player_soft = this->player.GetHands().at(i).GetSoftPoints();
                int player_hard = this->player.GetHands().at(i).GetHardPoints();
                player_soft = player_soft > 21 ? 0 : player_soft;
                int player_points = std::max(player_soft, player_hard);

                if(player_points > dealer_points){
                    this->win++;
                    this->player.bankroll += this->bank[i] * 2;
                } 
                else if(dealer_points > player_points){
                    this->loss++;
                } 
                else{
                    this->push++;
                    this->player.bankroll += this->bank[i];
                } 
            }
        }
    }

    void Simulation::Reset(){
        std::vector<Card> player_cards = this->player.Clear();
        std::vector<Card> dealer_cards = this->dealer.Clear();
        this->bin.insert(this->bin.end(), player_cards.begin(), player_cards.end());
        this->bin.insert(this->bin.end(), dealer_cards.begin(), dealer_cards.end());
        this->bank[0] = 0;
        this->bank[1] = 0;
        this->bank[2] = 0;
        this->bank[3] = 0;
    }

    std::string Simulation::PrintHand(Hand hand){
        std::stringstream ss;
        for(int i=0; i<hand.GetCards().size(); i++){
            if(i+1 == hand.GetCards().size()) ss << hand.GetCards().at(i).rank;
            else ss << hand.GetCards().at(i).rank << ",";
        }
        return ss.str();
    }
    
    std::string Simulation::PrintGameStats(){
       std::stringstream ss;
       ss << "Game #" << this->game 
           << "\tPlayer Hands: " << this->hands
           << "\tWon: " << this->win 
           << "\tLost: " << this->loss 
           << "\tPush: " << this->push
           << "\tSurrendered: " << this->surrender
           << "\tBankroll: " << this->player.GetBankroll() 
           << "\n";
        return ss.str();
    }
}
