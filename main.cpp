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

//#include "make_input.h"

namespace po = boost::program_options;

using namespace std;

int main(int argc, const char * argv[])
{
    long input_size, annealing_steps;
    string input_file, generate_file;
    
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "print help message")
        ("generate", po::value<string>(&generate_file), "generate input file")
        ("size", po::value<long>(&input_size), "size of input to generate")
        ("anneal", po::value<string>(&input_file), "anneal specified file")
        ("steps", po::value<long>(&annealing_steps), "number of annealing steps")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    
    if (vm.count("generate")) {
        //make_input(generate_file, input_size);
        return 0;
    }
    
    return 0;
}

