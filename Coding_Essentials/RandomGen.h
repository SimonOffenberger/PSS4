#ifndef RANDOMGEN_INCLUDED
#define RANDOMGEN_INCLUDED

namespace rgen {

	// returns a random value between lo and hi
	// usage: cout << rgen::GetRandVal(-100, 100);
	int GetRandVal(int const lo, int const hi);
}

#endif
