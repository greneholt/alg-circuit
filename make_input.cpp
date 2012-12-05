#include "make_input.h"

#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

void make_input(string filename, long size) {
  int cost[size][size];
    
  srand(time(NULL));

  for(int i = 0; i < size; i++) {
    for(int j = i; j < size; j++) {
      if(i == j) {
        cost[i][j] = 0;
        continue;
      }
      int val = rand() % 5;
      cost[i][j] = val;
      cost[j][i] = val;
    }
  }
    
  ofstream file(filename);
  file << size << endl;
  for(int i = 0; i < size; i++) {
    file << cost[i][0];
    for(int j = 1; j < size; j++) {
      file << " " << cost[i][j];
    }
    file << endl;
  }
  file.close();
}
