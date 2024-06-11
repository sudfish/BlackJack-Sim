#include "Simulation.hpp"
#include "Global.hpp"
#include "Participant.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace blackjack_sim {
    Simulation::Simulation(){}

    void Simulation::Run(){
        system("clear");
        this->DealCards();
        this->HandlePlayerTurn();
        this->HandleDealerTurn();
        this->DetermineWinner();
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
        std::cout << "Dealer First Card Value: " << dealer_first << "\n";
        for (int i=0; i<this->player.GetHands().size(); i++) {
            std::cout << "\t" << "Hand #" << i << "\n";
            while(!this->player.HasBust(i)){
                std::string hand_string = this->player.GetHandString(i);
                std::string instruction = DEALER_STANDS_ON_SOFT_17.at(std::make_pair(hand_string, dealer_first));
                int choice = INSTRUCTION_TO_NUMBER.at(instruction);
                std::cout << "Hand String: " << hand_string << "\t" 
                    << "Instruction: " << instruction << "\t" 
                    << "Choice: " << choice << "\t"
                    << "Hand: " << this->PrintHand(this->player.GetHands().at(i)) << "\n";

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
            std::cout << "\tFINAL HAND\n"
                << "Hand String: " << this->player.GetHandString(i) << "\t"
                << "Hand: " << this->PrintHand(this->player.GetHands().at(i)) << "\n";
        }
    }

    void Simulation::HandleDealerTurn(){
        while(!this->dealer.HasReached17()){
            this->dealer.AddCard(this->deck.DrawCard());
        }
    }

    void Simulation::DetermineWinner(){
        if(this->dealer.HasBust()) {
            std::cout << "Dealer busted. Player wins.\n";
            return;
        }


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
