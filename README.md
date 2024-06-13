# Blackjack Basic Strategy Simulator ♠️  ♥️  ♣️  ♦️

Program designed to simulate a large number of blackjack games executing
perfect basic strategy. Provides users with insight of how well basic strategy 
works in the long run and how several rules can change your odds at the 
blackjack table. For example, in a blackjack table with 8 decks that get 
reshuffled once 70% of the cards have been dealt, where doubling is allowed, 
doubling after splitting is allowed, surrendering is allowed, with a bankroll
of $1,000,000 and bets of $50, after 1,000,000 games the bankroll decreases to
~$750,000, showcasing that the house edge is around 0.5. Even though the rules
of the table are favorable, one will mathematically still loose money in the 
long run.

## Requirements 
- C++ Compiler
- CMake

## Features 
- Able to simulate any number of decks.
- Able to change rules of the table.
- Able to edit/add basic strategy map directly. 

## References
- Basic strategy used: [here](https://wizardofodds.com/games/blackjack/strategy/4-decks/)
- House Edge Calculator: [here](https://www.blackjackapprenticeship.com/blackjack-calculator/)

## Instructions 
- Modify ```Global.hpp``` file with your own rules, compile, and run.

---

Feel free to use this however you like. 
- [@sudfish](https://github.com/sudfish)
