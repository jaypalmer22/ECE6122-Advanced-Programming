/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: October 11, 2020
Description: 
Implementation of Sudoku Grid class which holds and can solve a single sudoku grid
*/

#include "SudokuGrid.h"


/* 
Purpose: Is the number already in the current column
@col: The current column
@num: The current number
@return: True if the number is present, false otherwise
*/
bool SudokuGrid::isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < 9; row++)
      if (gridElement[row][col] - '0' == num)
         return true;
   return false;
}

/* 
Purpose: Is the number already in the current row
@row: The current row
@num: The current number
@return: True if the number is present, false otherwise
*/
bool SudokuGrid::isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < 9; col++)
      if (gridElement[row][col] - '0' == num)
         return true;
   return false;
}

/* 
Purpose: Is the number already in the current box
@boxStartRow: Starting row of box
@boxStartCol: Starting column of box
@num: The current number
@return: True if the number is present, false otherwise
*/
bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (gridElement[row+boxStartRow][col+boxStartCol] - '0' == num)
            return true;
   return false;
}

/* 
Purpose: Find the first empty location and update row and column 
@row: The current row, updated to where the 0 is found
@col: The current col, updated to where the 0 is found
@return: True if a zero is found, false otherwise
*/
bool SudokuGrid::findEmptyPlace(int &row, int &col){ 
   for (row = 0; row < 9; row++)
      for (col = 0; col < 9; col++)
         if (gridElement[row][col] - '0' == 0) 
            return true;
   return false;
}

/* 
Purpose: Is the current spot a valid number 
@row: The current row
@col: The current col
@num: The current number
@return: True if valid, false otherwise
*/
bool SudokuGrid::isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
col - col%3, num);
}


/* 
Purpose: Main function for solving the current grid
@return: True if solved, false otherwise
*/
bool SudokuGrid::solve() {
	int row, col;
	if (!findEmptyPlace(row, col))
		return true;
	for (int num = 1; num <= 9; num++) {
		if (isValidPlace(row, col, num)) {
			gridElement[row][col] = num + '0';
			if (solve()) 
				return true;
			gridElement[row][col] = 0 + '0';
		}
	}
	return false;
}

/* 
Purpose: Read a grid from the input file and store its name and elements
@os: The file to read from
@gridIn: The current grid to set attributes
@return: The file
*/
fstream& operator>>(fstream& os, SudokuGrid& gridIn) {
	
	// Get grid name
	getline(os, gridIn.m_strGridName);
	string line;

	// Get elements and store in gridElement
	for (int i = 0; i < 9; i++) {
		getline(os, line);
		for (int j = 0; j < 9; j++) {
			gridIn.gridElement[i][j] = line[j];
		}
	}

	return os;
}

/* 
Purpose: Write a grid (name and elements) to the output file
@os: The file to write to
@gridIn: The current grid to write
@return: The file
*/
fstream& operator<<(fstream& os, const SudokuGrid& gridIn) {

	// Write the grid name
	os << gridIn.m_strGridName;

	// Write the elements
	for (int i = 0; i < 9; i++) {
		os << endl;
		for (int j = 0; j < 9; j++) {
			os << gridIn.gridElement[i][j];
		}	
	} 

	return os;
}


