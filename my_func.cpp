#include <iostream>
#include <cmath> 

using namespace std;

double my_func( double k_w, double pts)
{
	return cos(100*pts-k_w*sin(pts)); 
}
