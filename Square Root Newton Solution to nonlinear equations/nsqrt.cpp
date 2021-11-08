#include <iostream>
#include "nsqrt.h"
#include "math.h"

double nsqrt(double x, double epsilon) 
{
	double s = x / 2;

	do 
	{
		s = ((s * s) + x) / (2 * s);

	} while (abs((s*s)-x) >= epsilon);

	return s;

}
