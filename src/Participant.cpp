#include "Participant.hpp"
#include <vector>

namespace blackjack_sim {
    // ===== HAND =====
    Hand::Hand(){};

    void Hand::ReceiveCard(Card &card){
        this->cards.push_back(card);
        this->CalculatePoints();
    }

    bool Hand::HasBust(){
        return this->points.first > 21 && this->points.second > 21;
    }

    std::vector<Card> Hand::GetCards(){
        return this->cards;
    }

    void Hand::CalculatePoints(){
        this->CalculateSoftPoints();
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
    Participant::Participant(){};


}
