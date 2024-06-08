#include "Participant.hpp"
#include "Global.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace blackjack_sim {
    // ===== HAND =====
    Hand::Hand(){};

    void Hand::AddCard(Card card){
        this->cards.push_back(card);
        this->CalculatePoints();
    }

    std::vector<Card> Hand::ClearHand(){
        std::vector<Card> vec = this->cards;
        this->cards.clear();
        this->CalculatePoints();
        return vec;
    }

    std::vector<Card> Hand::GetCards(){
        return this->cards;
    }

    std::string Hand::GetHandString(){
        std::stringstream ss;
        if(this->IsPair()){
            Card card = this->cards.at(0);
            if(card.rank == "A") ss << "A,A";
            else if (
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
        } else if (!this->HasAces() && this->GetHardPoints() <= 21){
            ss << "HARD " << this->GetHardPoints();
        } else if (!this->HasBust()) {
            if(this->GetSoftPoints() <= 21) ss << "SOFT " << this->GetSoftPoints();
            else ss << "HARD " << this->GetHardPoints();
        } else {
            ss << "BUST";
        }

        return ss.str();
    }

    bool Hand::HasBust(){
        if(!this->HasAces()) return this->GetHardPoints() > 21;
        return this->GetHardPoints() > 21 && this->GetSoftPoints() > 21;
    }

    int Hand::GetSoftPoints(){
        return this->points.first;
    }

    int Hand::GetHardPoints(){
        return this->points.second;
    }

    bool Hand::IsPair(){
        if( this->cards.size() == 2 && (
            this->cards.at(0).rank == this->cards.at(1).rank
            ||
            RANK_TO_NUMBER.at(this->cards.at(0).rank) == 
            RANK_TO_NUMBER.at(this->cards.at(1).rank))
            ){
            return true;
        }
        return false;
    }

    bool Hand::HasAces(){
        for(const auto& card : this->cards){
            if(card.rank == "A") return true;
        }
        return false;
    }

    void Hand::CalculatePoints(){
        if(this->HasAces()) this->CalculateSoftPoints();
        this->CalculateHardPoints();
    }

    void Hand::CalculateSoftPoints(){
        int soft_points = 0; int aces = 0;
        for(const auto& card : this->cards){
            if(card.rank == "A") {soft_points++; aces++;}
            else soft_points += RANK_TO_NUMBER.at(card.rank);
        }

        if(aces > 0) soft_points += 10;
        this->points.first = soft_points;
    }

    void Hand::CalculateHardPoints(){
        int hard_points = 0;
        for(const auto& card : this->cards){
            if(card.rank == "A") hard_points++;
            else hard_points += RANK_TO_NUMBER.at(card.rank);
        }

        this->points.second = hard_points;
    }

    // ===== PARTICIPANT =====
    Participant::Participant(){}

    void Participant::AddHand(Hand hand){
        this->hands.push_back(hand);
    }

    std::vector<Hand> Participant::GetHands(){
        return this->hands;
    }

    void Participant::ClearHands(){
        for(Hand hand : this->hands){
            hand.ClearHand();
        }
    }

    // ===== PLAYER =====
    Player::Player(){}

    bool Player::HasBust(){
        for(Hand hand : this->hands){
            if(!hand.HasBust()) return false;
        }
        return true;
    }


    // ===== DEALER =====
    Dealer::Dealer(){}

    Card Dealer::GetFirstCard(){
        return this->hands.front().GetCards().front();
    }

    bool Dealer::HasBust() {
        return this->hands.front().HasBust(); 
    }
}
