#pragma once

#include "Global.hpp"
#include <utility>
#include <vector>

namespace blackjack_sim {
    class Hand{
        public:
            Hand();

            void ReceiveCard(Card &card);
            bool HasBust();
            std::vector<Card> GetCards();

        private:
            std::vector<Card> cards;
            std::pair<int, int> points = std::make_pair(0, 0);

            void CalculatePoints();
            void CalculateSoftPoints();
            void CalculateHardPoints();
    };

    class Participant {
        public:
            Participant();

            void Hit();
            void Stand();
            virtual bool HasBust() = 0;

        protected:
            std::vector<Hand> hands;
    };

    class Player : public Participant {
        public:
            Player();

            void Split(Hand &hand);

        private:

    };

    class Dealer : public Participant {
        public:
            Dealer();

        private:

    };
}
