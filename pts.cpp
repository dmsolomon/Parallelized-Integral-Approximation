#include <iostream> 
using namespace std;

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


