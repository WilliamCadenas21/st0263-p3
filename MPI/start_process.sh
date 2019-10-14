# Compile process
mpiicpc -o -std=c++11 -qopenmp NqueensMPI nqueens_MPI_loop.cpp 

#Send work
qsub mpi_file
