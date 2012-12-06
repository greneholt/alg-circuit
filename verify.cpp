#include "verify.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <cmath>
#include <string>

#include "matrix.h"
#include "load_connections.h"

using namespace std;

void verify_solution(string connections_filename, string solution_filename)
{
	ifstream solution_file(solution_filename.c_str());
	if (solution_file.fail()) {
		cout << "Error opening solution file: " << solution_filename << endl;
		exit(1);
	}

	int size;
	matrix<int> connections = load_connections(connections_filename, size);

	vector<int> solution(size);
	{
		string line;
		getline(solution_file, line);
		stringstream stream(line);
		for (int i = 0; i < size; i++) {
			stream >> solution[i];
		}
	}

	unsigned long solution_cost;
	{
		string line;
		getline(solution_file, line);
		stringstream stream(line);
		stream >> solution_cost;
	}

	solution_file.close();

	unsigned long total_cost = 0;
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			total_cost += connections[solution[i]-1][solution[j]-1] * abs(i - j);
		}
	}

	if (total_cost == solution_cost) {
		cout << "solution is valid" << endl;
	}
	else {
		cout << "solution is INVALID" << endl;
	}

	cout << "cost is: " << total_cost << endl;
}
