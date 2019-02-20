/*Sodoku_AI.cpp 

Description: Solves soduku puzzles using Depth first search with heuristics of number of possible cell values
	     Implement using recursions

Author:Chinedu Isaiah
	   cjude32@yahoo.com



*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

//fuction prototype
int** SolveSoduku(int soduku[9][9]);

/* Checks if the inputs are in the correct format
** Returns true if they are in the right format
** Otherwise returns false
*/
bool CheckIfValid(int soduku[9][9]) {
	int frequency[10];
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			if (soduku[row][col] < 0 || soduku[row][col] > 9)
				return false;
		}
	}
	
	return true;
}

/* Puts one of the possible values of an empty soduku cell into the cell
** Then calls the solve soduku function
*/
int** ModifyAndSolveSoduku(int soduku[9][9], int row, int col, int value) {
	soduku[row][col] = value;
	return SolveSoduku(soduku);
}

/* Get's a soduku problem in the specified format
** returns null if there is no solution
** otherwise returns a solution
*/
int** SolveSoduku(int soduku[9][9]) {

	vector<int> cellPossibleValues[81];
	bool frequency[10];
	int possibleValues,value;
	int cellsToBeFilled = 0;
	int checkcellsToFill;
	int **solution;
	int **intermediateSolution;
	int sodukuClone[9][9];
	int rowStartIndex;
	int colStartIndex;

	//find number of empty cells
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			if (soduku[row][col] == 0)
				++cellsToBeFilled;
		}
	}
	

	// loop till all cells are filled
	while (cellsToBeFilled > 0) {
		checkcellsToFill = cellsToBeFilled;
		
		//clear vector of possible values for all cells
		for (int row = 0; row < 9; ++row) {
			for (int col = 0; col < 9; ++col) {
				cellPossibleValues[(row * 9) + col].clear();
			}
		}
		
		for (int row = 0; row < 9; ++row) {
			for (int col = 0; col < 9; ++col) {
				
				// Search for possible values if cell is empty
				if (soduku[row][col] == 0) {
					// set all values in frequency array to false
					for (int index = 1; index < 10; ++index) {
						frequency[index] = false;
					}
					//set the index values of other cells on same column to true
					for (int index = 0; index < 9; ++index) {
						if (index == row)
							continue;
						else
							frequency[soduku[index][col]] = true;
					}
					//set the index values of other cells on same row to true
					for (int index = 0; index < 9; ++index) {
						if (index == col)
							continue;
						else
							frequency[soduku[row][index]] = true;
					}
					// set the index values of other cells in the 3x3 subset cells to true
					rowStartIndex = (row / 3) * 3;
					colStartIndex = (col / 3) * 3;
					for (int rowIndex = 0; rowIndex < 3; ++rowIndex) {
						for (int colIndex = 0; colIndex < 3; ++colIndex) {
							if (rowIndex == row % 3 && colIndex == col % 3)
								continue;
							else 
								frequency[soduku[rowStartIndex + rowIndex][colStartIndex + colIndex]] = true;			
						}
					}
					possibleValues = 0;
					//Add all possible values of empty cell to the cell vector
					for (int index = 1; index < 10; ++index) {
						if (!frequency[index]){
							++possibleValues;
							value = index;
							cellPossibleValues[(row * 9) + col].push_back(index);
							}
					}
					// Return if no value satisfies the constraints for an empty cell
					// In the case, no solution is possible
					if (possibleValues == 0) {
						return NULL;
					}
					// If a cell has only one possible value, set cell to that value
					else if (possibleValues == 1) {
						soduku[row][col] = value;
						--cellsToBeFilled;
					}
				}
			}
		}
		
		/* Code if no empty cell has 1 possible value
		** That is when every empty cell has at least 2 possible values
		*/
		if (cellsToBeFilled == checkcellsToFill) {
			// start from cells with 2 possible states
			for (int size = 2; size < 8; ++size) {
				for (int row = 0; row < 9; ++row) {
					for (int col = 0; col < 9; ++col) {
						if (cellPossibleValues[(row * 9) + col].size() == size) {

							// Replace the cell with each of the possible values iteratively and solve
							while (!cellPossibleValues[(row * 9) + col].empty()) {
								int val = cellPossibleValues[(row * 9) + col].back();
								cellPossibleValues[(row * 9) + col].pop_back();
								
								// Copies the existing soduku problem
								memcpy(sodukuClone, soduku, 81 * sizeof(int));

								// Replaces the cell with one it's possible values and then try to solve the soduku again
								intermediateSolution = ModifyAndSolveSoduku(sodukuClone, row, col, val);
								if (intermediateSolution != NULL)
									return intermediateSolution;
							}
							// return null if none of the possible values of a cell leads to a solution
							return NULL;
						}
					}
				}
			}
		}
	}
	// Create a pointer to the solved array and returns it
	
	solution = new int*[9];
	for (int row = 0; row < 9; ++row) {
		solution[row] = new int[9];
		for (int col = 0; col < 9; ++col) {
			solution[row][col] = soduku[row][col];
		}
	}
	return solution;
}

