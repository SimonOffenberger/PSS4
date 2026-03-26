/*****************************************************************//**
 * \file   Test.hpp
 * \brief  
 * 
 * \author Simon
 * \date   April 2025
 *********************************************************************/
#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <forward_list>

#define ON 1
#define OFF 0
#define COLOR_OUTPUT OFF

// Definitions of colors in order to change the color of the output stream.
const std::string colorRed = "\x1B[31m";
const std::string colorGreen = "\x1B[32m";
const std::string colorWhite = "\x1B[37m";

std::ostream& RED(std::ostream& ost) {
	if (ost.good()) {
		ost << colorRed;
	}
	return ost;
}
std::ostream& GREEN(std::ostream& ost) {
	if (ost.good()) {
		ost << colorGreen;
	}
	return ost;
}
std::ostream& WHITE(std::ostream& ost) {
	if (ost.good()) {
		ost << colorWhite;
	}
	return ost;
}

std::ostream& TestStart(std::ostream& ost) {
	if (ost.good()) {
		ost << std::endl;
		ost << "*******************************************" << std::endl;
		ost << "             TESTCASE START                " << std::endl;
		ost << "*******************************************" << std::endl;
		ost << std::endl;
	}
	return ost;
}

std::ostream& TestEnd(std::ostream& ost) {
	if (ost.good()) {
		ost << std::endl;
		ost << "*******************************************" << std::endl;
		ost << std::endl;
	}
	return ost;
}

std::ostream& TestCaseOK(std::ostream& ost) {

#if COLOR_OUTPUT
	if (ost.good()) {
		ost << colorGreen << "TEST OK!!" << colorWhite << std::endl;
	}
#else 
	if (ost.good()) {
		ost <<  "TEST OK!!" <<  std::endl;
	}
#endif // COLOR_OUTPUT

	return ost;
}

std::ostream& TestCaseFail(std::ostream& ost) {

#if COLOR_OUTPUT
	if (ost.good()) {
		ost << colorRed << "TEST FAILED !!" << colorWhite << std::endl;

	}
#else 
	if (ost.good()) {
		ost << "TEST FAILED !!" << std::endl;

	}
#endif // COLOR_OUTPUT

	return ost;
}

/**
	* \brief function that reports if the testcase was successful.
	*
	* \param testcase	String that indicates the testcase
	* \param succsessful true -> reports to cout test OK
	* \param succsessful false -> reports test failed
	*/
template <typename T>
bool check_dump(std::ostream& ostr, const std::string& testcase, const T& expected, const T& result) {
	if (ostr.good()) {
#if COLOR_OUTPUT
		if (expected == result) {
			ostr << testcase << std::endl <<  colorGreen << "[Test OK] " << colorWhite <<"Result: (Expected: " << std::boolalpha << expected << " ==" << " Result: " << result << ")"  << std::noboolalpha << std::endl << std::endl;
		}
		else {
			ostr << testcase << std::endl << colorRed << "[Test FAILED] " << colorWhite << "Result: (Expected: " << std::boolalpha << expected << " !=" << " Result: " << result << ")"  << std::noboolalpha << std::endl << std::endl;
		}
#else
		if (expected == result) {
			ostr << testcase << std::endl << "[Test OK] "  << "Result: (Expected: " << std::boolalpha << expected << " ==" << " Result: " << result << ")" << std::noboolalpha << std::endl << std::endl;
		}
		else {
			ostr << testcase << std::endl  << "[Test FAILED] "  << "Result: (Expected: " << std::boolalpha << expected << " !=" << " Result: " << result << ")" << std::noboolalpha << std::endl << std::endl;
		}
#endif
		if (ostr.fail()) {
			std::cerr << "Error: Write Ostream" << std::endl;
		}
	}
	else {
		std::cerr << "Error: Bad Ostream" << std::endl;
	}
	return expected == result;
}

template <typename T1, typename T2>
std::ostream& operator<< (std::ostream& ost,const std::pair<T1,T2> & p) {
	if (!ost.good()) throw std::exception{ "Error bad Ostream!" };
	ost << "(" << p.first << "," << p.second << ")";
	return ost;
}

template <typename T>
std::ostream& operator<< (std::ostream& ost,const std::vector<T> & cont) {
	if (!ost.good()) throw std::exception{ "Error bad Ostream!" };
	std::copy(cont.cbegin(), cont.cend(), std::ostream_iterator<T>{ost, " "});
	return ost;
}

template <typename T>
std::ostream& operator<< (std::ostream& ost,const std::list<T> & cont) {
	if (!ost.good()) throw std::exception{ "Error bad Ostream!" };
	std::copy(cont.cbegin(), cont.cend(), std::ostream_iterator<T>{ost, " "});
	return ost;
}

template <typename T>
std::ostream& operator<< (std::ostream& ost,const std::deque<T> & cont) {
	if (!ost.good()) throw std::exception{ "Error bad Ostream!" };
	std::copy(cont.cbegin(), cont.cend(), std::ostream_iterator<T>{ost, " "});
	return ost;
}

template <typename T>
std::ostream& operator<< (std::ostream& ost,const std::forward_list<T> & cont) {
	if (!ost.good()) throw std::exception{ "Error bad Ostream!" };
	std::copy(cont.cbegin(), cont.cend(), std::ostream_iterator<T>{ost, " "});
	return ost;
}


#endif // !TEST_HPP