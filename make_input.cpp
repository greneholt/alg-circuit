#include "make_input.h"

#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "matrix.h"

using namespace std;

const int MAX_CONNECTIONS = 5;

template < class T >
void generate_random(T &connections, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			connections[j][i] = (connections[i][j] += rand() % MAX_CONNECTIONS);
		}
	}
}

template < class T >
void generate_noise(T &connections, int size, long noise_points)
{
	for (long i = 0; i < noise_points; i++) {
		int a = rand() % size;
		int b = rand() % size;

		if (a == b) {
			continue;
		}

		connections[b][a] = (connections[a][b] += rand() % 10);
	}
}

template < class T >
void generate_proximity(T &connections, int size, int proximity_distance)
{
	if (proximity_distance > 0) {
		for (int i = 0; i < size; i++) {
			int end  = min(i + proximity_distance + 1, size);
			for (int j = max(i - proximity_distance, 0); j < end; j++) {
				if (i == j) {
					continue;
				}

				connections[j][i] = (connections[i][j] += rand() % MAX_CONNECTIONS);
			}
		}
	}
}

void make_input(std::string filename, int size, int noise_density, int proximity_distance)
{
	matrix<int> connections(size, size);

	srand((unsigned int)time(NULL));

	long noise_points = (long) size * size * noise_density / 2 / 100;
	generate_noise(connections, size, noise_points);
	generate_proximity(connections, size, proximity_distance);

	ofstream file(filename.c_str());
	file << size << endl;

	for (int i = 0; i < size; i++) {
		file << connections[i][0];
		for (int j = 1; j < size; j++) {
			file << " " << connections[i][j];
		}
		file << endl;
	}

	file.close();
}
