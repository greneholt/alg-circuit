//
//  make_input.h
//  CircuitLayout
//
//  Created by Connor McKay on 12/5/12.
//  Copyright (c) 2012 Connor McKay. All rights reserved.
//

#ifndef CircuitLayout_make_input_h
#define CircuitLayout_make_input_h

#include <string>

enum strategy_t { RANDOM, PROXIMITY, PROXIMITY_RANDOM };

void make_input(std::string filename, long size, strategy_t strategy);

#endif
