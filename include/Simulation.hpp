#pragma once

namespace blackjack_sim {
    class Simulation{
        public:
            Simulation();

            void Run();
        private:

            void DealCards();
            void HandlePlayerTurn();
            void HandleDealerTurn();
            void DetermineWinner();
    };
}
