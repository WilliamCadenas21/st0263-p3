
#include <omp.h>
#include "mpi.h"
#include <iostream>
#include <vector>

using namespace std;
int solve_nqs(int,int,int);
bool check_position(vector<int>&,int);


int main(int argc, char* argv[]){

    MPI_Init (&argc, &argv); // Initialize MPI Env
    int rank, size, namelen;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    MPI_Comm_rank (MPI_COMM_WORLD, &rank); // ID of current process
    MPI_Get_processor_name(name, &namelen); // Hostname of node
    MPI_Comm_size (MPI_COMM_WORLD, &size); // Number of processes
    printf("Hello World from rank %d runnung on %s! \n", rank, name);
    if (rank == 0) printf("MPI Wold size = %d processes \n", size);

    // Vector unit -> [0] Start position [1] end position
    
    vector<uint32_t> ranges_local;
    // If i'm the master I'll send the ranges to my slaves
    int N =stoi(argv[1]);


    if (rank == 0) {

        vector<uint32_t> ranges;

        
        // The slop is the number of queens divided the number of cores.
        int slop = (int) N/size;

        // Defined the limits 
        int left_limit = 0;
        int right_limit = 0;

        printf("The slop is %d, N is %d, The size is %d \n", slop, N, size);

        for(int i =0; i < size; i++){

            ranges.push_back(left_limit);

            right_limit = left_limit + slop;

            if (right_limit >= N) right_limit = N;

            ranges.push_back(right_limit);

            left_limit = right_limit;
            
            MPI_Send(&ranges[0], 2, MPI_INT, i, 0 ,MPI_COMM_WORLD);
        }
        printf("All data have been seended ");
    }


    ranges_local.resize(2);

    // Get params
    MPI_Recv(&ranges_local[0], 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    printf("Proccess %d has %d - %d", rank,ranges_local[0],ranges_local[1])

    // Calculated solutions
    int solutions_number_local =  solve_nqs(N,ranges_local[0],ranges_local[1] );
    
    // send solutions tag = 1 -> Solutions tag, to master

    printf("Procces %d has finished the job", rank);

    MPI_Send(&solutions_number_local, 1, MPI_INT, 0, 1 ,MPI_COMM_WORLD);

    if (rank == 0){
        
        int global_sum_up = 0;
        int local_sum_up;
        printf ("Master start receiving results");
        for(int i =0; i < size; i++){
            MPI_Recv(&local_sum_up, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            global_sum_up = global_sum_up + local_sum_up;
            printf ("Master received %d", rank);
        }
        cout << "Total combinations ->" << global_sum_up << endl;
    }
    
    MPI_Finalize(); //Terminate MPI Env

    return 0;
}


int solve_nqs(int N, int lowerBound, int upperBound){

    int solutions_counter_global = 0;

    #pragma omp parallel
    {
        int solutions_counter_local = 0;
        bool is_valid = false;
        int actual_col = 1;
        vector<int> flatted_matrix(N,-1);

        #pragma omp for
        for (int iterator = lowerBound; iterator < upperBound; iterator++ ){
            flatted_matrix[0] = iterator; 
            actual_col = 1;
            for(;;){
            // Stop condition -> End reached
                if (actual_col == 0){
                    break;
                }

                // I found a solution due to I fill all columns
                if (actual_col == N){
                    solutions_counter_local ++;
                    // Go back to the final col to continue finding solutions
                    actual_col --;
                }
                // Flag that indicates whethere we find a corret combination per column
                is_valid = false;
                
                // Iterate over the row finding the position
                // were the queen fit
                for (int actual_pos = flatted_matrix[actual_col]; actual_pos < (N -1 ); actual_pos++){
                    flatted_matrix[actual_col] = actual_pos + 1;
                    // It's a valid position
                    // Advance to the next column
                    if ( check_position(flatted_matrix,actual_col) ){
                        is_valid= true;
                        break;
                    }
                    
                }
                // If we find a valid position then move forward (Column)
                if(is_valid){
                    actual_col ++;
                }else{
                    // Backtracking. Go back
                    flatted_matrix[actual_col] = -1;
                    actual_col--;
                }
            }
        }

        #pragma omp atomic
            solutions_counter_global += solutions_counter_local;

    }
    return solutions_counter_global;
}

bool check_position(vector<int>& flatted_matrix, int actual_col){
    int actual_pos = flatted_matrix[actual_col];
    int upper_diagonal = actual_pos;
    int lower_diagonal = actual_pos;
    int center = actual_pos;

    for (int column_to_check = actual_col - 1; column_to_check >= 0 ; column_to_check--){
        upper_diagonal = upper_diagonal - 1;
        lower_diagonal = lower_diagonal + 1;

        if (flatted_matrix[column_to_check] == upper_diagonal){
            return false;
        }

        if (flatted_matrix[column_to_check] == lower_diagonal){
            return false;
        }

        if (flatted_matrix[column_to_check] == center){
            return false;
        }
    }

    return true;

}
