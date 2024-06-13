#pragma once

#include "Deck.hpp"
#include "Participant.hpp"
#include <map>
#include <string>
#include <vector>

namespace blackjack_sim {
    class Simulation{
        public:
            Simulation();

            void Run();
        private:
            std::map<int, long long> bank;
            int hands;
            int game, win, loss, push, surrender;

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
            std::string PrintGameStats();
    };
}
