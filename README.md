# Soduku_Solver
Implements an algorithm to solve any Soduku puzzle

The code solve soduku puzzles and returns an integer array of size 9x9 containing the solution

# Algorithm
First it gets all the possible values of the empty cell. It does this by checking it's row, column and 3x3 subset square for values not contained in all three of those. This gives the possible values of an empty cell.<br/>
If cell has only one possible value, then the value is filled into that cell. <br/>
If all the empty cells are transversed and no cell with only one possible value is found, it then moves to a cell with 2 possible values. Fills in the first one and tries to solve the puzzle, If no solution is found, it then fills in the next possible value and tries to solve the puzzle. This process is repeated recursively till a solution is found

# Methods
int** SolveSoduku(int soduku[9][9])  - Returns a pointer to a 2D array with the solution to the input soduku. Note, the input must me in a valid format which is described below. <br/>
bool CheckIfValid(int soduku[9][9]) - Checks if the input soduku is valid. A <b>valid input</b> should be a 9x9 integer array with empty cells given a value 0 and non-empty cells given their appropriate value.<br/>
bool VerifySolution(int **solution) - Checks if a solution is valid. It checks if 1 to 9 can be found on every, row, column and 3x3 subset cells. <br/>
void PrintResult(int **result) - Prints out the result to nthe console in a soduku array format

# Usage
Always ensure the input is valid before solving the soduku. The input should be in a 9x9 integer array and all empty cells should be given a value of 0;

A sample usage in main is shown below:

int **result;

int sodukuProblem_1[9][9] =  {	  {0,0,0,2,6,0,7,0,1}, <br/>
                                  {6,8,0,0,7,0,0,9,0}, <br/>
                                  {1,9,0,0,0,4,5,0,0}, <br/>
                                  {8,2,0,1,0,0,0,4,0}, <br/>
                                  {0,0,4,6,0,2,9,0,0}, <br/>
                                  {0,5,0,0,0,3,0,2,8}, <br/>
                                  {0,0,9,3,0,0,0,7,4}, <br/>
                                  {0,4,0,0,5,0,0,3,6}, <br/>
                                  {7,0,3,0,1,8,0,0,0} };
				  
if (CheckIfValid(sodukuProblem)) { <br/>
		result = SolveSoduku(sodukuProblem);  <br/>
		if(VerifySolution(result)) <br/>
			PrintResult(result); <br/>
	}
  
This solves the soduku problem and Prints out the solution
