#include "anneal.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <cmath>
#include "time.h"

#include "matrix.h"

using namespace std;

const double INITIAL_TEMPERATURE = 1;
const bool TRACE_OUTPUT = false;
const int COOLING_STEPS = 500;
const double COOLING_FRACTION = 0.97;
const int STEPS_PER_TEMP = 1000;
const double K = 0.1;

/*
 The solution vector stores the position of each element. So solution[i] is where the ith circuit
 element should be in the circuit.
 */

template < class T, class S >
long long swap(T &connections, int size, S &solution, int i1, int i2)
{
	long long delta = 0;

	int a = solution[i1]; // original position of i1 in the circuit
	int b = solution[i2]; // original position of i2 in the circuit

	// perform the swap
	solution[i1] = b;
	solution[i2] = a;

	// we need a to be before b in the circuit
	if (a > b) {
		int t = b;
		b = a;
		a = t;

		// swap the indices to match
		int ti = i2;
		i2 = i1;
		i1 = ti;
	}

	/*
	 There are three separate sets of connections that need to be considered:

	 1. Before a (a will get farther away, b will get closer)
	 2. Between a and b (the distance change needs to be calculated, it could be closer or farther)
	 3. After b (a will get closer, b will get farther away)
	 */

	int sep = b - a;

	for (int i = 0; i < size; i++) {
		// i1 and i2 stay at the same distance from each other, so skip them
		if (i == i1 || i == i2) {
			continue;
		}

		int pos = solution[i];

		// if its before a, i1 will get farther away and i2 will get closer
		if (pos < a) {
			delta += sep * connections[i][i1];
			delta -= sep * connections[i][i2];
		}
		// if its after b, i1 will get closer and i2 will get farther away
		else if (pos > b) {
			delta -= sep * connections[i][i1];
			delta += sep * connections[i][i2];
		}
		// if its between them, we need to calculate the change in distance as it could be closer or farther
		else {
			int dist_change = (b - pos) - (pos - a); // the amount the distance changes for i1
			// If its positive, i1 got farther away and i2 got closer.
			delta += dist_change * connections[i][i1];
			delta -= dist_change * connections[i][i2];
		}
	}

	return delta;
}

template < class T, class S >
void initialize_solution(T &connections, int size, S &solution, long long &cost)
{
	// initialize the solution so that the ith circuit element is in the ith position
	for (int i = 0; i < size; i++) {
		solution[i] = i;
		for (int j = i + 1; j < size; j++) {
			if (j == i) {
				continue;
			}

			cost += abs(i - j) * connections[i][j];
		}
	}
}

template < class T, class S >
void anneal(T &connections, int size, S &solution, long long &cost)
{
	srand((unsigned int)time(NULL));

	double temperature = INITIAL_TEMPERATURE; // the current system temp

	for (int i = 1; i <= COOLING_STEPS; i++) {
		long long before_cost = cost; // value at start of loop

		for (int j = 1; j <= STEPS_PER_TEMP; j++) {
			int i1, i2;
			// pick indices of elements to swap
			do {
				i1 = rand() % size;
				i2 = rand() % size;
			}
			while (i1 == i2);

			// calculate the cost of the change
			long long delta = swap(connections, size, solution, i1, i2);

			double flip = (double)rand() / RAND_MAX;
			double merit = exp(-delta / (K * cost * temperature));

			// printf("merit = %f  flip=%f  exponent=%f\n",merit,flip,exponent);
			// if (merit >= 1.0)
			// merit = 0.0; // don't do unchanging swaps

			if (delta == 0) {
				continue;
			}
			else if (delta < 0) { // automatically accept a lower cost
				cost += delta;

				if (TRACE_OUTPUT) {
					cout << "swap win: " << i1 << "-" << i2 << " delta=" << delta << " cost=" << cost << " temp=" << temperature << " coolstep=" << i << " step=" << j << endl;
				}
			}
			else if (merit > flip) { // accept a loss if the the random number generator says so
				cost += delta;

				if (TRACE_OUTPUT) {
					cout << "swap loss: " << i1 << "-" << i2 << " delta=" << delta << " cost=" << cost << " temp=" << temperature << " coolstep=" << i << " step=" << j << endl;
				}
			}
			else { // revert the swap
				swap(connections, size, solution, i1, i2);
			}
		}

		// if the cost isn't going down, lower the temperature
		if ((cost - before_cost) >= 0) {
			temperature *= COOLING_FRACTION;

			if (TRACE_OUTPUT) {
				cout << "reduce temperature to " << temperature << endl;
			}
		}
	}
}

void anneal_file(string filename, long steps)
{
	ifstream input(filename);
	if (input.fail()) {
		cout << "Error opening file" << endl;
		return;
	}

	int size;

	// load line count
	{
		string line;
		getline(input, line);
		stringstream stream(line);
		stream >> size;
	}

	matrix<int> connections(size, size);

	// load the connections
	for (int i = 0; i < size; i++) {
		string line;
		getline(input, line);
		stringstream stream(line);

		for (int j = 0; j < size; j++) {
			stream >> connections[i][j];
		}
	}

	vector<int> solution(size);

	long long cost;

	initialize_solution(connections, size, solution, cost);

	anneal(connections, size, solution, cost);

	vector<int> order(size);

	for (int i = 0; i < size; i++) {
		order[solution[i]] = i + 1;
	}

	cout << order[0];
	for (int i = 1; i < size; i++) {
		cout << " " << order[i];
	}
	cout << endl;

	cout << cost << endl;
}