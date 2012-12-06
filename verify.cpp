#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <cmath>
#include <string>

#include "matrix.h"

using namespace std;

void verify_solution(string cost_matrix, string solution_file) {
	ifstream cost(cost_matrix);
	if (cost.fail()) {
		cout << "Error opening cost matrix file" << endl;
		return;
	}
	ifstream solution(solution_file);
	if (solution.fail()) {
		cout << "Error opening solution file" << endl;
		return;
	}
	int size;
	{
		string line;
		getline(cost, line);
		stringstream stream(line);
		stream >> size;
	}

	int *sol = new int[size];

	{
		string line;
		getline(solution, line);
		stringstream stream(line);
		for (int i = 0; i < size; i++) {
			stream >> sol[i];
		}
	}

	matrix<int> connections(size, size);

	for (int i = 0; i < size; i++) {
		string line;
		getline(cost, line);
		stringstream stream(line);

		for (int j = 0; j < size; j++) {
			stream >> connections[i][j];
		}
	}

	cost.close();
	solution.close();
	long long total_cost = 0;
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			total_cost += connections[sol[i]][sol[j]] * abs(i-j);
		}
	}
	cout << "cost is: " << cost << endl;
}
