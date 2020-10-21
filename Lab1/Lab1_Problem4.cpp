/*
Author: Jason Palmer
Class: ECE6122
Last Date Modified: September 16th, 2020
Description: Reflected Beam / Mirror Problem
What is the purpose of this file?
To figure out how many reflections our laser beam takes
*/
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main() {
	int count = 0;
	double x0 = 0.0;
	double y0 = 10.1;

	double x1 = 1.4;
	double y1 = -9.6;
	while (x1 > .01 || x1 < -.01 || y1 < 0) {

		// Calculate the slope of the first line and the ellipse tangent line
		double slope0 = (y1 - y0) / (x1 - x0);
		double slopeTan = -4 * x1 / y1;

		// Calculate the tangent of the first line to the ellipse tangent
		double tan0 = (slope0 - slopeTan) / (1 + slope0 * slopeTan);

		// Use that tangent to calculate the slope of the reflected line
		double slope1 = (slopeTan - tan0) / (1 + tan0 * slopeTan);

		// Calculate the y-intercept of the reflected line
		double intercept1 = y1 - slope1 * x1;

		// Get components of quadratic formula (-b +- sqrt(b^2 - 4ac) / 2a)
		double a = pow(slope1, 2) + 4;
		double b = 2 * slope1 * intercept1;
		double c = pow(intercept1, 2) - 100;

		// Solve quadratic formula for x-component intersection of reflected line and ellipse
		double xA = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		double xB = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

		// Set new starting point to old ending point
		x0 = x1;
		y0 = y1;

		// Set new ending point to intersection
		if (abs(x1 - xA) > abs(x1 - xB)) {
			x1 = xA;
		} else {
			x1 = xB;
		}
		y1 = slope1 * x1 + intercept1;

		// Increase number of bounces
		count++;

	}
	ofstream output;
	output.open("output4.txt");

	output << count << endl;
	output.close(); 

}