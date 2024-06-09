#pragma once

#include "Deck.hpp"
#include "Participant.hpp"

namespace blackjack_sim {
    class Simulation{
        public:
            Simulation();

            void Run();
        private:
            Deck deck;
            Player player;
            Dealer dealer;

            void DealCards();
            void HandlePlayerTurn();
            void HandleDealerTurn();
            void DetermineWinner();

            void PrintHand(Hand hand);
    };
}
