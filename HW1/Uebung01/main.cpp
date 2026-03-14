/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include <iostream>
#include "Matrix.h"
#include "Fib.hpp"

using namespace std;

int main(void){
	
	PrintFibSequenceMultiThreaded(40);

	BenchmarkFib(43);

	Matrix * pA = new Matrix;
	Matrix * pB = new Matrix;
	Matrix * pC = new Matrix;


	pA->Init(3);
	pB->Init(5);

	*pC = (*pA) * (*pB);

	pC->Print(cout);

	delete pA, pB, pC;

}
