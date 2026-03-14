/*****************************************************************//**
 * @file Fib.hpp
 * @brief Declarations for Fibonacci benchmarking and concurrent printing.
 *
 * Provides functions to benchmark recursive Fibonacci calculations
 * and to print Fibonacci sequences using multiple threads.
 *********************************************************************/
#ifndef FIB_HPP
#define FIB_HPP


/**
 * @brief Run a benchmark for computing fib(max_fib_n) in single- and multi-threaded modes.
 * @param max_fib_n Maximum Fibonacci input to compute.
 */
void BenchmarkFib(size_t max_fib_n);

/**
 * @brief Print the Fibonacci sequence up to max_fib_n using multiple worker threads.
 * @param max_fib_n Maximum Fibonacci input to compute and print.
 */
void PrintFibSequenceMultiThreaded(size_t max_fib_n);


#endif // !FIB_HPP