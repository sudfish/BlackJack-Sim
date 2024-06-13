#pragma once

#include "Global.hpp"

namespace blackjack_sim {
    class Hand{
        public:
            Hand();

            void AddCard(Card card);
            Card RemoveCard(int index);
            int GetSoftPoints();
            int GetHardPoints();
            bool HasAces();
            bool IsPair();
            std::vector<Card> GetCards();
            std::vector<Card> ClearHand();
            bool IsSurrendered();
            void Surrender();

        private:
            std::vector<Card> cards;
            std::pair<int, int> points = std::make_pair(0, 0);

            bool surrendered = false;

            void CalculatePoints();
            void CalculateSoftPoints();
            void CalculateHardPoints();
    };
}
