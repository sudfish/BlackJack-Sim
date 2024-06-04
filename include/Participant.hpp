#pragma once

#include "Global.hpp"
#include <string>
#include <utility>
#include <vector>

namespace blackjack_sim {
    class Hand{
        public:
            Hand();

            void AddCard(Card &card);
            std::vector<Card> ClearHand();
            std::vector<Card> GetCards();
            std::string GetHandString();
            int GetSoftPoints();
            int GetHardPoints();
            bool HasBust();
            bool IsPair();
            Card Split();

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

            void CreateHand(Card &first, Card &second);
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
        private:

    };

    class Dealer : public Participant {
        public:
            Dealer();

            bool HasBust() override;
            Card GetFirstCard();

        private:

    };
}
