/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: September 14th, 2020
Description: Euler's Problem
What is the purpose of this file?
To sum the prime numbers including a below a given number
*/
#include <iostream>
#include <fstream>

using namespace std;

// Returns true if number is prime, false if not
bool isPrime(unsigned long INum) {
	// If divisible by a number, return false, else, return true
	for (int i = INum / 2; i > 1; i--) {
		if (INum % i == 0) {
			return false;
		}
	}
	return true;
}

// Runs through each number less than or equal to input, creating a running sum of prime numbers
int main(int argc, char* argv[]) {
	unsigned long num = stoul(argv[1]);
	unsigned long sum = 0;
	for (unsigned long i = num; i > 1; i--) {
		if (isPrime(i)) {
			sum += i;
		}
	}

	ofstream output;
	output.open("output1.txt");

	output << sum << endl;
	output.close(); 
}