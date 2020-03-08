
compiler = mpiCC
FLAGS = -O3 

p3_files = Assignment2_driver.cpp MTS.cpp my_func.cpp pts.cpp




all:	p1_exe	

p3_exe: $(p3_files)
		$(compiler) $(FLAGS) $(p3_files) -o $@

clean:
		rm *_exe

