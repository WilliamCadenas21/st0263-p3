# N-Queens with MPI + openMP

## Compile

To compile it simply go to the MPI directory and type make:

	$ cd {path of your local copy of the repository}/MPI
	$ make

The previous command will generate an executable called 'nqueensMPI'

## Run

To run the program simply type a command with the following structure:
	
	$ mpirun -np <number of processes> -f hosts_mpi nqueensMPI <number of queens>

e.g.

	$ mpirun -np 4 -f hosts_mpi nqueensMPI 8

The previous command will compute the number of solutions for 8-queens using 4 processes. Important: if needed change the IPs in hosts_mpi to match your nodes' IPs.

## Results

## Analysis

### Graphs
---

