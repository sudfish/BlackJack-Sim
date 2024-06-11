#include "Simulation.hpp"
#include "Global.hpp"
#include "Participant.hpp"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace blackjack_sim {
    Simulation::Simulation(){}

    void Simulation::Run(){
        system("clear");
        while(true){
            this->game_count++;
            if(this->deck.GetCards().size() < 26){
                this->deck.PutCards(this->bin);
                this->bin.clear();
                this->deck.Shuffle();
            }
            this->DealCards();
            this->HandlePlayerTurn();
            this->HandleDealerTurn();
            this->DetermineWinner();
            this->Reset();
            // std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
            this->player_hands++;
            while(!this->player.HasBust(i)){
                std::string hand_string = this->player.GetHandString(i);
                std::string instruction = DEALER_STANDS_ON_SOFT_17.at(std::make_pair(hand_string, dealer_first));
                int choice = INSTRUCTION_TO_NUMBER.at(instruction);

                switch (choice) {
                    case 1:     // Hit
                        this->player.AddCard(i, this->deck.DrawCard());
                        break;
                    case 3:     // Split
                        this->player.Split(i);
                        break;
                    case 4:     // Double
                        break;
                    case 5:     // Surrender
                        break;
                    default:
                        break;
                }

                if(choice == 2) break;
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
            if (this->player.HasBust(i)) {
                this->loss_count++;
            } else if (dealer_busted){
                this->win_count++;
            } else {
                int player_soft = this->player.GetHands().at(i).GetSoftPoints();
                int player_hard = this->player.GetHands().at(i).GetHardPoints();
                player_soft = player_soft > 21 ? 0 : player_soft;
                int player_points = std::max(player_soft, player_hard);

                if(player_points > dealer_points){
                    this->win_count++;
                } 
                else if(dealer_points > player_points){
                    this->loss_count++;
                } 
                else{
                    this->push_count++;
                } 
            }
        }
        std::cout << "Games: " << this->game_count 
            << "\tPlayer Hands: " << this->player_hands
            << "\tWon: " << this->win_count 
            << "\tLost: " << this->loss_count 
            << "\tPush: " << this->push_count << "\n";
    }

    void Simulation::Reset(){
        std::vector<Card> player_cards = this->player.Clear();
        std::vector<Card> dealer_cards = this->dealer.Clear();
        this->bin.insert(this->bin.end(), player_cards.begin(), player_cards.end());
        this->bin.insert(this->bin.end(), dealer_cards.begin(), dealer_cards.end());
    }

    std::string Simulation::PrintHand(Hand hand){
        std::stringstream ss;
        for(int i=0; i<hand.GetCards().size(); i++){
            if(i+1 == hand.GetCards().size()) ss << hand.GetCards().at(i).rank;
            else ss << hand.GetCards().at(i).rank << ",";
        }
        return ss.str();
    }
}
