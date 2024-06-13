#include "Participant.hpp"
#include "Global.hpp"
#include <map>
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

    void Player::PlaceBet(int index, std::map<int, long long> &bank){
        this->bankroll -= PLAYER_BET_IN_CENTS;
        bank[index] += PLAYER_BET_IN_CENTS;
    }

    std::string Player::GetBankroll(){
        std::stringstream ss;
        ss << "$" << this->bankroll / 100 << "." << this->bankroll % 100;
        return ss.str();
    }

    bool Player::HasBust(int index){
        Hand hand = this->hands.at(index);
        return hand.GetHardPoints() > 21;
    }

    void Player::Surrender(int index){
        this->hands.at(index).Surrender();
    }

    std::string Player::GetHandString(int index){
        Hand hand = this->hands.at(index); 
        std::stringstream ss;
        if(hand.IsPair()){
            Card card = hand.GetCards().at(0);
            std::string rank = card.rank;
            if(rank == "A") ss << "A,A";
            else if (rank == "10" || rank == "K" || rank == "Q" || rank == "J") {
                ss << "HARD 20";
            } else if (rank == "5"){
                ss << "HARD 10";
            }
            else ss << card.rank << "," << card.rank;

        } else if (!hand.HasAces() && hand.GetHardPoints() <= 21){
            ss << "HARD " << hand.GetHardPoints();
        } else {
            int softPoints = hand.GetSoftPoints();
            int hardPoints = hand.GetHardPoints();
            if (softPoints <= 21) {
                ss << "SOFT " << softPoints;
            } else if (hardPoints <= 21) {
                ss << "HARD " << hardPoints;
            }
        } 

        return ss.str();
    }

    std::vector<Card> Player::Clear(){
        std::vector<Card> cards;
        for(Hand &hand : this->hands){
            std::vector<Card> temp = hand.ClearHand();
            for(Card card : temp){
                cards.push_back(card);
            }
        }
        this->hands.clear();
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
        std::string rank = card.rank;
        if(rank == "K"|| rank == "Q" || rank == "J") ss << "10";
        else ss << rank;
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
        std::vector<Card> vec = this->hands.at(0).ClearHand();
        this->hands.clear();
        return vec;
    }
}
