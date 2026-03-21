// --------------------------------------------------
// Loesung des Optimierungsproblems "Rucksack"
// mittels Backtracking:
// Gegeben sind n Gegenstaende mit den Volumina
// v[1] .. v[n] und ein Rucksack mit dem
// Fassungsvermoegen f. Wird Gegenstand i im
// Rucksack mitgenommen, so wird der Gewinn
// g[i] erzielt. Gesucht ist eine Fuellung des
// Rucksacks mit (Gesamtvolumen <= f und)
// maximalem Gewinn.
// Indizierung ab 1, Komponenten 0 von Feldern
// werden nicht benutzt
// (c) Andreas Frommer, Bruno Lang
// ---------------------------------------------------

#include <iostream>

using namespace std;

// Untersucht, ob eine Fuellung des Rucksacks mit
// und/oder ohne Gegenstand i zu einem optimalen
// Gewinn fuehren kann. x[ 1 .. i-1 ] ist der
// bereits festgelegte Teil der gerade betrachteten
// Fuellung (x[i] = true(false) heisst, dass Gegenstand
// i (nicht) mitgenommen wird), g_x und v_x der zu
// dieser Teilfuellung gehoerige Gewinn bzw. das
// Volumen, g_rest der durch Mitnahme aller
// restlichen Gegenstaende i .. n erzielbare
// Gesamtgewinn.
void Einpacken(int const n, int i, double f, double const g[], double const v[], bool x[],
	double const& g_x, double const& v_x, double g_rest, double& g_opt, double& v_opt, bool opt_fuellung[]) {
	int j = 0;

	if (i > n) {	// Fuellung vollstaendig
		if (g_x > g_opt) { // neues Optimum
			for (j = 1; j <= n; j++) {
				opt_fuellung[j] = x[j];
			}
			g_opt = g_x;
			v_opt = v_x;
		}
	}
	else { // betrachte Gegenstand i
		g_rest -= g[i];
		if ((v_x + v[i] <= f) && (g_x + g[i] + g_rest > g_opt)) {
			// vervollstaendige Fuellung MIT Gegenstand i
			x[i] = true; // mitnehmen
			Einpacken(n, i + 1, f, g, v, x, g_x + g[i], v_x + v[i], g_rest, g_opt, v_opt, opt_fuellung);
		}

		if (g_x + g_rest > g_opt) {
			// vervollstaendige Fuellung OHNE Gegenstand i
			x[i] = false; // nicht mitnehmen
			Einpacken(n, i + 1, f, g, v, x, g_x, v_x, g_rest, g_opt, v_opt, opt_fuellung);
		}
	}
}


// ------------------------------------------------
int main() {

	// Eingabedaten:
	// -------------
	double const f = 5;		// max. Fassungsvermoegen des Rucksacks
	int    const n = 4;		// Anzahl aller Gegenstaende

	// g[i]: Gewinn fuer Gegenstand i, wobei i im Intervall [1..n]
	double g[n + 1] = { 0, 11, 20, 30, 40 };

	// v[i]: Volumen von Gegenstand i, wobei i im Intervall [1..n]
	double v[n + 1] = { 0, 1, 2, 3, 4 };
	// -------------


	bool x[n + 1];			// aktuelle (Teil-)Fuellung
	bool opt_fuellung[n + 1]; // bisher beste (vollstaendige) Fuellung
	double g_opt = 0.0;		// Gewinn dieser besten Fuellung
	double v_opt = 0.0;		// Volumen dieser besten Fuellung
	double g_rest = 0.0;	// Gewinn aller restl. Gegenstaende


	// Initialisierung: leerer Rucksack
	for (int i = 1; i <= n; i++) {
		x[i] = false;				// nicht mitnehmen
		opt_fuellung[i] = false;	// nicht mitnehmen
		g_rest += g[i];
	}

	// Loesung bestimmen
	Einpacken(n, 1, f, g, v, x, 0.0, 0.0, g_rest, g_opt, v_opt, opt_fuellung);

	// Ergebnis ausgeben
	for (int i = 1; i <= n; i++) {
		if (opt_fuellung[i] == true) {
			cout << "Gegenstand " << i << " wird mitgenommen" << endl;
		}
		else {
			cout << "Gegenstand " << i << " wird nicht mitgenommen" << endl;
		}
	}
	cout << "Erzielter Gesamtgewinn: " << g_opt << endl;
	cout << "bei einem Volumen von " << v_opt << endl;

	return 0;
}

/* Ausgabe:

Gegenstand 1 wird mitgenommen
Gegenstand 2 wird nicht mitgenommen
Gegenstand 3 wird nicht mitgenommen
Gegenstand 4 wird mitgenommen
Erzielter Gesamtgewinn: 51
bei einem Volumen von 5
Press any key to continue . . .
*/


