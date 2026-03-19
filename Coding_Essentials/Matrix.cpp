////////////////////////////////////////////////////////////////////////////
// class Matrix encapsulates a single matrix
// Implementation
// Michael Bogner / PSS4 / HSD
////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Matrix.h"

// init entire matrix with value val
void Matrix::Init(double const & val) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mMatrix[i][j] = val;
        }
    }
}


void Matrix::AttachTemperature() {

    // 10x10 Matrix
    //assert(n == 10);
    //mMatrix[0][n-1] = 50;
    //mMatrix[1][n-1] = 400;
    //mMatrix[2][n-1] = 700;
    //mMatrix[3][n-1] = 900;
    //mMatrix[4][n-1] = 1000;
    //mMatrix[5][n-1] = 1000;
    //mMatrix[6][n-1] = 900;
    //mMatrix[7][n-1] = 700;
    //mMatrix[8][n-1] = 400;
    //mMatrix[9][n-1] = 50;

    // 32x32 Matrix
    assert(n == 32);
    mMatrix[0][n-1] =   20;
    mMatrix[1][n-1] =   50;
    mMatrix[2][n-1] =  100;
    mMatrix[3][n-1] =  150;
    mMatrix[4][n-1] =  200;
    mMatrix[5][n-1] =  250;
    mMatrix[6][n-1] =  300;
    mMatrix[7][n-1] =  350;
    mMatrix[8][n-1] =  400;
    mMatrix[9][n-1] =  500;
    mMatrix[10][n-1] = 600;
    mMatrix[11][n-1] = 700;
    mMatrix[12][n-1] = 800;
    mMatrix[13][n-1] = 900;
    mMatrix[14][n-1] = 950;
    mMatrix[15][n-1] = 1000;

    // symmetric on other side
    for (int i = 16; i < n; i++) {
        mMatrix[i][n-1] = mMatrix[31-i][n-1];
    }

     // 250x250 Matrix
    //assert(n == 250);
    //mMatrix[ 98][n-1] = 1000;
    //mMatrix[ 99][n-1] = 1000;
    //mMatrix[100][n-1] = 1000;
    //mMatrix[101][n-1] = 1000;
    //mMatrix[102][n-1] = 1000;

}



// print the matrix
void Matrix::Print(std::ostream & ost) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ost << static_cast<int>(mMatrix[i][j]) << "  ";
        }
        ost << std::endl;
    }
}


// print the matrix as comma seperated values file (readable by MS Excel)
void Matrix::PrintAsCSVFile() {
    std::ofstream out("MatrixTempResult.csv");
    assert(out.good()); // check if file could be opened/created

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out << static_cast<int>(mMatrix[i][j]) << ";";
        }
        out << std::endl;
    }
    out.close();
}

