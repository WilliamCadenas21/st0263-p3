CXX=mpiicpc
CXXFLAGS=-o -std=c++11 -qopenmp -xMIC-AVX512
LDFLAGS=-qopenmp

all: 
	$(CXX) $(LDFLAGS) NqueensMPI nqueens_MPI_loop.cpp

queue:	all
	qsub mpi_file