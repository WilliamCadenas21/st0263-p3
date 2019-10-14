# Compile process
mpiicpc -o -std=c++11 NqueensMPI NqueensMPI.cpp 

#Send work
qsub mpi_file
