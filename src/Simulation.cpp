#include "Simulation.hpp"
#include "Global.hpp"
#include <iostream>
#include <string>
#include <utility>

namespace blackjack_sim {
    Simulation::Simulation(){}

    void Simulation::Run(){
        this->DealCards(); 
        this->HandlePlayerTurn();
    }

    void Simulation::DealCards(){
        Hand player_hand, dealer_hand;
        player_hand.AddCard(this->deck.DrawCard());
        dealer_hand.AddCard(this->deck.DrawCard());
        player_hand.AddCard(this->deck.DrawCard());
        dealer_hand.AddCard(this->deck.DrawCard());
        this->player.AddHand(player_hand);
        this->dealer.AddHand(dealer_hand);
    }

    void Simulation::HandlePlayerTurn(){
        Card dealer_card = this->dealer.GetFirstCard();
        std::string dealer_card_value = this->dealer.GetFirstCardString();

        for (int i=0; i<this->player.GetHands().size(); i++) {
            std::cout << "\n\tHand No. " << i+1 << "\n";
            while(!this->player.GetHands().at(i).HasBust()){
                std::string hand_string = this->player.GetHands().at(i).GetHandString();
                std::cout << hand_string;
                std::cout << " ";
                std::string move_str = DEALER_STANDS_ON_SOFT_17.at(
                        std::make_pair(hand_string, dealer_card_value)
                        );
                std::cout << move_str << "\n";
                int move_int = MOVE_TO_NUMBER.at(move_str);

                switch (move_int) {
                    case 1:     // Hit
                        {
                            Card card = this->deck.DrawCard();
                            this->player.AddCardToHand(i, card);
                        }
                        break;
                    case 3:     // Split
                        {
                            this->player.SplitHand(i);
                        }
                        break;
                    case 4:     // Double
                        break;
                    default:
                        break;
                }

                if(move_int == 2) break;
            }
        } 
    }

    void Simulation::HandleDealerTurn(){

    }

    void Simulation::DetermineWinner(){

    }
}
