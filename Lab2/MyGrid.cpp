/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: September 28, 2020
Description: Implementation of grid class functions
What is the purpose of this file?
To add infrastructure for grids to perform operations on themselves and each other
*/

#include <iostream>
#include "MyGrid.h"

/* 
Purpose: Load grid from text file and create class for it
@filename: Input filename
@return: True if file was valid and grid was transferred, false if otherwise
*/
bool MyGrid::loadGridFromFile(const string& filename) {
	
	// Open the input file
	ifstream inFile;
	inFile.open(filename);
	string word;

	long rows, cols;
	if (inFile.is_open()) {

		// Read corner location and size, and set to grid members
		inFile >> myX;
		inFile >> myY;

		inFile >> rows;
		inFile >> cols;

		// Read elements from file, set to grid elements
		for (int i = 0; i < rows; i++) {
			vector<long> v1;
			for (int j = 0; j < cols; j++){
				inFile >> word;
				v1.push_back(stol(word));
			}
			gridElements.push_back(v1);
		}

	} else {
		return false;
	}

	return true;

}

/* 
Purpose: Convert all entries in the grid to 0
*/
void MyGrid::zeroOutGrid() {
	for (int i = 0; i < gridElements.size(); i++) {
		fill(gridElements[i].begin(), gridElements[i].end(), 0);
	}
}

/* 
Purpose: Return the number of rows in the grid
@return: The number of rows in the grid
*/
long MyGrid::getNumRows() const {
	return static_cast<long>(gridElements.size());
}

/* 
Purpose: Return the number of columns in the grid
@return: The number of columns in the grid
*/
long MyGrid::getNumCols() const {
	return static_cast<long>(gridElements[0].size());
}

/* 
Purpose: Add two grids together (add overlapping elements and match largest extent)
@rhs: The grid on the right hand side of the addition (gridA + gridB) would be gridB
@return: The result of adding two grids together
*/
MyGrid MyGrid::operator+(MyGrid const& rhs) const {
	
	// If no elements in grid, return full grid
	if (gridElements.size() == 0) {
		return rhs;
	}
	if (rhs.gridElements.size() == 0) {
		return *this;
	}

	// Initialize new grid top left and bottom right locations
	MyGrid add;
	add.myX = min(myX, rhs.myX);
	add.myY = max(myY, rhs.myY);
	long rightX = max(rhs.myX + rhs.gridElements[0].size(), myX + gridElements[0].size()) - 1;
	long rightY = min(rhs.myY - rhs.gridElements.size(), myY - gridElements.size()) + 1;
	
	// Create correct dimensions for new grid
	add.gridElements.resize(add.myY - rightY + 1);
	for (int i = 0; i <= add.myY - rightY; i++) {
		add.gridElements[i].resize(rightX - add.myX + 1);
		
	}
	
	// Add this grids elements into new grid
	for (int j = 0; j < gridElements.size(); j++) {
		for (int k = 0; k < gridElements[0].size(); k++) {
			add.gridElements[add.myY - myY + j][myX - add.myX + k] = gridElements[j][k];
		}
	}

	// Add rhs grids elements into new grid and add to existing elements
	for (int x = 0; x < rhs.gridElements.size(); x++) {
		for (int y = 0; y < rhs.gridElements[0].size(); y++) {
			add.gridElements[add.myY - rhs.myY + x][rhs.myX - add.myX + y] += rhs.gridElements[x][y];
		}
	}
	
	return add;
}

/* 
Purpose: Subtract one grid from another (subtract overlapping elements and match largest extent)
@rhs: The grid on the right hand side of the addition (gridA - gridB) would be gridB
@return: The result of subtracting one grid from another
*/
MyGrid MyGrid::operator-(MyGrid const& rhs) const {
	
	// If no elements in grid, return full grid
	if (gridElements.size() == 0) {
		return rhs;
	}
	if (rhs.gridElements.size() == 0) {
		return *this;
	}

	// Initialize new grid top left and bottom right locations
	MyGrid add;
	add.myX = min(myX, rhs.myX);
	add.myY = max(myY, rhs.myY);
	long rightX = max(rhs.myX + rhs.gridElements[0].size(), myX + gridElements[0].size()) - 1;
	long rightY = min(rhs.myY - rhs.gridElements.size(), myY - gridElements.size()) + 1;
	
	// Create correct dimensions for new grid
	add.gridElements.resize(add.myY - rightY + 1);
	for (int i = 0; i <= add.myY - rightY; i++) {
		add.gridElements[i].resize(rightX - add.myX + 1);
		
	}
	
	// Add this grids elements into new grid
	for (int j = 0; j < gridElements.size(); j++) {
		for (int k = 0; k < gridElements[0].size(); k++) {
			add.gridElements[add.myY - myY + j][myX - add.myX + k] = gridElements[j][k];
		}
	}

	// Subtract rhs grids elements into new grid and subtract to existing elements
	for (int x = 0; x < rhs.gridElements.size(); x++) {
		for (int y = 0; y < rhs.gridElements[0].size(); y++) {
			add.gridElements[add.myY - rhs.myY + x][rhs.myX - add.myX + y] -= rhs.gridElements[x][y];
		}
	}
	
	return add;
}