//Prints the result after getting a solution
void PrintResult(int **result) {
	if (result == NULL)
		return;
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			cout << result[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;

}

/* Checks if all rows and columns contain 1 to 9
** Returns true if this condition is satisfied otherwise false
*/
bool VerifySolution(int **solution) {
	if (solution == NULL)
		return false;
	//stores the frequency of each index in a row or column
	int frequency[10];

	// Checks if numbers 1 to 9 occur on all rows else returns false
	for (int row = 0; row < 9; ++row) {
		for (int index = 0; index < 10; ++index) {
			frequency[index] = 0;
		}
		for(int col = 0; col < 9; ++col){
			++frequency[solution[row][col]];
		}
		for (int index = 1; index < 10; ++index) {
			if (frequency[index] != 1)
				return false;
		}

	}


	// Checks if numbers 1 to 9 occur on all columns else returns false
	for (int col = 0; col < 9; ++col) {
		for (int index = 0; index < 10; ++index) {
			frequency[index] = 0;
		}
		for (int row = 0; row < 9; ++row) {
			++frequency[solution[row][col]];
		}
		for (int index = 1; index < 10; ++index) {
			if (frequency[index] != 1)
				return false;
		}
	}

	// Check if numbers 1 to 9 occur in a 3x3 Subset
	for (int rowSubset = 0; rowSubset < 3; ++rowSubset) {
		for (int colSubset = 0; colSubset < 3; ++colSubset) {
			for (int index = 0; index < 10; ++index) {
				frequency[index] = 0;
			}
			for (int row = 0; row < 3; ++row) {
				for (int col = 0; col < 3; ++col) {
					++frequency[solution[(rowSubset*3)+row][(colSubset*3)+ col]];
				}
			}
			for (int index = 1; index < 10; ++index) {
				if (frequency[index] != 1)
					return false;
			}
		}
	}
	return true;
}
int main(int argc, char* argv[])
{
	// Unit test
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

    return 0;
}

//Test if the method checkIfValid detects when inputs are in wrong format
TEST(Soduku_AI_Test, checkIfValid) {
	int validInput[9][9] = { { 0,0,0,2,6,0,7,0,1 },
	{ 6,8,0,0,7,0,0,9,0 },
	{ 1,9,0,0,0,4,5,0,0 },
	{ 8,2,0,1,0,0,0,4,0 },
	{ 0,0,4,6,0,2,9,0,0 },
	{ 0,5,0,0,0,3,0,2,8 },
	{ 0,0,9,3,0,0,0,7,4 },
	{ 0,4,0,0,5,0,0,3,6 },
	{ 7,0,3,0,1,8,0,0,0 } };

	int invalidInput[9][9] = { { 0,0,0,2,6,0,7,0,1 },
	{ 6,8,-1,0,7,0,0,9,0 },
	{ 1,9,0,0,0,4,5,0,0 },
	{ 8,2,0,1,0,0,0,4,0 },
	{ 0,0,4,6,0,2,9,0,0 },
	{ 0,5,0,0,0,3,0,2,8 },
	{ 0,0,9,3,0,0,0,7,4 },
	{ 0,4,0,0,5,0,0,3,6 },
	{ 7,0,3,0,1,8,0,0,0 } };

	EXPECT_TRUE(CheckIfValid(validInput));
	EXPECT_FALSE(CheckIfValid(invalidInput));

}

// Test for VerifySolution method that Checks if a soduku solution satisfies all constraints

TEST(Soduku_AI_Test, VerifySolution) {

	int **solutionUnderTest;
	solutionUnderTest = new int*[9];

	int validSolution[9][9] = { { 4,3,5,2,6,9,7,8,1 },
	{ 6,8,2,5,7,1,4,9,3 },
	{ 1,9,7,8,3,4,5,6,2 },
	{ 8,2,6,1,9,5,3,4,7 },
	{ 3,7,4,6,8,2,9,1,5 },
	{ 9,5,1,7,4,3,6,2,8 },
	{ 5,1,9,3,2,6,8,7,4 },
	{ 2,4,8,9,5,7,1,3,6 },
	{ 7,6,3,4,1,8,2,5,9 } };

	for (int i = 0; i < 9; ++i) {
		solutionUnderTest[i] = new int[9];
		for (int j = 0; j < 9; ++j) {
			solutionUnderTest[i][j] = validSolution[i][j];
		}
	}
	EXPECT_TRUE(VerifySolution(solutionUnderTest));
	int invalidSolution1[9][9] = { { 4,3,5,2,6,9,7,8,1 },
	{ 6,8,2,5,7,1,4,9,3 },
	{ 1,9,7,8,3,4,5,6,2 },
	{ 8,2,6,1,9,5,3,4,7 },
	{ 3,7,4,8,6,2,9,1,5 },
	{ 9,5,1,7,4,3,6,2,8 },
	{ 5,1,9,3,2,6,8,7,4 },
	{ 2,4,8,9,5,7,1,3,6 },
	{ 7,6,3,4,1,8,2,5,9 } };

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			solutionUnderTest[i][j] = invalidSolution1[i][j];
		}
	}
	EXPECT_FALSE(VerifySolution(solutionUnderTest));

	int invalidSolution2[9][9] = { { 4,3,5,2,6,9,7,8,1 },
	{ 6,8,2,5,7,1,4,9,3 },
	{ 1,9,7,8,3,4,5,6,2 },
	{ 8,2,6,1,9,5,3,4,5 },
	{ 3,7,4,6,8,2,9,1,7 },
	{ 9,5,1,7,4,3,6,2,8 },
	{ 5,1,9,3,2,6,8,7,4 },
	{ 2,4,8,9,5,7,1,3,6 },
	{ 7,6,3,4,1,8,2,5,9 } };

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			solutionUnderTest[i][j] = invalidSolution2[i][j];
		}
	}
	EXPECT_FALSE(VerifySolution(solutionUnderTest));
	free(solutionUnderTest);
}

