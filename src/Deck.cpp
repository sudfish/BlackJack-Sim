#include "Deck.hpp"
#include "Global.hpp"
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

namespace blackjack_sim {
    Deck::Deck(){
        this->Initialize();
        this->Shuffle();
    }


    std::vector<Card> Deck::GetCards(){
        return this->cards;
    }

    void Deck::PutCards(std::vector<Card> cards){
        for(const auto &card : cards){
            this->cards.push_back(card);
        }
    }

    void Deck::Shuffle(){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(this->cards.begin(), this->cards.end(), std::default_random_engine(seed));
    }

    Card Deck::DrawCard(){
        Card card = Card("NA", "NA");
        if(!this->cards.empty()){
           card = this->cards.front();
           this->cards.erase(this->cards.begin());
        }
        return card;
    }

    void Deck::Initialize(){
        int deck = 0; 
        while(deck != NUMBER_OF_DECKS){
            for(const auto &suit : SUITS){
                for(const auto &rank : RANKS){
                    Card new_card(suit, rank);
                    cards.push_back(new_card);
                }
            }
            deck++;
        }
    }
}
