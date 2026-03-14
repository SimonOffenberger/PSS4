#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

////////////////////////////////////////////////////////////////////////////
// @file Matrix.h
// @brief Declaration of the Matrix class which encapsulates a single matrix
//        and provides basic operations (init, multiply, compare, print).
// @author Michael Bogner
// @version Revision history:
//          - March 2026: Simon Offenberger (updates)
////
////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <string>
#include <array>

/**
 * @class Matrix
 * @brief Simple fixed-size matrix type with basic operations.
 *
 * The matrix size is controlled by the static constant `n`.
 * The class provides initialization, multiplication (multi-threaded),
 * comparison and printing utilities.
 */
class Matrix {
public:

    inline static const std::string ERROR_CREATING_THREAD = "Failed to create thread: ";
    inline static const std::string ERROR_BAD_OSTREAM = "Error Ostream is bad!";

    // Declarations and Members
    static int const n = 3 /* 250*/ ;   // size of matrix: set this value according to your needs!

    typedef double TMatrix[n][n];        // underlying matrix storage type
 
    /**
     * @brief Default constructor.
     */
    Matrix() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Matrix() {}

    /**
     * @brief Initialize entire matrix with the given value.
     * @param val Value to write to every cell.
     */
    void Init(double const & val);

    /**
     * @brief Accessor (non-const) for the underlying matrix.
     * @return Reference to the raw matrix array.
     */
    TMatrix & GetMatrix() {
        return mMatrix;
    }

    /**
     * @brief Accessor (const) for the underlying matrix.
     * @return Const reference to the raw matrix array.
     */
    const TMatrix & GetMatrix() const {
        return mMatrix;
    }

    /**
     * @brief Matrix multiplication operator.
     * @param other Right-hand side matrix.
     * @return Result of multiplying this * other.
     *
     * The multiplication implementation uses one worker thread per result cell.
     */
	Matrix operator*(Matrix const & other) const;

	/**
	 * @brief Equality operator for matrices.
	 * @param other Matrix to compare with.
	 * @return true if all cells are equal, false otherwise.
	 */
	bool operator==(Matrix const& other) const;

    /**
     * @brief Print matrix to the given output stream in a human readable form.
     * @param ost Output stream to write to.
     * @throws std::invalid_argument if the output stream is bad.
     */
    void Print(std::ostream & ost) const;

    /**
     * @brief Write matrix as a CSV file ("MatrixTempResult.csv").
     *        Values are separated with ';' to be Excel-friendly.
     */
    void PrintAsCSVFile() const;

private:
    TMatrix mMatrix = { 0 };    // the matrix
};

/**
 * @brief Stream insertion operator for Matrix.
 * @param ost Output stream.
 * @param M Matrix to print.
 * @return Reference to the stream.
 * @throws std::invalid_argument if the stream is bad.
 */
std::ostream& operator<<(std::ostream& ost, const Matrix & M);


#endif