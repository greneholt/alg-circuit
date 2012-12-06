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
#include "anneal.h"
#include "verify.h"

namespace po = boost::program_options;

using namespace std;

int main(int argc, const char *argv[])
{
	int generate_size;
	int noise_density;
	int proximity_distance;
	long annealing_steps;
	string input_file, generate_file, solution_file;

	po::options_description desc("Allowed options");
	desc.add_options()
	("help", "print help message")
	("generate", po::value<string>(&generate_file), "generate circuit file")
	("size", po::value<int>(&generate_size), "size of circuit to generate")
	("noise", po::value<int>(&noise_density)->default_value(10), "noise density in the generated file (out of 100)")
	("distance", po::value<int>(&proximity_distance)->default_value(10), "maximum length of proximity connections in generated file")
	("anneal", po::value<string>(&input_file), "anneal specified file")
	("steps", po::value<long>(&annealing_steps)->default_value(1000), "number of annealing steps")
	("solution", po::value<string>(&solution_file), "solution specified file")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	if (vm.count("generate")) {
		make_input(generate_file, generate_size, noise_density, proximity_distance);
		return 0;
	}

	if (vm.count("anneal")) {
		anneal_file(input_file, annealing_steps);
		return 0;
	}

	if (vm.count("solution")) {
		verify_solution(input_file, solution_file);
		return 0;
	}

	return 0;
}

