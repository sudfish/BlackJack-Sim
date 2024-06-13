#include "Deck.hpp"
#include "Global.hpp"
#include <algorithm>
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
        std::mt19937 rng(std::random_device{}());
        int n = this->cards.size();

        for (int i = n - 1; i > 0; --i) {
            std::uniform_int_distribution<int> uni(0, i);
            int j = uni(rng);
            std::swap(this->cards[i], this->cards[j]);
        }
    }

    Card Deck::DrawCard(){
        Card card = Card("NA", "NA");
        if(!this->cards.empty()){
           card = this->cards.front();
           this->cards.erase(this->cards.begin());
        }
        return card;
    }

    float Deck::GetDealtPercentage(){
        int total_cards = NUMBER_OF_DECKS * 52;
        int cards_in_deck = this->GetCards().size();
        return (static_cast<float>((total_cards - cards_in_deck) / total_cards) * 100.0f);
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
