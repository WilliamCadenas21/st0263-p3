
#include <iostream>
#include <vector>

using namespace std;
int solve_nqs(int);
bool check_position(vector<int>&,int);


int main(int argc, char* argv[]){

    int N =stoi(argv[1]);
    int solutions_number =  solve_nqs(N);

    cout << "Total combinations ->" << solutions_number << endl;

    return 0;
}


int solve_nqs(int N){
    int solutions_counter = 0;
    int actual_col = 0;
    bool is_valid = false;

    vector<int> flatted_matrix(N,-1);
    // While true.
    for(;;){
        // Stop condition -> End reached
        if (actual_col < 0){
            break;
        }

        // I found a solution due to I fill all columns
        if (actual_col == N){
            solutions_counter ++;
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

    return solutions_counter;
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
