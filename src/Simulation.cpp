#include "Simulation.hpp"
#include <iostream>

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
        std::cout << "Dealer Card: " << dealer_card.name << "\n";

        for (int i=0; i<this->player.GetHands().size(); i++) {
            std::cout << this->player.GetHands().at(i).GetHandString() << "\n"; 
        } 
    }

    void Simulation::HandleDealerTurn(){

    }

    void Simulation::DetermineWinner(){

    }
}
