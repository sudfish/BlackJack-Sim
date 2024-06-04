#pragma once

#include <map>
#include <string>
#include <vector>

const int NUMBER_OF_DECKS = 1;

const std::vector<std::string> SUITS = {
    "Hearts", "Diamonds", "Clubs", "Spades"
};

const std::vector<std::string> RANKS = {
    "2", "3", "4", "5", "6", "7", "8", "9", "10",
    "J", "Q", "K", "A"
};

const std::map<std::string, int> RANK_TO_NUMBER = {
    {"2", 2}, 
    {"3", 3}, 
    {"4", 4}, 
    {"5", 5}, 
    {"6", 6}, 
    {"7", 7}, 
    {"8", 8}, 
    {"9", 9}, 
    {"10", 10}, 
    {"J", 10}, 
    {"Q", 10}, 
    {"K", 10} 
};

struct Card{
    std::string suit;
    std::string rank; 
    std::string name;

    Card(std::string suit, std::string rank) : suit(suit), rank(rank) {
        this->name = this->rank + " of " + this->suit;
    }
};