/* 
Purpose: Add a long on the right side to every element in the grid
@plus: The long-typed number to add to the grid
@return: The result of adding a long to each element in the grid
*/
MyGrid MyGrid::operator+(long const& plus) const {
	MyGrid add = *this;

	// Add long-typed number to all elements
	for (int i = 0; i < gridElements.size(); i++) {
		for (int j = 0; j < gridElements[0].size(); j++) {
			add.gridElements[i][j] += plus;
		}
	}

	return add;
} 

/* 
Purpose: Add a long on the left side to every element in the grid
@lhs: The long-typed number to add to the grid
@rhs: The grid to add the number to
@return: The result of adding a long to each element in the grid
*/
MyGrid operator+(long const& lhs, MyGrid const& rhs) {
	MyGrid add = rhs;

	// Add long-typed number to all elements
	for (int i = 0; i < rhs.gridElements.size(); i++) {
		for (int j = 0; j < rhs.gridElements[0].size(); j++) {
			add.gridElements[i][j] += lhs;
		}
	}

	return add;
}

/* 
Purpose: Add two grids together and store the result in the first grid
@rhs: The grid on the right hand side of the addition (gridA + gridB) would be gridB
@return: The updated left hand grid (after adding)
*/
MyGrid& MyGrid::operator+=(MyGrid const& rhs) {
	
	// Call operator+
	*this = *this + rhs;

	return *this;
}

/* 
Purpose: Add one to every element in a grid, pre-increment
@return: The original grid with each element having +1
*/
MyGrid& MyGrid::operator++() {
	
	// Add one to each element
	for (int i = 0; i < gridElements.size(); i++) {
		for (long & elem : gridElements[i]) {
			elem++;
		}
	}

	// Return changed object (pre-increment)
	return *this;
}

/* 
Purpose: Add one to every element in a grid, post-increment
@return: A copy of the original grid, before adding one
*/
MyGrid MyGrid::operator++(int) {
	MyGrid add = *this;

	// Add one to each element
	for (int i = 0; i < gridElements.size(); i++) {
		for (long & elem : gridElements[i]) {
			elem++;
		}
	}

	// Return old object (post-increment)
	return add;
}

/* 
Purpose: Subtract one to every element in a grid, pre-increment
@return: The original grid with each element having -1
*/
MyGrid& MyGrid::operator--() {
	
	// Subtract one from each element
	for (int i = 0; i < gridElements.size(); i++) {
		for (long & elem : gridElements[i]) {
			elem--;
		}
	}

	// Return changed object (pre-increment)
	return *this;
}

/* 
Purpose: Subtract one to every element in a grid, post-increment
@return: A copy of the original grid, before subtracting one
*/
MyGrid MyGrid::operator--(int) {
	MyGrid sub = *this;

	// Subtract one from each element
	for (int i = 0; i < gridElements.size(); i++) {
		for (long & elem : gridElements[i]) {
			elem--;
		}
	}

	// Return old object (post-increment)
	return sub;
}

/* 
Purpose: Multiply every element by -1
@return: A copy of the original grid, with the negative of each element
*/
MyGrid MyGrid::operator-() const {
	MyGrid negative = *this;
	for (int i = 0; i < negative.gridElements.size(); i++) {
		for (long & elem : negative.gridElements[i]) {
			elem *= -1;
		}
	}
	return negative;
}

/* 
Purpose: Check if two grids are equal (if they have same corner location, size and elements)
@rhs: The right grid to compare to this grid
@return: True if equal, false if not
*/
bool MyGrid::operator==(MyGrid const& rhs) const {
	if (myX != rhs.myX || myY != rhs.myY) {
		return false;
	}
	if (gridElements.size() != rhs.gridElements.size() || gridElements[0].size() != rhs.gridElements[0].size()) {
		return false;
	}
	if (gridElements != rhs.gridElements) {
		return false;
	}
	return true;
}

/* 
Purpose: When writing to a file, print out corner location, size and all elements
@os: The file to write to
@gridIn: The grid to write/print
*/
fstream& operator<<(fstream& os, const MyGrid& gridIn) {

	// Output corner location and size of grid
	os << gridIn.myX << " " << gridIn.myY <<  endl;
	os << gridIn.gridElements.size() << " " << gridIn.gridElements[0].size() << endl;
	
	// Output all elements in grid
	for (int i = 0; i < gridIn.gridElements.size(); i++) {
		os << gridIn.gridElements[i][0];
		for (int j = 1; j < gridIn.gridElements[0].size(); j++) {
			os << " " << gridIn.gridElements[i][j];
		}
		os << endl;
	}
	return os;
}
