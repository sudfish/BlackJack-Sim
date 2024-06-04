/*
 * BlackJack Strategy Simulator 
 * =============================
 * Highly customizable simulator that plays BlackJack according to a given
 * strategy map. For example, we are able to simulate basic strategy with 
 * this program by playing a certain number of games and following the basic
 * strategy chart. Then, the program displays the output after simulating all
 * those games.
 *
 * Created by @sudfish
 *
 * Started: 2024-06-03
 * Ended: 
*/

#include "Simulation.hpp"

int main (int argc, char *argv[]) {
    blackjack_sim::Simulation simulation;
    simulation.Run();
}
