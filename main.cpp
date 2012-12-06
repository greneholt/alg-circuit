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
	string connections_filename, solution_filename;

	po::options_description desc("Allowed options");
	desc.add_options()
	("help", "print help message")
	("generate", "generate connections file")
	("anneal", "perform simulated annealing on the connections file and output the solution file")
	("verify", "verify the validity of the solution file for the connections file")
	
	("connections,C", po::value<string>(&connections_filename)->default_value("input.txt"), "the connections file")
	("solution,S", po::value<string>(&solution_filename)->default_value("solution.txt"), "the solution file")
	
	("size", po::value<int>(&generate_size)->default_value(100), "size of circuit to generate")
	("noise", po::value<int>(&noise_density)->default_value(10), "noise density in the generated file (out of 100)")
	("distance", po::value<int>(&proximity_distance)->default_value(10), "maximum length of proximity connections in generated file")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	if (vm.count("generate")) {
		make_input(connections_filename, generate_size, noise_density, proximity_distance);
		return 0;
	}

	if (vm.count("anneal")) {
		anneal_file(connections_filename, solution_filename);
		return 0;
	}

	if (vm.count("verify")) {
		verify_solution(connections_filename, solution_filename);
		return 0;
	}

	return 0;
}

