#include "../include/deck.h"

std::string card_ranks[13] = {"A ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10", "J ", "Q ", "K "};
std::string card_suites[4] = {"♠", "♥", "♣", "♦"};

void generateDeck(std::string* deck, unsigned int seed){
    std::mt19937 gen;
    gen.seed(seed);
    int random_rank;
    int random_suite;
    std::string current_card = "";
    for(int x = 0; x < 13; x++){
        for(int y = 0; y < 4; y++){
            current_card = card_ranks[x] + card_suites[y];
            deck[(x*4)+y] = current_card;
        }
    }
}

void shuffleDeck(std::string* deck, unsigned int seed){
    std::mt19937 gen;
    gen.seed(seed);
    int temp_swap_index;
    std::string temp_swap;
    for (int x = 0; x < 52; x++) {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,51); // distribution in range [1, 6]

        temp_swap_index = dist6(gen);
        temp_swap = deck[temp_swap_index];
        deck[temp_swap_index] = deck[x];
        deck[x] = temp_swap; 
    }
}

void printDeck(std::string* deck, std::string type_of_grid){
    for (int x = 0; x < 52; x++) {
        if(type_of_grid == "freecell"){
            int start_x = x;
            for(x; x < start_x+8 && x < 52;){
                std::cout << "|" << deck[x] << "|";
                x++;
            }
            x--;
            std::cout << "\n";
        }
        else if(type_of_grid == "even"){
            std::cout << "|" << deck[x] << "|";
            if((x+1) % 4 == 0){
                std::cout << "\n";
            }
        }        
    }
}