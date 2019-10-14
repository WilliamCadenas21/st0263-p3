all: 
	mpiicpc -xMIC-AVX512 -std=c++11 -qopenmp -o NqueensMPI nqueens_MPI_loop.cpp 

queue:	all
	qsub mpi_file

clear:
	rm -rf mpi_file.*
	rm NqueensMPI