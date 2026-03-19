#ifndef ACKERMANN_INCLUDED
#define ACKERMANN_INCLUDED

/////////////////////////////////////////////////////////////////
// Berechnung der Ackermann-Funktion
// Verwendung: int Res = Ackermann::AMann(3,10);  -> OK für 1MB Stack
/////////////////////////////////////////////////////////////////

class Ackermann {
	Ackermann();
	Ackermann(Ackermann const &);
	Ackermann& operator = (Ackermann const &);

public:

	static int AMann(int m, int n);
};


#endif