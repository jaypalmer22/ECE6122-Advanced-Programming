/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: September 14th, 2020
Description: Collatz Problem
What is the purpose of this file?
To sum the numbers in a given collatz sequence
*/
#include <iostream>
#include <fstream>

using namespace std;

// Solves collatz sequence and adds each number (num) to running sum (&total)
void collatz(unsigned long &total, unsigned long num) {
	while (num > 1) {
		// If even, n/2 else, 3 * n + 1
		if (num % 2 == 0) {
			num = num / 2;
		} else {
			num = 3 * num + 1;
		}
		total += num;
	}
}

// Main code to give correct parameters to collatz function
int main(int argc, char* argv[]) {
	// convert string to unsigned long
	unsigned long num = stoul(argv[1]);
	unsigned long sum = num;

	if (num > 1) {
		collatz(sum, num);
	}

	ofstream output;
	output.open("output2.txt");

	output << sum << endl;
	output.close(); 
}