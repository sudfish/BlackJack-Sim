#include "Participant.hpp"
#include "Global.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace blackjack_sim {
    Participant::Participant(){}
    
    void Participant::CreateHand(Card first, Card second){
        Hand hand; hand.AddCard(first); hand.AddCard(second);
        this->hands.push_back(hand);
    }

    std::vector<Hand> Participant::GetHands(){
        return this->hands;
    }

    // ===== Player =====
    Player::Player(){}

    void Player::AddCard(int index, Card card){
        this->hands.at(index).AddCard(card);
    }

    void Player::Split(int index){ 
        if(this->hands.at(index).IsPair()){
            Card card = this->hands.at(index).RemoveCard(1);
            Hand new_hand; new_hand.AddCard(card);
            this->hands.push_back(new_hand);
        }
    }

    bool Player::HasBust(int index){
        Hand hand = this->hands.at(index);
        return hand.GetHardPoints() > 21;
    }

    std::string Player::GetHandString(int index){
        Hand hand = this->hands.at(index); 
        std::stringstream ss;
        if(hand.IsPair()){
            Card card = hand.GetCards().at(0);
            if(card.rank == "A") ss << "A,A";
            else if (
                    card.rank == "10" ||
                    card.rank == "K" ||
                    card.rank == "Q" ||
                    card.rank == "J"
                    ){
                ss << "HARD 20";
            }
            else ss << card.rank << "," << card.rank;
            
            if(ss.str() == "5,5"){
                ss.str("");
                ss.clear();
                ss << "HARD 10";
            }
        } else if (!hand.HasAces() && hand.GetHardPoints() <= 21){
            ss << "HARD " << hand.GetHardPoints();
        } else if (hand.GetSoftPoints() <= 21 || hand.GetHardPoints() <= 21) {
            if(hand.GetSoftPoints() <= 21) ss << "SOFT " << hand.GetSoftPoints();
            else ss << "HARD " << hand.GetHardPoints();
        } 

        return ss.str();
    }

    std::vector<Card> Player::Clear(){
        std::vector<Card> cards;
        for(Hand hand : this->hands){
            std::vector<Card> temp = hand.ClearHand();
            for(Card card : temp){
                cards.push_back(card);
            }
        }
        return cards;
    }

    // ===== Dealer =====
    Dealer::Dealer(){}

    void Dealer::AddCard(Card card){
        this->hands.at(0).AddCard(card);
    }

    Card Dealer::GetFirstCard(){
        return this->hands.at(0).GetCards().at(0);
    }

    std::string Dealer::GetFirstCardString(){
        std::stringstream ss;
        Card card = this->GetFirstCard();
        if( card.rank == "K"|| card.rank == "Q" || card.rank == "J") ss << "10";
        else ss << card.rank;
        return ss.str();
    }

    bool Dealer::HasReached17(){
        Hand hand = this->hands.at(0);
        if(hand.HasAces()) return hand.GetSoftPoints() >= 17;
        return hand.GetHardPoints() >= 17;
    }

    bool Dealer::HasBust(){
        Hand hand = this->hands.at(0);
        return hand.GetHardPoints() > 21;
    }

    std::vector<Card> Dealer::Clear(){
        return this->hands.at(0).ClearHand();
    }
}
