#include "Simulation.hpp"

namespace blackjack_sim {
    Simulation::Simulation(){}

    void Simulation::Run(){
        this->DealCards(); 
    }

    void Simulation::DealCards(){
        Card player_first = this->deck.DrawCard();
        Card dealer_first = this->deck.DrawCard();
        Card player_second = this->deck.DrawCard();
        Card dealer_second = this->deck.DrawCard();
        this->player.CreateHand(player_first, player_second);
        this->dealer.CreateHand(dealer_first, dealer_second);
    }

    void Simulation::HandlePlayerTurn(){

    }

    void Simulation::HandleDealerTurn(){

    }

    void Simulation::DetermineWinner(){

    }
}
