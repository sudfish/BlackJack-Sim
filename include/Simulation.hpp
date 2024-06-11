#pragma once

#include "Deck.hpp"
#include "Participant.hpp"
#include <vector>

namespace blackjack_sim {
    class Simulation{
        public:
            Simulation();

            void Run();
        private:
            int game_count = 0;
            int win_count = 0; 
            int loss_count = 0; 
            int push_count = 0; 
            int player_hands = 0;
            Deck deck;
            std::vector<Card> bin;
            Player player;
            Dealer dealer;

            void DealCards();
            void HandlePlayerTurn();
            void HandleDealerTurn();
            void DetermineWinner();
            void Reset();

            std::string PrintHand(Hand hand);
    };
}
