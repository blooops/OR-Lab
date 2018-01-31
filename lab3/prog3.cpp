#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX_ITER 1000
#define TOL 0.001
using namespace std;

// Function to generate all combinations
template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
   if ((first == last) || (first == k) || (last == k))
      return false;
   Iterator itr1 = first;
   Iterator itr2 = last;
   ++itr1;
   if (last == itr1)
      return false;
   itr1 = last;
   --itr1;
   itr1 = k;
   --itr2;
   while (first != itr1)
   {
      if (*--itr1 < *itr2)
      {
         Iterator j = k;
         while (!(*itr1 < *j)) ++j;
         std::iter_swap(itr1,j);
         ++itr1;
         ++j;
         itr2 = k;
         std::rotate(itr1,j,last);
         while (last != j)
         {
            ++j;
            ++itr2;
         }
         std::rotate(k,itr2,last);
         return true;
      }
   }
   std::rotate(first,k,last);
   return false;
}

// Get the norm of 2 vectors' diff
float get_norm(float* a, float* b, int n) {
    float norm = 0.0f;
    for(int i=0; i<n; i++) {
        norm += (a[i]-b[i])*(a[i] - b[i]);
    }
    return sqrt(norm);
}
// Function to print out a matrix to the screen
void display_matrix(float** matrix, int nrows, int ncols) {
    for(int i=0; i<nrows; i++) {
        for(int j=0; j<ncols; j++) {
           cout << " " << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to print out a vector to the screen
void display_vector(float* vector, int n) {
    for(int i=0; i<n; i++)
        cout << " " << vector[i] << " ";
    cout << endl;
}

// Function to solve a simultaneous linear equation set:
void solve_linear_equation(float** A, float* b, int nvar, int neq) {
    int n = nvar;
    float* x0, *x;

    // dynamic memory allocations
    x0 = new float[n];
    x = new float[n];


    // check that diagonal elements are non-zero
    int flag = 1;
    for(int i=0; i<n; i++) {
        if(A[i][i] == 0) {
            flag = 0;
            break;
        }
    }

    if(flag == 0) {
        cout << "This set of equations cannot be solved by jacobi method" << endl;
        return;
    }

    // System can be solved. Check if solutions exist


    // Solve the given equation:
    for(int i=0; i<n; i++)
        x0[i] = 0.0f;

    for(int k=0; k<MAX_ITER; k++) {
        for(int i=0; i<n; i++) {
            x[i] = 0.0f;
            for(int j=0; j<n; j++) {
                if(j!=i)
                x[i] += (-1.0f * A[i][j] * x0[j] );
            }
            x[i] += b[i];
            x[i] /= A[i][i];
        }

        //cout << "Step : " << k << endl;
        //display_vector(x0, n);
        //display_vector(x, n);

        if(get_norm(x, x0, n) < TOL) {
            cout << "The solution obtained is: " << endl;
            display_vector(x, n);

        }

        else {
            //cout << "Norm : " << get_norm(x, x0, n) << endl;
            for(int i=0; i<n; i++)
                x0[i] = x[i];
        }

    }

    // Job done, free unwanted memory
    delete[] x;
    delete[] x0;  
}

// Function to calculate factorial
int fact(int n) {
    if(n == 1)
        return 1;
    else return n * fact(n-1);
}

// Function to print out the different basic solutions and their types
void print_basic_solutions(float** A, float* b, int nvar, int neq) {
    float* xb, *xnb;

    // Allocating and declaring xb, xnb, B, NB :
    xb = new float[neq];
    xnb = new float[nvar - neq];

    float** B = new float*[neq];
    for(int i=0; i<neq; i++)
        B[i] = new float[neq];

    float** NB = new float*[neq];
    for(int i=0; i<neq; i++)
        NB[i] = new float[nvar-neq];

    // generating a matrix containing all combinations of indices to be selected
    std::size_t n_t = nvar;
    std::size_t k_t = neq;

    std::vector<int> ints;
    for (int i = 0; i < n_t; ints.push_back(i++));

    do
    {
	cout << "New combinations" << endl;
	cout << endl << "Indices of basic variables : " << endl;
   	for (int i = 0; i < k_t; ++i)
   	{
      	    cout << ints[i];
   	}

	// NOW solve basic variables equation
	for(int i = 0; i<neq; i++) {
	    for(int j=0; j<neq; j++) {
                B[i][j] = A[i][ints[j]];
	    }
    }
	cout << endl << "Matrix B : " << endl;
    display_matrix(B, neq, neq);
	cout << endl << "Matrix b : " << endl;
	display_vector(b, neq);
    //solve_linear_equation(B, b, neq, neq);

        // Finished solving move on to next combination
   	cout << endl;
    }
    while(next_combination(ints.begin(),ints.begin() + k_t,ints.end()));
    
    delete[] xb;
    delete[] xnb;
    for(int i=0; i<neq; i++){ delete[] B[i]; delete[] NB[i]; }
}

int main() {

    // Inputting relative sizes of variables
    int nvar, neq;
    cout << "Enter the number of variables : "<<endl;
    cin >> nvar;
    cout << "Enter the number of equations : " << endl;
    cin >> neq;
    
    float** A;
    float* b;

    // Memory allocation

    A = new float*[neq];
    for(int i=0; i<neq; i++)
        A[i] = new float[nvar];

    b = new float[neq];

    // Obtaining user input and printing
    cout << "Enter Matrix A : " << endl;
    for(int i=0; i<neq; i++) 
        for(int j=0; j<nvar; j++)
            cin >> A[i][j];

    cout << "Enter  Matrix b : " << endl;
    for(int i=0; i<neq; i++)
        cin  >> b[i];

    cout << "Entered Matrix A : " << endl;
    display_matrix(A, neq, nvar);
    cout << endl << "Entered Matrix B : " << endl;
    display_vector(b, neq); 
    print_basic_solutions(A, b, nvar, neq);
    

    for(int i = 0; i<neq; i++) {delete[] A[i];}
    delete[] b;
    return 0;
}
