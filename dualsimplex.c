#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float* dual_simplex(int** table, int nrows, int ncols) {
  int i, j, k, l;

  // Calculate the number of equations and variables
  int neqs = nrows - 3; int nvars = ncols - 2;

  // Create and initialize solution variable
  float* sol = (float*) malloc(sizeof(float) * nvars);
  for(i = 0; i < nvars; i++)
    sol[i] = 0.0f;
  for(i=0; i<neqs; i++)
    sol[nvars-neqs] = table[i][ncols-1]; // initializing BFS

  int out_index, in_index;
  bool optimality_reached = false;
  bool solution_unbounded = false;

  // Dual Simplex loop:
  while(true) {
    // Check if optimal solution has been reached:

    // Select the leaving variables by index:
    float min_b; int min_b_index;
    min_b = table[0][ncols-1]; min_b_index = 0;
    for(i = 1; i < neqs; i++) {
      if(min_b > table[i][ncols-1]) {
        min_b = table[i][ncols-1]; min_b_index = i;
      }
    }

    // Select the entering variable:
    for(i = 0; i < nvars; i++) {
      table[neqs+1][i+1] = 0.0f;
      for(j = 0; j < neqs; j++)
        table[neqs+1][i+1] += table[1+j][i+1] * table[1+j][0];
      table[neqs+1][i+1] -= table[0][i+1];
      table[neqs+2][i+1] /= table[min_b_index][i+1];
    }

    float max_ratio, max_ratio_index;
    max_ratio = -100000000f; max_ratio_index = -1;

    for(i = 0; i < nvars; i++) {
      if(!isnan(table[neqs+2][i+1]) && !isinf(table[neqs+2][i+1])) {
        if(max_ratio < table[neqs+2][i+1]) {
          max_ratio = table[neqs+2][i+1]; max_ratio_index = i+1;
        }
      }
    }

    float pivot = table[min_b_index][max_ratio_index];

    if(pivot == 0.0f) {
      printf("ZERO VALUED PIVOT ELEMENT!\n");
      return NULL;
    }

    // Transform and interchange tableau values for next iteration:
    for(i = 0; i < nvars; i++)
      table[min_b_index][i+1] /= pivot;
    table[min_b_index][nvars+1] /= pivot;

    table[min_b_index][0] = table[0][max_ratio_index];

    for(i = 0; i < neqs; i++) {
      if(i+1 == min_b_index)
        continue;
      else if(table[i+1][max_ratio_index] == 0.0f)
        continue;

      float fact = -1.0f * table[i+1][max_ratio_index];

      for(j = 0; j <= nvars; j++) {
        
      }
    }


  }
}

int main() {

}
