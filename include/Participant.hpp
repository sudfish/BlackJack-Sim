#pragma once

#include "Global.hpp"
#include "Hand.hpp"
#include <string>
#include <vector>

namespace blackjack_sim {
    class Participant {
        public:
            Participant();

            void CreateHand(Card first, Card second);
            std::vector<Hand> GetHands();
            virtual std::vector<Card> Clear() = 0;

        protected:
            std::vector<Hand> hands;
    };

    class Player : public Participant {
        public:
            Player();

            void AddCard(int index, Card card);
            void Split(int index);
            bool HasBust(int index);
            std::string GetHandString(int index);
            std::vector<Card> Clear() override;

        private:

    };

    class Dealer : public Participant {
        public:
            Dealer();

            void AddCard(Card card);
            Card GetFirstCard();
            std::string GetFirstCardString();
            bool HasReached17();
            bool HasBust();
            std::vector<Card> Clear() override;

        private:

    };
}
