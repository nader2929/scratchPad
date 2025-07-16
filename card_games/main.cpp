#include "include/deck.h"
#include "include/parse_args.h"
#include "include/includes.h"

int main(int argc, char* argv[]) {
    po::variables_map parsed_args = parse_args(argc, argv);
    unsigned int seed = parsed_args["seed"].as<unsigned int>();

    std::string deck[52];
    
    generateDeck(deck, seed);
    shuffleDeck(deck, seed);
    printDeck(deck, parsed_args["type_of_grid"].as<std::string>());

    std::vector<std::vector<std::string>> freecell_grid(
        8,
        std::vector<std::string>(0));


    int freecell_column = 0;
    for (int x = 0; x < 52; x++) {
        int start_x = x;
        for(x; x < start_x+8 && x < 52;){
            freecell_grid[freecell_column].push_back(deck[x]);
            x++;
        }
        freecell_column++;
        x--;
    }

    for(std::vector<std::string> column : freecell_grid){
        for(std::string val : column){
            std::cout << "|" << val << "|";
        }
        std::cout << "\n";
    }

    
    std::cout << "\n";
}
