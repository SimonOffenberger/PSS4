#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

////////////////////////////////////////////////////////////////////////////
// class Matrix encapsulates a single matrix
// Michael Bogner / PSS4 / HSD
////////////////////////////////////////////////////////////////////////////

#include <fstream>

class Matrix {
public:
    // Declarations and Members
    static int const n = 64 /* 250*/ ;   // size of matrix: set this value according your needs!
    typedef double TMatrix[n][n];        // type of matrix
 
    // CTor
    Matrix() {}

    // DTor
    virtual ~Matrix() {}

    // init entire matrix with value val
    void Init(double const & val);

    // set special values into the matrix to simulate temperature
    // note: this is specific to the current matrix size n, of course!
    void AttachTemperature();

    TMatrix & GetMatrix() {
        return mMatrix;
    }

    const TMatrix & GetMatrix() const {
        return mMatrix;
    }

	Matrix operator*(Matrix const & other) const;

    // print the matrix
    void Print(std::ostream & ost);
    void PrintAsCSVFile();

private:
    TMatrix mMatrix;    // the matrix
};

#endif