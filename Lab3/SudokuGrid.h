/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: October 11, 2020
Description: 
Definition of Sudoku Grid class which holds and can solve a single sudoku grid
*/

#pragma once
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

extern mutex outFileMutex;
extern mutex inFileMutex;
extern fstream outFile;
extern fstream inFile;

/* The functions to actually solve the sudoku puzzle were obtained from 
https://www.tutorialspoint.com/sudoku-solver-in-cplusplus 
Includes:
isPresentInCol(int, int)
isPresentInRow(int, int)
isPresentInBox(int, int, int)
findEmptyPlace(int, int)
isValidPlace(int, int, int)
solve()
*/
class SudokuGrid {

private: 
	// Name of current grid object
	string m_strGridName;

	// Elements in the grid
	unsigned char gridElement[9][9];

public:
	
	// Solving sudoku
	bool isPresentInCol(int col, int num);
	bool isPresentInRow(int row, int num);
	bool isPresentInBox(int boxStartRow, int boxStartCol, int num);
	bool findEmptyPlace(int &row, int &col);
	bool isValidPlace(int row, int col, int num);
	bool solve();

	// Operator overload for reading and writing to/from file
	friend fstream& operator>>(fstream& os, SudokuGrid& gridIn);
	friend fstream& operator<<(fstream& os, const SudokuGrid& gridIn);
	
};
