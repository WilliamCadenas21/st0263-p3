/* Main Algorithm taken from:

   https://www.geeksforgeeks.org/printing-solutions-n-queen-problem/
*/

#include <iostream>
#include <vector>

using namespace std;

void solvenq(vector<vector<int>>&);
int solvenqaux(vector<vector<int>>&, int);
bool issafe(vector<vector<int>>, int, int);
void printsol(vector<vector<int>>);

int main(int argc, char* argv[])
{
  if (argc < 2) {
    cout << "Usage: nqueens_serial number (number > 1)" << endl;
    return 1;
  }

  int N = stoi(argv[1]);

  if (N < 1) {
    cout << "Usage: nqueens_serial number (number > 1)" << endl;
    return 2;
  }

  vector<vector<int>> board(N, vector<int>(N, 0));

  solvenq(board);

  return 0;
}

/* Solve nqueens */
void solvenq(vector<vector<int>>& board)
{
  cout << solvenqaux(board, 0) << endl;
}

/* Recursive utility function to solve the problem */
int solvenqaux(vector<vector<int>>& board, int col)
{
  static int nsols = 0;
  /* All queens are placed */
  if (col >= board.size()) {
    // printsol(board);
    nsols++;
    return nsols;
  }

  /* Consider this column and try placing this queen
     in all rows one by one */
  for (int i = 0; i < board.size(); i++) {
    if (issafe(board, i, col)) {
      board[i][col] = 1;

      solvenqaux(board, col+1);

      board[i][col] = 0;
    }
  }
  // Papi, por aca no fue
  return nsols;
}

/* Check if a queen can be placed on board[row][col].
   Only need to check for attacking queens to the left
   since those are the ones already in place.*/
bool issafe(vector<vector<int>> board, int row, int col)
{
  int i, j;

  /* Check this row on the left side */
  for (i = 0; i < col; i++)
    if (board[row][i])
      return false;

  /* Check the upper diagonal on the left side */
  for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return false;

  /* Check the lower diagonal on the left side */
  for (i = row, j = col; j >= 0 && i < board.size(); i++, j--)
    if (board[i][j])
      return false;

  return true;
}

/* Print the solution*/
void printsol(vector<vector<int>> board)
{
  static int k = 1;
  cout << k << " -- " << endl;
  for (auto i : board) {
    for (auto j : i) {
      cout << " " << j << " ";
    }
    cout << endl;
  }
  cout << endl;
  k++;
}
