/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: October 11, 2020
Description: 
Main file to take in files and make calls to grid class
*/

#include <vector>
#include <thread>
#include "SudokuGrid.h"


// Definition of Mutex's and files
mutex outFileMutex;
mutex inFileMutex;
fstream outFile;
fstream inFile;

/* 
Purpose: Create a new grid and call the operator overload functions to read/write
*/
void solveSudokuPuzzles() {

	do {
		SudokuGrid grid;

		// Read from file into grid object
		inFileMutex.lock();
		inFile >> grid;
		inFileMutex.unlock();

		// Solve the puzzle
		grid.solve();

		// Write solution to output file
		outFileMutex.lock();
		outFile << grid << endl;
		outFileMutex.unlock();

	} while (inFile.peek() != EOF);
	
}

/* 
Purpose: Main function to open/cose files and spawn threads to solve puzzles
*/
int main(int argc, char* argv[]) {

	// Open files
	inFile.open(argv[1], fstream::in);

	if (!inFile.is_open()) {
		cout << "Invalid input file" << endl;
		return 0;
	}
		
	outFile.open("Lab3Prob1.txt", fstream::out);

	int numThreads = thread::hardware_concurrency();
	vector<thread> threads;

	// Spawn threads
	for (int t = 0; t < numThreads - 1; t++) {
		threads.push_back(thread(solveSudokuPuzzles));
	}

	// Wait for all threads
	for (auto& th : threads) {
		th.join();
	}

	// Close files
	inFile.close();
	outFile.close();
}