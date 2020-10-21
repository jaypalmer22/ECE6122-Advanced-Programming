/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: October 9, 2020
Description: 
Solve optimization problem z = (e^X1 + X2)^2 + 3(1 - X3)^2
*/

#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <random>
#include <chrono>


using namespace std;

/* 
Purpose: Main function to perform optimization
*/
int main(int argc, char* argv[]) {
	int runs = stoi(argv[1]);
	double X1, X2, X3, x1, x2, x3, z, max_z;

	// Initialize random dist
	random_device rd;
	default_random_engine generator(rd());
	uniform_real_distribution<double> dist1(0.0, 1.0);
	uniform_real_distribution<double> dist2(0.0, 2.0);
	uniform_real_distribution<double> dist3(2.0, 3.0);

	//chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	
	// Start omp parallel
	#pragma omp parallel 
	{
		#pragma omp for reduction (max: max_z) nowait
		for (int i = 0; i < runs; ++i) {
		
			// Pull random number for x1, x2, x3
			x1 = dist1(generator);
			x2 = dist2(generator);
			x3 = dist3(generator);

			// Calculate z
			z = pow(exp(x1) + x2, 2) + 3 * pow(1 - x3, 2);

			// If z is greater than previous, set max_z to max
			if (z > max_z) {
				max_z = z;
				X1 = x1;
				X2 = x2;
				X3 = x3;
			}
		}
	}
	
	/*
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2-t1);
	cout << time_span.count() << endl;
	*/
	
	// Open output file
	ofstream output;
	output.open("Lab3Prob3.txt");

	// cout << "X1: " << X1 << " X2: " << X2 << " X3: " << X3 << " max_z: " << max_z << endl;

	// Write to output file
	output << fixed << setprecision(15);
	output << "X1: " << X1 << endl;
	output << "X1: " << X2 << endl;
	output << "X1: " << X3;
	output.close();
}