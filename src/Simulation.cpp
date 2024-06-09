#include "Simulation.hpp"
#include "Global.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace blackjack_sim {
    Simulation::Simulation(){}

    void Simulation::Run(){
        this->DealCards(); 
        this->HandlePlayerTurn();
        this->HandleDealerTurn();
        this->DetermineWinner();
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
                std::cout << "\n";
                this->PrintHand(this->player.GetHands().at(i));
                std::string hand_string = this->player.GetHands().at(i).GetHandString();
                std::string move_str = DEALER_STANDS_ON_SOFT_17.at(
                        std::make_pair(hand_string, dealer_card_value)
                        );
                int move_int = MOVE_TO_NUMBER.at(move_str);

                switch (move_int) {
                    case 1:     // Hit
                        {
                            std::cout << "\tPlayer hits. \n";
                            Card card = this->deck.DrawCard();
                            this->player.AddCardToHand(i, card);
                        }
                        break;
                    case 3:     // Split
                        {
                            std::cout << "\tPlayer splits. \n";
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
        // Dealer stands on soft 17
        std::cout << "=== Dealer Turn ===\n";
        this->PrintHand(this->dealer.GetHands().at(0));

        while(this->dealer.GetPoints() < 17){
            Card card = this->deck.DrawCard();
            this->dealer.AddCardToHand(0, card);
            this->PrintHand(this->dealer.GetHands().at(0));
        }
    }

    void Simulation::DetermineWinner(){
        int dealer_points = this->dealer.GetPoints();

        if(dealer_points > 21) {std::cout << "Dealer busted. Player wins.\n"; return;}
        
        for (int i; i<this->player.GetHands().size(); i++) {
            std::cout << "\n\tHand No. " << i+1 << "\n";
            if(this->player.GetHands().at(i).HasBust()) std::cout << "Player Busted. Dealer Wins\n";
            else{
                Hand player_hand = this->player.GetHands().at(i);
                int player_soft = player_hand.GetSoftPoints() > 21 ? 0 : player_hand.GetSoftPoints();
                int player_hard = player_hand.GetHardPoints() > 21 ? 0 : player_hand.GetHardPoints();
                int player_best = player_soft > player_hard ? player_soft : player_hard;
                if(dealer_points > player_best) std::cout << "Dealer has more points. Dealer wins.\n";
                else if(dealer_points < player_best) std::cout  << "Player has more points. Player wins.\n";
                else std::cout << "Same amount of points. Nobody wins.\n";
            }
        }
    }

    void Simulation::PrintHand(Hand hand){
        std::vector<Card> cards = hand.GetCards();
        for(const auto& card : cards){
            std::cout << card.name << "\n";
        }
        std::cout << "Soft Points: " << hand.GetSoftPoints() << "\n";
        std::cout << "Hard Points: " << hand.GetHardPoints() << "\n";
    }
}
