#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include "includes.h"

namespace po = boost::program_options;

po::variables_map parse_args(int argc, char* argv[]);

#endif