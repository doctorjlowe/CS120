/****************************************************************
File:             Computer.cpp
Description:      class declarations

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include "Computer.h"

using namespace std;
using namespace Vids;

Computer::Computer() {
	homepage = "";
	source = "";
}

Computer::Computer(string homepage, string source) {
	this->homepage = homepage;
	this->source = source;
}
void Computer::display() { // order: name, audience, 1st director, 1st actor, runtime
	if (name != "") {
		string shortName = name;
		cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
	}
	cout << left << fixed << setw(6) << audience;

}// displays information for all objects of Video type

void Computer::displayAll() {
	cout << "Name: " << name << endl;
	cout << "Audience: " << audience << endl;
	cout << "Runtime Minutes: " << runtimeMinutes << endl;
	cout << "Location: " << location << endl;
	cout << "Date Released: " << released;
	cout << "Date Viewed: " << viewed;
	cout << "Homepage: " << homepage << endl;
	cout << "Link to Video: " << source << endl;
}	// displayAll()

bool Computer::searchTarget(string target) {
	if (name.find(target) != string::npos // search name
		|| audience == target // if audience rating is equivalent
		|| location.find(target) != string::npos // if it matches a location
		|| dateToString(released).find(target) != string::npos // if it matches the released date
		|| dateToString(viewed).find(target) != string::npos
		|| homepage.find(target) != string::npos
		|| source.find(target) != string::npos) { // if it matches the viewed date
		return true;
	}
	else
		return false;
}
