#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

#define SIZE 100

int main() {
  int cost[SIZE][SIZE];
  ofstream file;
  srand(time(NULL));
  for(int i = 0; i < SIZE; i++) {
    for(int j = i; j < SIZE; j++) {
      if(i == j) {
        cost[i][j] = 0;
        continue;
      }
      int val = rand() % 5;
      cost[i][j] = val;
      cost[j][i] = val;
    }
  }
  file.open("input.txt");
  file << SIZE << endl;
  for(int i = 0; i < SIZE; i++) {
    file << cost[i][0];
    for(int j = 1; j < SIZE; j++) {
      file << " " << cost[i][j];
    }
    file << endl;
  }
  file.close();
}
