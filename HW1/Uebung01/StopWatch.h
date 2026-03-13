#ifndef STOPWATCH_INCLUDED
#define STOPWATCH_INCLUDED

namespace stw {

	// simple stopwatch implementation to measure sequences in seconds or milliseconds
	// usage:  stw::Start();
	//         // sequence to measure ....
	//         cout << "Duration [sec]: " << stw::Stop() << endl;

	void   Start();
	double Stop();    // returns seconds
	double Stop_ms(); // returns milliseconds
}

#endif
