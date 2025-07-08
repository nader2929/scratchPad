#ifndef DECK_H
#define DECK_H

#include "includes.h"

void generateDeck(std::string* deck, unsigned int seed);
void shuffleDeck(std::string* deck, unsigned int seed);
void printDeck(std::string* deck, std::string type_of_grid);

#endif