/****************************************************************
File:             Movie.cpp
Description:      class declarations

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#include "Movie.h"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace Vids;
	
Movie::Movie() {
	seriesNum = 0;
}

Movie::Movie(unsigned int series) {
	seriesNum = series;
}

void Movie::display() { // order: name, audience, 1st director, 1st actor, runtime
	string shortName = name;
	// TODO: actors and directors abreviation
	cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
	cout << left << fixed << setw(6) << audience;
	// cout << left << fixed << setw(21) << Truncate(shortDirector, 17);
	// cout << left << fixed << setw(12) << Truncate(shortActors, 12);
	cout << left << fixed << setw(4) << runtimeMinutes;
}// displays information for all objects of Video type

void Movie::displayAll() {
	cout << "Name: " << name << endl;
	cout << "Audience: " << audience << endl;
	cout << "Runtime Minutes: " << runtimeMinutes << endl;
	cout << "Location: " << location << endl;
	cout << "Date Released: " << released;
	cout << "Date Viewed: " << viewed;
}

bool Movie::searchTarget(string target) {
	string ser = to_string(seriesNum);
	cout << "name: " << getName() << " target: " << target << endl;
	if (getRuntimeMinutes().find(target) != string::npos // search string of runtimeMinutes
		|| name.find(target) != string::npos // search name
		|| audience == target // if audience rating is equivalent
		|| location.find(target) != string::npos // if it matches a location
		|| dateToString(released).find(target) != string::npos // if it matches the released date
		|| dateToString(viewed).find(target) != string::npos
		|| ser.find(target)) { // if it matches the viewed date
		return true;
	}
	else
		return false;
}
