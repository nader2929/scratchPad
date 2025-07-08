#include "../include/parse_args.h"
#include "../include/includes.h"

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
            ("type_of_grid,t", po::value<std::string>()->default_value("even"), "type_of_grid")
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