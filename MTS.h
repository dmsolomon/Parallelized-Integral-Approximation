#ifndef MTS_h
#define MTS_h

double * MTS( double (*func)(double,double), double w_n, int q_n,
		double start, double end, double i);

#endif
