#include <iostream>
#include "nsqrt.h"
#include "math.h"

using namespace::std;

short int onOff;

void Calculate()
{
	cout << "Si inserisca un valore di cui si vuol trovare la radice quadrata" << endl;
	int x;
	cin >> x;
	cout << "Si inserisca ora l'errore tollerato con virgola mobile o intero" << endl;
	double tolleranza;
	cin >> tolleranza;
	double  RQ = nsqrt(x, tolleranza);
	cout << "La radice quadrata di: " << x << "e': " << RQ << endl;
	cout << "Premi 0 ed invia per uscire oppure premi 1 ed invia per ricalcolare" << endl;
	cin >> onOff;


}

int main() 
{
	Calculate();
	while (onOff == 1) 
	{
		Calculate();
		
	}

	return 0;
}