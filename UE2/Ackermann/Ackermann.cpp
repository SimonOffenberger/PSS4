///////////////////////////////////////////////////////////
// Berechnung der Ackermann-Funktion
// Implementierung
///////////////////////////////////////////////////////////
#include "Ackermann.h"

int Ackermann::AMann(int m, int n) {

    if (m == 0)          return n + 1;              // A(0,n) = n + 1
    if (n == 0 && m > 0) return AMann(m - 1, 1);    // A(m,0) = A(m-1, 1)
    return AMann(m - 1, AMann(m, n - 1));           // A(m,n) = A(m-1, A(m,n-1))
}


