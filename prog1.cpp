#include <iostream>
#include <cmath>

#define MAX_ITER 100
#define TOL 0.000001f

using namespace std;

void matrix_exchange_rows(float** matrix, int n, int i, int j) {
    for(int k=0; k<n; k++) {
        float tmp;
        tmp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = tmp;
    }
}

void matrix_scale_row(float** matrix, int n, int i, float value) {
    for(int j=0; j<n; j++)
        matrix[i][j] *= value;
}

void matrix_scale_add_row(float** matrix, int n, int i, int j, float value) {
    for(int k=0; k<n; k++) 
        matrix[i][k] += matrix[j][k] * value;
}

void display_matrix(float** matrix, int nrows, int ncols) {
    for(int i=0; i<nrows; i++) {
        for(int j=0; j<ncols; j++) {
            cout << " " << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void get_rank(float** matrix, int nrows, int ncols) {
}

void display_vector(float* v, int n) {
    for(int i =0; i<n; i++)
        cout << " " << v[i] << " " ;

    cout << endl;
}

float get_norm(float* a, float* b, int n) {
    float norm = 0.0f;
    for(int i=0; i<n; i++) {
        norm += (a[i]-b[i])*(a[i] - b[i]);
    }
    return sqrt(norm);
}

void solve_jacobi() {
    int n;
    float** A;
    float* x0, *x;
    float* b;

    // taking user input
    cout << "Enter the number of equations/varialbles : " << endl;
    cin >> n;

    // dynamic memory allocations
    b = new float[n];
    x0 = new float[n];
    x = new float[n];
    A = new float*[n];

    for(int i=0; i<n; i++) 
        A[i] = new float[n];

    // Take user input for the equations:
    for(int i=0; i<n; i++) {
        cout << "Input coefficients for equation " << i << endl;
        for(int j=0; j<n; j++)
            cin >> A[i][j];

        cout << "Input the rhs value of the equation " << i << endl;
        cin >> b[i];
    }

    // Print out the matrices / vectors:
    cout << "Matrix A :" << endl;
    display_matrix(A, n, n);
    cout << "Vector B :" << endl;
    display_vector(b, n);


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

        cout << "Step : " << k << endl;
        display_vector(x0, n);
        display_vector(x, n);

        if(get_norm(x, x0, n) < TOL) {
            cout << "The solution obtained is: " << endl;
            display_vector(x, n);
            break;
        }

        else {
            cout << "Norm : " << get_norm(x, x0, n) << endl;
            for(int i=0; i<n; i++)
                x0[i] = x[i];
        }

    }

    // Job done, free unwanted memory
    delete[] x;
    delete[] x0;
    delete[] b;
    for(int i=0; i<n; i++)
        delete[] A[i];

}

int main() {
    solve_jacobi();
}

