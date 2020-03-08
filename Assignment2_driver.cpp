#include <iostream>
#include <cmath> 
#include <iomanip>
#include "pts.h"
#include "MTS.h"
#include "my_func.h"
#include "mpi.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	MPI::Init( argc, argv);
	double master=0;
	double tag=123;
	double num_cores=MPI::COMM_WORLD.Get_size();
	ofstream out_mid("Midpoint");
	ofstream out_trap("Trapezoid");
	ofstream out_simp("Simpson");
	
	
	for (int wave_vect=100; wave_vect <= 10000; wave_vect++)
	{
	    	double rank=MPI::COMM_WORLD.Get_rank();	
	  	double K= wave_vect;
		double len=floor(K/num_cores);
		double rem= int(K) % int(num_cores);
		double local_integral[3];
		local_integral[0]=0;
		local_integral[1]=0;
       		local_integral[2]=0;

		if (rank != num_cores - 1)
		{
			for (int i= len*rank + 1; i <= len*rank + len; i++)
			{
				double* output= MTS( my_func, K, 101, 0, M_PI, i);
				local_integral[0] += output[0];
				local_integral[1] += output[1];
				local_integral[2] += output[2];
			}
		}
	
		else if (rank == num_cores - 1)
		{
		    
	    		for (int i=len*rank +1; i <= len*rank + len + rem; i++)
			{
				double* output= MTS( my_func, K, 101, 0, M_PI, i);
				local_integral[0] += output[0];
				local_integral[1] += output[1];
				local_integral[2] += output[2];
			}
		}
	
		if ( rank != master)
		{
			MPI::COMM_WORLD.Send(local_integral, 3, MPI::DOUBLE, master, tag);	
		}
	
		else
		{
			double full_integral[3];
			full_integral[0]=local_integral[0];
			full_integral[1]=local_integral[1];
			full_integral[2]=local_integral[2];
			MPI::Status status;

			for (int source=1; source <= num_cores - 1; source++)
			{
				MPI::COMM_WORLD.Recv(local_integral, 3, MPI::DOUBLE, source, tag, status);
				full_integral[0] += local_integral[0];
				full_integral[1] += local_integral[1];
				full_integral[2] += local_integral[2];
			}

			out_mid  << setprecision(15) << full_integral[0] << endl;
		        out_trap <<  setprecision(15) << full_integral[1] << endl;
			out_simp << setprecision(15) << full_integral[2] << endl;

			if ( wave_vect % 1000 ==0)
			{
				cout << scientific << setprecision(15) << "The integral using the Midpoint Method for K= "
			   	 << wave_vect << " is "<< full_integral[0] << endl;

		        	cout << scientific << setprecision(15) << "The integral using the Trapezoidal Method for K= "
				<< wave_vect << " is "<< full_integral[1] << endl;

				cout << scientific << setprecision(15) << "The integral using the Simpson Method for K= "
			   	 << wave_vect << " is "<< full_integral[2] << endl;
			}
		}
	}
	out_mid.close();
	out_trap.close();
	out_simp.close();
	MPI::Finalize();
	return 0;
}
