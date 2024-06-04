#pragma once

#include "Global.hpp"
#include <vector>

namespace blackjack_sim {
    class Deck {
        public:
            Deck();

            void Shuffle();
            int GetSize();
            std::vector<Card> GetCards();

        private:
            std::vector<Card> cards;
    };
}
