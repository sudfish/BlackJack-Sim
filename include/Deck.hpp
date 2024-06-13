#pragma once

#include "Global.hpp"
#include <vector>

namespace blackjack_sim {

    class Deck {
        public:
            Deck();

            Card DrawCard();
            std::vector<Card> GetCards();
            void PutCards(std::vector<Card> cards);
            void Shuffle();
            float GetDealtPercentage();

        private:
            std::vector<Card> cards;

            void Initialize();
    };
}
