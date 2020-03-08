#include <iostream> 
using namespace std;

// Returns grid points from start to end in increments of (end-start)/wave_num, 
// splits full interval into i evenly spaced sub-intervals
double* x_vals(double start, double end, double wave_num, int n, double i)
{
    	double* vals=new double[n+1];
	double w= (end - start)/ wave_num;
	double init= start + (i-1) * w ;

	for (int j=0; j <= n; j++)
	{
		vals[j] = init + j*w/double(n); 
	}
	return vals;
}