//Test for SolveSoduku method for different levels of difficulty
TEST(Soduku_AI_Test, SolveSoduku) {
	int **result;

	//Difficult: Easy
	int sodukuProblem_1[9][9] = { { 0,0,0,2,6,0,7,0,1 },
					{ 6,8,0,0,7,0,0,9,0 },
					{ 1,9,0,0,0,4,5,0,0 },
					{ 8,2,0,1,0,0,0,4,0 },
					{ 0,0,4,6,0,2,9,0,0 },
					{ 0,5,0,0,0,3,0,2,8 },
					{ 0,0,9,3,0,0,0,7,4 },
					{ 0,4,0,0,5,0,0,3,6 },
					{ 7,0,3,0,1,8,0,0,0 } };
	//Difficulty: Intermediate 
	int sodukuProblem_2[9][9] = { { 0,2,0,6,0,8,0,0,0 },
					{ 5,8,0,0,0,9,7,0,0 },
					{ 0,0,0,0,4,0,0,0,0 },
					{ 3,7,0,0,0,0,5,0,0 },
					{ 6,0,0,0,0,0,0,0,4 },
					{ 0,0,8,0,0,0,0,1,3 },
					{ 0,0,0,0,2,0,0,0,0 },
					{ 0,0,9,8,0,0,0,3,6 },
					{ 0,0,0,3,0,6,0,9,0 } };

	//Difficulty: Hard
	int sodukuProblem_3[9][9] = { { 0,0,0,6,0,0,4,0,0 },
					{ 7,0,0,0,0,3,6,0,0 },
					{ 0,0,0,0,9,1,0,8,0 },
					{ 0,0,0,0,0,0,0,0,0 },
					{ 0,5,0,1,8,0,0,0,3 },
					{ 0,0,0,3,0,6,0,4,5 },
					{ 0,4,0,2,0,0,0,6,0 },
					{ 9,0,3,0,0,0,0,0,0 },
					{ 0,2,0,0,0,0,1,0,0 } };

	//Difficulty: Very Hard
	int sodukuProblem_4[9][9] = { { 0,2,0,0,0,0,0,0,0 },
					{ 0,0,0,6,0,0,0,0,3 },
					{ 0,7,4,0,8,0,0,0,0 },
					{ 0,0,0,0,0,3,0,0,2 },
					{ 0,8,0,0,4,0,0,1,0 },
					{ 6,0,0,5,0,0,0,0,0 },
					{ 0,0,0,0,1,0,7,8,0 },
					{ 5,0,0,0,0,9,0,0,0 },
					{ 0,0,0,0,0,0,0,4,0 } };

	result = SolveSoduku(sodukuProblem_1);
	EXPECT_TRUE(VerifySolution(result));

	result = SolveSoduku(sodukuProblem_2);
	EXPECT_TRUE(VerifySolution(result));

	result = SolveSoduku(sodukuProblem_3);
	EXPECT_TRUE(VerifySolution(result));

	result = SolveSoduku(sodukuProblem_4);
	EXPECT_TRUE(VerifySolution(result));

	free(result);
}

