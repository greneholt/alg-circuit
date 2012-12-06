//
//  load_connections.h
//  CircuitLayout
//
//  Created by Connor McKay on 12/5/12.
//  Copyright (c) 2012 Connor McKay. All rights reserved.
//

#ifndef __CircuitLayout__load_connections__
#define __CircuitLayout__load_connections__

#include <string>

#include "matrix.h"

matrix<int> load_connections(std::string filename, int &size);

#endif /* defined(__CircuitLayout__load_connections__) */
