//
//  main.cpp
//  CircuitLayout
//
//  Created by Connor McKay on 12/5/12.
//  Copyright (c) 2012 Connor McKay. All rights reserved.
//

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include "make_input.h"

namespace po = boost::program_options;

using namespace std;

int main(int argc, const char *argv[])
{
	long input_size, annealing_steps;
	string input_file, generate_file, input_type;

	po::options_description desc("Allowed options");
	desc.add_options()
	("help", "print help message")
	("generate", po::value<string>(&generate_file), "generate input file")
	("size", po::value<long>(&input_size), "size of input to generate")
	("anneal", po::value<string>(&input_file), "anneal specified file")
	("steps", po::value<long>(&annealing_steps)->default_value(1000), "number of annealing steps")
    ("input_type", po::value<string>(&input_type), "type of input to generate (random, proximity, proximity-random)")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	if (vm.count("generate")) {
        input_type_t type = RANDOM;

        if (input_type == "proximity") {
            type = PROXIMITY;
        }
        else if (input_type == "proximity-random") {
            type = PROXIMITY_RANDOM;
        }

		make_input(generate_file, input_size, type);
		return 0;
	}

	return 0;
}

