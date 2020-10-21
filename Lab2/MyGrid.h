/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: September 28, 2020
Description: Outline of grid class functions
What is the purpose of this file?
To add outline for grids to perform operations on themselves and each other
*/
// Remember your file headers and comments

#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std; 

class MyGrid
{

public:
    // Load grid from file and instantiate
    bool loadGridFromFile(const string& filename);

    // All elements to 0
    void zeroOutGrid();

    // Return rows or columns in grid
    long getNumRows() const;
    long getNumCols() const;

    // Add or subtract two grids
    MyGrid operator+(MyGrid const&) const;
    MyGrid operator-(MyGrid const&) const;

    // Add rhs constant to this grid
    MyGrid operator+(long const&) const;

    // Add lhs constant to rhs grid
    friend MyGrid operator+(long const& lhs, MyGrid const& rhs);

    // Addition assignment 
    MyGrid& operator+=(MyGrid const&);

    // Increment
    MyGrid& operator++(); // Prefix
    MyGrid operator++(int); // Postfix

    // Decrement
    MyGrid& operator--(); // Prefix
    MyGrid operator--(int); // Postfix

    // Multiply -1
    MyGrid operator-() const;

    // Equal check
    bool operator==(MyGrid const&) const;

    // Write to file
    friend fstream& operator<<(fstream& os, const MyGrid& gridIn);

public:
    long myX, myY;
    vector<vector<long>> gridElements;
};

