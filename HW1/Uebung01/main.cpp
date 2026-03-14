/*****************************************************************//**
 * @file main.cpp
 * @brief Test driver that runs matrix multiplication tests and 
 *        Fibonacci demos/benchmarks.
 *
 * The program writes results to console and optionally to a file "Testoutput.txt".
 *********************************************************************/
#include <iostream>
#include "Matrix.h"
#include "Fib.hpp"
#include "Test.hpp"
#include <memory>
#include <cassert>
#include "vld.h"

using namespace std;

#define WriteOutputFile ON

static bool Test_Matrix_Multiplication(std::ostream & ost);

int main(void){


    ofstream output{ "Testoutput.txt" };
    if (!output.is_open()) {
        cerr << "Konnte Testoutput.txt nicht oeffnen" << TestCaseFail;
        return 1;
    }

    try {
		bool TestOK = true; 

	    PrintFibSequenceMultiThreaded(10);
	    BenchmarkFib(10);

        TestOK = TestOK && Test_Matrix_Multiplication(cout);


        if (WriteOutputFile) {

            TestOK = TestOK && Test_Matrix_Multiplication(output);


            if (TestOK) {
                output << TestCaseOK;
            }
            else {
                output << TestCaseFail;
            }

            output.close();
        }

        if (TestOK) {
            cout << TestCaseOK;
        }
        else {
            cout << TestCaseFail;
        }
    }
    catch (const string& err) {
        cerr << err << TestCaseFail;
    }
    catch (bad_alloc const& error) {
        cerr << error.what() << TestCaseFail;
    }
    catch (const exception& err) {
        cerr << err.what() << TestCaseFail;
    }
    catch (...) {
        cerr << "Unhandelt Exception" << TestCaseFail;
    }

    if (output.is_open()) output.close();

    return 0;

}

/**
 * @brief Run tests for matrix multiplication and report results to given stream.
 * @param ost Output stream to write test details to.
 * @return true if all tests passed, false otherwise.
 *
 * The function performs:
 *  - multiplication with a zero matrix
 *  - multiplication with an identity matrix
 *  - checks for exceptions
 */
bool Test_Matrix_Multiplication(std::ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    try
    {

        unique_ptr<Matrix> A = make_unique<Matrix>();
        unique_ptr<Matrix> B = make_unique<Matrix>();
        unique_ptr<Matrix> C = make_unique<Matrix>();

        A->Init(0);
        B->Init(5);

        *C = (*A) * (*B);

        TestOK = TestOK && check_dump(ost, "Test for Matrix Multiplication with 0 Matrix", *A, *C);

        A->Init(0);
        B->Init(5);

		// create identity matrix in A
        for(size_t i= 0; i < Matrix::n; ++i) {
            A->GetMatrix()[i][i] = 1;
		}

        *C = (*A) * (*B);
		TestOK = TestOK && check_dump(ost, "Test for Matrix Multiplication with Identity Matrix", *B, *C);

        A->Init(0);
        B->Init(5);

		// create identity matrix in A
        for(size_t i= 0; i < Matrix::n; ++i) {
            A->GetMatrix()[i][i] = -1;
		}

        *C = (*A) * (*B);
        
		unique_ptr<Matrix> expected = make_unique<Matrix>();
		expected->Init(-5);

		TestOK = TestOK && check_dump(ost, "Test for Matrix Multiplication with negative Identity Matrix", *expected, *C);


        A->GetMatrix()[0][0] = 1;
        A->GetMatrix()[0][1] = -2;
        A->GetMatrix()[0][2] = 3;
        A->GetMatrix()[1][0] = 4;
        A->GetMatrix()[1][1] = -5;
        A->GetMatrix()[1][2] = -6;
        A->GetMatrix()[2][0] = -7;
        A->GetMatrix()[2][1] = 8;
        A->GetMatrix()[2][2] = 9;

        B->GetMatrix()[0][0] = 9;
        B->GetMatrix()[0][1] = 8;
        B->GetMatrix()[0][2] = 7;
        B->GetMatrix()[1][0] = 6;
        B->GetMatrix()[1][1] = 5;
        B->GetMatrix()[1][2] = 4;
        B->GetMatrix()[2][0] = 3;
        B->GetMatrix()[2][1] = 2;
        B->GetMatrix()[2][2] = 1;

        expected->GetMatrix()[0][0] = 6;
        expected->GetMatrix()[0][1] = 4;
        expected->GetMatrix()[0][2] = 2;
        expected->GetMatrix()[1][0] = -12;
        expected->GetMatrix()[1][1] = -5;
        expected->GetMatrix()[1][2] = 2;
        expected->GetMatrix()[2][0] = 12;
        expected->GetMatrix()[2][1] = 2;
        expected->GetMatrix()[2][2] = -8;

        *C = (*A) * (*B);

		TestOK = TestOK && check_dump(ost, "Test for Matrix Multiplication with provided Example", *expected, *C);

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Exception in TestCase", true , error_msg.empty());
    error_msg.clear();


    ost << TestEnd;

    return TestOK;
}
