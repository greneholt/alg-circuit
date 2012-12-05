#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include "time.h"
using namespace std;

#define INITIAL_TEMPERATURE 1
#define TRACE_OUTPUT        0
#define COOLING_STEPS       500
#define COOLING_FRACTION    0.97
#define STEPS_PER_TEMP      10000
#define E                   2.718
#define K                   0.01

int solution_count = 0;                     /* how many solutions evaluated */
int** cost_matrix;

//seems this could be improved such that when we do a swap we only
//recalculate cost for the portions which have actually changed,
//so only the chips which swapped, and the chips connected to those
//chips, just doing it quick and dirty for a first pass
double solution_cost(int* input, int size) {
  int i, j;
  double totalCost = 0;
  for (i = 0, j = 1; i < size && j < size; j++) {
    totalCost += cost_matrix[i][j] * abs(input[i]-input[j]);
    if (j == size-1) {
      i++;
      j=i;
    }
  }
  return totalCost;
}


void solution_count_update(int* input, int size)
{
        solution_count = solution_count+1;
        if ((solution_count % 10000) == 0) {
                printf("%d %7.1f\n",solution_count,solution_cost(input, size));
                for(int i = 0; i < size; i++) {
                       printf(" %d=%d", i, input[i]);
                }
                printf("\n");
        }
}

void swap(int* input, int x, int y) {
  int temp;
  temp = input[x];
  input[x] = input[y];
  input[y] = temp;
}

void anneal(int* input, int size)
{
	int i1, i2;                 /* pair of items to swap */
	int i,j;                    /* counters */
	double temperature;         /* the current system temp */
	double current_value;       /* value of current state */
	double start_value;         /* value at start of loop */
	double delta;               /* value after swap */
	double merit, flip;         /* hold swap accept conditions*/
	double exponent;            /* exponent for energy funct*/

        srand(time(NULL));

	temperature = INITIAL_TEMPERATURE;

	current_value = solution_cost(input, size);

	for (i=1; i<=COOLING_STEPS; i++) {
		temperature *= COOLING_FRACTION;

		start_value = current_value;		
		
		for (j=1; j<=STEPS_PER_TEMP; j++) {

		   /* pick indices of elements to swap */
		   i1 = rand() % size;
                   i2 = rand() % size;

                   swap(input, i1, i2);
		   delta = solution_cost(input, size) - current_value;

		   flip = ((double)rand())/((double)RAND_MAX);
		   exponent = (-delta/current_value)/(K*temperature);
		   merit = pow(E,exponent);
/*printf("merit = %f  flip=%f  exponent=%f\n",merit,flip,exponent); */
		   /*if (merit >= 1.0)
			merit = 0.0;*/ /* don't do unchanging swaps*/

		   if (delta < 0) {	/*ACCEPT-WIN*/
			current_value = current_value+delta;

		     if (TRACE_OUTPUT) {
			   printf("swap WIN %d--%d value %f  temp=%f i=%d j=%d\n",
			       i1,i2,current_value,temperature,i,j);
		     }
		   } else { if (merit > flip) { 		/*ACCEPT-LOSS*/
			current_value = current_value+delta;
			if (TRACE_OUTPUT) {
				printf("swap LOSS %d--%d value %f merit=%f flip=%f i=%d j=%d\n",
				i1,i2,current_value,merit,flip,i,j);
			}
		   } else { 				/* REJECT */
			 swap(input, i1,i2);
		   } }
		   solution_count_update(input, size);
		}
		if ((current_value-start_value) < 0.0){ /* rerun at this temp */
			temperature /= COOLING_FRACTION;
			if (TRACE_OUTPUT) printf("rerun at temperature %f\n",temperature);
		}
	}
}

int main(int argc, char** argv) {
  char line[1024];
  ifstream input;
  int chips;
  int* order;
  if(argc != 2) {
    cout << "Usage:" << endl << argv[0] << " <inputFile>" << endl;
    return 0;
  }
  input.open(argv[1], ifstream::in);
  if(input.fail()) {
    cout << "Error opening file" << endl;
    return 0;
  }

  input.getline(line, sizeof(line));
  chips = atoi(line);
  order = new int[chips];
  cost_matrix = new int*[chips];
  for(int i = 0; i < chips; i++) {
    cost_matrix[i] = new int[chips];
  }
  for(int i = 0; i < chips; i++) {
    order[i] = i;
  }
  for(int i = 0; i < chips; i++) {
    char* token;
    input.getline(line, sizeof(line));
    token = strtok(line, " ");
    cost_matrix[i][0] = atoi(token);
    for(int j = 1; j < chips; j++) {
      token = strtok(NULL, " ");
      cost_matrix[i][j] = atoi(token);
    }
  }
  anneal(order, chips);

  for(int i = 0; i < chips; i++) {
    printf(" chip %d=pos %d", i, order[i]);
  }
  printf("\ncost is %d\n", (int)solution_cost(order, chips));
  for(int i = 0; i < chips; i++) {
    delete cost_matrix[i];
  }
  delete cost_matrix;
}