#include <ctime>
#include <random>
#include "RandomGen.h"

int rgen::GetRandVal(int const lo, int const hi) {
	static std::mt19937_64 generator((unsigned)std::time(0));
	return std::uniform_int_distribution <int>(lo, hi) (generator);
}
