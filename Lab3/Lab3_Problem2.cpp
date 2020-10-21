/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: October 11, 2020
Description: 
Find probability that ant will make his way to end of the maze
*/

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <chrono>


using namespace std;

int main(int argc, char* argv[]) {
	int runs;
	int size;
	try {
		// If the first flag is -N
		if (string(argv[1]) == "-N") {
			runs = stoi(argv[2]);
			size = stoi(argv[4]);
		// If the first flag is - g
		} else if (string(argv[1]) == "-g") {
			size = stoi(argv[2]);
			runs = stoi(argv[4]);
		// If neither flag is present
		} else {
			cout << "Invalid Parameters" << endl;
			return 0;
		}
		// cout << "Runs: " << runs << "Size: " << size << endl;
	// If there is command line exception
	} catch (exception& e) {
		cout << "Didn't specify parameters correctly" << endl;
		return 0;
	}

	// Initialize vars
	int count = 0;
	int x = 1;
	int y = 1;

	random_device rd;
	default_random_engine generator(rd());

	// chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	// Start omp parallel threads
	#pragma omp parallel shared (count, size) private(x, y) 
	{
		#pragma omp for nowait
		// Start for loop
		for (int i = 0; i < runs; ++i) {

			// Start at (1, 1)
			vector<pair<int, int>> vec;
			auto coord = make_pair(1, 1);
			vec.push_back(coord);

			while (true) {
				vector<pair<int, int>> valid;

				// Find all possible moves
				auto up = make_pair(x, y - 1);
				auto down = make_pair(x, y + 1);
				auto left = make_pair(x - 1, y);
				auto right = make_pair(x + 1, y);

				// Determine which moves are valid
				if (up.second > 0) {
					if (find(vec.begin(), vec.end(), up) == vec.end()) {
						valid.push_back(up);
					}
				}

				if (down.second <= size) {
					if (find(vec.begin(), vec.end(), down) == vec.end()) {
						valid.push_back(down);
					}
				}

				if (left.first > 0) {
					if (find(vec.begin(), vec.end(), left) == vec.end()) {
						valid.push_back(left);
					}
				}

				if (right.first <= size) {
					if (find(vec.begin(), vec.end(), right) == vec.end()) {
						valid.push_back(right);
					}
				}

				// If no valid moves, end
				if (valid.size() == 0) {
					x = 1;
					y = 1;
					break;
				}

				// Choose randomly from valid moves
				uniform_int_distribution<> distribution(1, valid.size());
				pair<int, int> move = valid[distribution(generator) - 1];

				// If finished, end
				if (move.first == size && move.second == size) {
					count++;
					x = 1;
					y = 1;
					break;
				}

				// Add the valid move
				vec.push_back(move);

				// Go to the valid move's point
				x = move.first;
				y = move.second;

			}
		}
	}
	/*
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2-t1);
	cout << time_span.count() << endl;
	*/

	// Successes / total runs
	double prob = (double)count / runs;

	//cout << fixed << setprecision(7) << prob << endl;

	// Output probability to file
	ofstream output;
	output.open("Lab3Prob2.txt");
	output << fixed << setprecision(7) << prob << endl;
	output.close();
	
}