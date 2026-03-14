////////////////////////////////////////////////////////////////////////////
// @file Matrix.cpp
// @brief Implementation of the Matrix class.
//        Provides initialization, multi-threaded multiplication (one thread per cell),
//        comparison and printing helpers.
// @author Michael Bogner
// @date   March 2026
////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <vector>
#include <algorithm>
#include "Matrix.h"
#include "windows.h"
#include "Hlp.h"

using namespace std;

// init entire matrix with value val
void Matrix::Init(double const & val) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mMatrix[i][j] = val;
        }
    }
}


// structure to pass the parameters for the cell multiplication task to the worker thread
typedef struct {
	const Matrix* pMatrixA;
    const Matrix* pMatrixB;
	Matrix* pResultMatrix;
	size_t row;
	size_t col;
}TCellTask ;

/**
 * \brief Worker Function that calculates the result of a Matrix Muliplication
 * \brief for one Cell of the result Matrix.
 * 
 * \param ptask Pointer to a TCellTask structure that contains the parameters for the cell multiplication.
 * \return 
 */
DWORD WINAPI Matrix_Cell_Mul(LPVOID ptask) {

    TCellTask* task = static_cast<TCellTask*>(ptask);

    double sum = 0;
    for (size_t i = 0; i < task->pMatrixA->n; ++i) {
        sum += task->pMatrixA->GetMatrix()[task->row][i] * task->pMatrixB->GetMatrix()[i][task->col];
    }

    task->pResultMatrix->GetMatrix()[task->row][task->col] = sum;

    return 0;
}


Matrix Matrix::operator*(Matrix const & other) const
{
	// result matrix
    Matrix result;    
    const size_t num_threads = n * n;
    
	// vectors to store the tasks, handles and thread IDs of the worker threads
    std::vector<TCellTask> tasks;
    std::vector<HANDLE> worker_threads;
    std::vector<DWORD> thread_ids(num_threads, 0);
	
	// reserve space in the vectors to avoid reallocations
    tasks.reserve(num_threads);
    worker_threads.reserve(num_threads);

    size_t idx = 0;

	// Start a worker thread for each cell in the result matrix
    for (size_t row = 0; row < n; ++row) {
        for (size_t col = 0; col < n; ++col) {

			// Fill the task structure with the parameters for the cell multiplication
			TCellTask task{ this, &other, &result, row, col };

			// Store the task in the vector and start a worker thread to execute the cell multiplication
            tasks.emplace_back(move(task));

            HANDLE Worker = CreateThread(
                0,
                0, // default stack size (1MB), value determines the number of bytes
                Matrix_Cell_Mul,
                &tasks.back(),
                0,
                &thread_ids.at(idx)
            );

			// check if the thread was created successfully
            if(Worker == nullptr) {
                throw runtime_error(ERROR_CREATING_THREAD + Hlp::ErrMsg(GetLastError()));
			}

			// Store the handle of the worker thread in the vector
            worker_threads.emplace_back(Worker);

            ++idx;
        }
    }

	// Wait for all worker threads to finish and close their handles
    for_each(worker_threads.cbegin(), worker_threads.cend(), [](const HANDLE& hThread) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
    });

	// Return the result matrix (RVO / move)
    return move(result);
}

bool Matrix::operator==(Matrix const& other) const
{

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (mMatrix[i][j] != other.mMatrix[i][j]) {
                return false;
            }
        }
	}

    return true;
}

// print the matrix
void Matrix::Print(std::ostream & ost) const {

    if(!ost.good()) {
        throw std::invalid_argument(ERROR_BAD_OSTREAM);
	}

    ost << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ost << static_cast<int>(mMatrix[i][j]) << "  ";
        }
        ost << std::endl;
    }
}


// print the matrix as comma separated values file (readable by MS Excel)
void Matrix::PrintAsCSVFile() const {
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

std::ostream& operator<<(std::ostream& ost, const Matrix& M)
{
    if (!ost.good()) {
        throw std::invalid_argument(Matrix::ERROR_BAD_OSTREAM);
    }

    M.Print(ost);

    return ost;
}
