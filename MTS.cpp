#include <iostream>
#include <cmath> 
#include "pts.h"

using namespace std; 

//Returns the approximate integral using Midpoint, Trapezoid and Simpson rules
// given a function to integrate, wavevector w and number of rectangles
double * MTS( double (*func)(double,double), double w_n, int q_n,
		double start, double end, double i)
{
	double M=0;
	double T=0;
	double S=0;
	double*	pts=x_vals(start, end, w_n, q_n ,i);
	double* out= new double[3];


	for (int j=1; j <= q_n; j++)
	{
	    	double len= pts[j] - pts[j-1];
		double mpts= ( pts[j] + pts[j-1] )/2;
		M += (*func)(w_n, mpts) * len ;
		T += .5 * ((*func)(w_n, pts[j-1]) + (*func)(w_n, pts[j])) * len;
	}

	S = 2*M/3 + T/3;
	out[0]=M;
	out[1]=T;
	out[2]=S;
	return out;
}

