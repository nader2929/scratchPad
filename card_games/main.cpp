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

    
    std::cout << "\n";
}
