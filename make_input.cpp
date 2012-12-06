#include "make_input.h"

#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "matrix.h"

using namespace std;

const int MAX_CONNECTIONS = 5;

void gen_random(matrix<int> &cost, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			cost[j][i] = (cost[i][j] += rand() % MAX_CONNECTIONS);
		}
	}
}

void gen_noise(matrix<int> &cost, int size, long noise_points)
{
	for (long i = 0; i < noise_points; i++) {
		int a = rand() % size;
		int b = rand() % size;

		if (a == b) {
			continue;
		}

		cost[b][a] = (cost[a][b] += rand() % 10);
	}
}

void gen_proximity(matrix<int> &cost, int size, int proximity_distance)
{
	if (proximity_distance > 0) {
		for (int i = 0; i < size; i++) {
			int end  = min(i + proximity_distance + 1, size);
			for (int j = max(i - proximity_distance, 0); j < end; j++) {
				if (i == j) continue;

				cost[j][i] = (cost[i][j] += rand() % MAX_CONNECTIONS);
			}
		}
	}
}

void make_input(std::string filename, int size, int noise_density, int proximity_distance)
{
	matrix<int> cost(size, size);

	srand((unsigned int)time(NULL));

	long noise_points = (long) size * size * noise_density / 2 / 100;
	gen_noise(cost, size, noise_points);
	gen_proximity(cost, size, proximity_distance);

	ofstream file(filename);
	file << size << endl;

	for (int i = 0; i < size; i++) {
		file << cost[i][0];
		for (int j = 1; j < size; j++) {
			file << " " << cost[i][j];
		}
		file << endl;
	}

	file.close();
}
