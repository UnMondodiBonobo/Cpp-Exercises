#include <iostream>
#include "nsqrt.h"
#include "math.h"

using namespace::std;

short int onOff;

void Calculate()
{
	cout << "Insert a number and I'll find his square root" << endl;
	int x;
	cin >> x;
	cout << "Insert now the error tolerance with decimal numbers or integers" << endl;
	double tolleranza;
	cin >> tolleranza;
	double  RQ = nsqrt(x, tolleranza);
	cout << "The square root of: " << x << "is: " << RQ << endl;
	cout << "Press 0 and enter to exit or press 1 and enter to retry" << endl;
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