#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <random>
#include <unordered_set>

namespace po = boost::program_options;

po::variables_map parse_args(int argc, char* argv[]){
    po::variables_map vm;
    try {
        // Declare a group of options that will be allowed only on the command line
        po::options_description generic("Generic options");
        generic.add_options()
            ("help,h", "produce help message")
            ("version,v", "print version string");

        // Declare a group of options that will be allowed both on the command line and in a config file
        po::options_description config("Configuration");
        config.add_options()
            ("seed,s", po::value<unsigned int>()->default_value(0), "seed");

        // Combine all the above options into one option set
        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config);

        po::options_description visible("Allowed options");
        visible.add(generic).add(config);

        po::store(po::command_line_parser(argc, argv).
                  options(cmdline_options).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << visible << "\n";
            return vm;
        }

        if (vm.count("version")) {
            std::cout << "My Program, version 1.0\n";
            return vm;
        }

        if (vm.count("seed")) {
            std::cout << "Seed is set to: "
                      << vm["seed"].as<unsigned int>() << "\n";
        } else {
            std::cout << "Seed was not set.\n";
        }

    } catch(std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return vm;
    } catch(...) {
        std::cerr << "Unknown error!\n";
        return vm;
    }

    return vm;
}


std::string card_ranks[13] = {"A ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10", "J ", "Q ", "K "};
std::string card_suites[4] = {"♠", "♥", "♣", "♦"};
std::mt19937 gen;

void generateDeck(std::string* deck){
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

void shuffleDeck(std::string* deck){
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
        std::cout << "|" << deck[x] << "|";
        if(type_of_grid == "freecell"){
            if((x+1 <= 28 && (x+1) % 7 == 0) || (x+1 > 28 && (((x+1)%29)+1) % 6 == 0)){
                std::cout << "\n";
            }
        }
        else if(type_of_grid == "even"){
            if((x+1) % 4 == 0){
                std::cout << "\n";
            }
        }        
    }
}

int main(int argc, char* argv[]) {
    po::variables_map parsed_args = parse_args(argc, argv);
    unsigned int seed = parsed_args["seed"].as<unsigned int>();
    gen.seed(seed);

    std::string deck[52];
    
    generateDeck(deck);
    shuffleDeck(deck);
    printDeck(deck, "even");

    
    std::cout << "\n";
}
