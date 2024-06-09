#pragma once

#include "Global.hpp"
#include <string>
#include <utility>
#include <vector>

namespace blackjack_sim {
    class Hand{
        public:
            Hand();

            void AddCard(Card card);
            std::vector<Card> ClearHand();
            std::vector<Card> GetCards();
            std::string GetHandString();
            Card Split();
            int GetSoftPoints();
            int GetHardPoints();
            bool HasBust();
            bool IsPair();

        private:
            std::vector<Card> cards;
            std::pair<int, int> points = std::make_pair(0, 0);

            bool HasAces();
            void CalculatePoints();
            void CalculateSoftPoints();
            void CalculateHardPoints();
    };

    class Participant {
        public:
            Participant();

            void AddHand(Hand hand);
            void AddCardToHand(int hand_index, Card card);
            virtual bool HasBust() = 0;
            std::vector<Hand> GetHands();
            void ClearHands();

        protected:
            std::vector<Hand> hands;
    };

    class Player : public Participant {
        public:
            Player();

            bool HasBust() override;
            void SplitHand(int hand_index);
        private:

    };

    class Dealer : public Participant {
        public:
            Dealer();

            bool HasBust() override;
            int GetPoints();
            Card GetFirstCard();
            std::string GetFirstCardString();

        private:

    };
}
