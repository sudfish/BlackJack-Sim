#include "Hand.hpp"

namespace blackjack_sim {
    Hand::Hand(){};

    void Hand::AddCard(Card card){
        this->cards.push_back(card);
        this->CalculatePoints();
    }

    Card Hand::RemoveCard(int index){
        Card card = this->cards.at(index);
        this->cards.erase(this->cards.begin()+index);
        this->CalculatePoints();
        return card;
    }

    int Hand::GetSoftPoints(){
        return this->points.first;
    }

    int Hand::GetHardPoints(){
        return this->points.second;
    }

    bool Hand::HasAces(){
        for(const auto& card : this->cards){
            if(card.rank == "A") return true;
        }
        return false;
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

    std::vector<Card> Hand::GetCards(){
        return this->cards;
    }

    std::vector<Card> Hand::ClearHand(){
        std::vector<Card> vec = this->cards;
        this->cards.clear();
        this->points.first = 0;
        this->points.second = 0;
        return vec;
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
}
