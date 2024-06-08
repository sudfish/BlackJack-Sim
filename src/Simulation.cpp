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
            std::string hand_string = this->player.GetHands().at(i).GetHandString();
            std::string move = DEALER_STANDS_ON_SOFT_17.at(
                std::make_pair(hand_string, dealer_card_value)
            );
        } 
    }

    void Simulation::HandleDealerTurn(){

    }

    void Simulation::DetermineWinner(){

    }
}
