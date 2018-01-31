#include "../utils/matrix.h"

void simplex_solve(Matrix<float>& A, Matrix<float>& b, 
                   Matrix<float>& c) {
    unsigned basic = A.getRows();
    unsigned nbasic = A.getColumns() - A.getRows();

    Matrix<float> Cb(1, basic);
    Matrix<float> Xb(1, basic);
    Matrix<float> Xnb(1, nbasic);
    Matrix<unsigned> Xbvars(1, basic);
    Matrix<unsigned> Xnbvars(1, nbasic);
    Matrix<float> Deltas();
    float Z;

    std::cout << "Initializing for simplex method: "
              << std::endl;

    // Initializing Xbvars and Xnbvars:
    for(int i=0; i<basic; i++) {
        Xbvars.put(0, i, i);
    }

    for(int i=0; i<Xbvars.getColumns(); i++) {
        Xb.put(0, i, b.get(i,0));
    }

    std::cout << "Xbvars = " <<std::endl;
    std::cout << Xbvars << std::endl;
    std::cout << "Xb = " <<std::endl;
    std::cout << Xb << std::endl;


    for(int i=0; i<nbasic; i++) {
        Xnbvars.put(0, i, basic+i );
    }

    for(int i=0; i<Xnbvars.getColumns(); i++) {
        Xnb.put(0, i, 0.0f);
    }

    std::cout << "Xnbvars = " <<std::endl;
    std::cout << Xnbvars << std::endl;
    std::cout << "Xnb = " <<std::endl;
    std::cout << Xnb << std::endl;

    // Creating BFS initial
    Matrix<float> BFS1(1, A.getColumns());

    for(int i=0; i<BFS1.getColumns(); i++) {
        if(i < basic)
            BFS1.put(0, i, Xb.get(0, i));
        else
            BFS1.put(0, i, Xnb.get(0, i-basic));
    }

    

    // Print out Initial data:
    std::cout << " Initial BFS : "<< std::endl;
    std::cout << BFS1 << std::endl;

    std::cout << "Now starting iterations:" << std::endl;

    int numIterations = 1;

    while(false) {
        std::cout << std::endl << " ITERATION : " << numIterations
                  << std::endl;
        
        numIterations++;
    }
}


int main() {
    unsigned nrows, ncols;
    std::cout << "Enter the details of the problem :" << std::endl;
    std::cout << "Number of variable : "<< std::endl;
    std::cin >> ncols;
    std::cout << "Number of equations : " << std::endl;
    std::cin >> nrows;

    // Create matrix of dim nrows * ncols
    Matrix<float>  A(nrows, ncols);

    // Inputting values into Matrices:
    for(int i=0; i<A.getRows(); i++) {
        std::cout << "Enter the coefficients for equation " << i 
                  << std::endl;
        for(int j=0; j<A.getColumns(); j++) {
            std::cout << " Enter the coefficient of variable x["
                      << j << "]" << std::endl; 
            float tmp; std::cin >> tmp;
            A.put(i, j, tmp);
        }
    }

    // Print the Matrix that has just been inputted:
    std :: cout << std::endl << "The Entered Matrix is " << std::endl;
    std :: cout << A;

    // Create Matrix B
    Matrix<float> b(nrows, 1);

    // Inputting the values for matrix b:
    for(int i=0; i<b.getRows(); i++) {
        std::cout << "Enter the value of RHS for equation " << i 
                  << std::endl;
        float tmp;
        std::cin >> tmp;
        b.put(i,0, tmp);
    }

    // Print the entered matrix to confirm
    std::cout << "The entered Matrix b is : " << std::endl;
    std::cout << b;

    // Print the system of equations being solved to confirm:
    std::cout << "equation to be solved is : " << std::endl;
    for(int i=0; i<A.getRows(); i++) {
        for(int j=0; j<A.getColumns() -1; j++) {
            std::cout << A.get(i, j) << "*x" << j << " + ";
        }
        std::cout << A.get(i, A.getColumns()-1) << "*x" << A.getColumns() -1 
        << " = " << b.get(i,0) << std::endl;
    }

    // Enter constraint matrix
    std::cout << "Enter the values of the constraint matrix:" << std::endl;
    Matrix<float> c(1, A.getColumns());
    for(int i=0; i<A.getColumns(); i++) {
        std::cout << "Input the cost of variable x" << i << std::endl;
        float tmp;
        std::cin >> tmp;
        c.put(0, i, tmp);
    }
    std::cout << "The entered constraint matrix is" << std::endl;
    std::cout << c;

    // Start solving using simplex method

    simplex_solve(A, b, c);
    return 0;

}

