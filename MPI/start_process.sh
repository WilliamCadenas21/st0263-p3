#Clean space
rm -rf mpi_file.*
rm NqueensMPI

# Compile process
mpiicpc  -std=c++11 -qopenmp -o NqueensMPI nqueens_MPI_loop.cpp 

#Send work
qsub mpi_file
