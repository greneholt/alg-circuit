//
//  load_connections.cpp
//  CircuitLayout
//
//  Created by Connor McKay on 12/5/12.
//  Copyright (c) 2012 Connor McKay. All rights reserved.
//

#include "load_connections.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

using namespace std;

matrix<int> load_connections(string filename, int &size)
{
	ifstream file(filename.c_str());
	if (file.fail()) {
		cout << "Error opening connections file: " << filename << endl;
		exit(1);
	}

	// load line count
	{
		string line;
		getline(file, line);
		stringstream stream(line);
		stream >> size;
	}

	if (size == 0) {
		cout << "Error: zero size matrix" << endl;
		exit(1);
	}

	matrix<int> connections(size, size);

	// load the connections
	for (int i = 0; i < size; i++) {
		string line;
		getline(file, line);
		stringstream stream(line);

		for (int j = 0; j < size; j++) {
			stream >> connections[i][j];
		}
	}
	
	file.close();
	
	return connections;
}