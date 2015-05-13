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
	cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
	cout << left << fixed << setw(6) << audience;
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
	size_t runMin = getRuntimeMinutes().find(target);
	size_t nm = name.find(target);
	size_t loc = location.find(target);
	size_t rel = dateToString(released).find(target);
	size_t view = dateToString(viewed).find(target);
	size_t series = ser.find(target);

	if (runMin != string::npos // search string of runtimeMinutes
		|| nm != string::npos // search name
		|| audience == target // if audience rating is equivalent
		|| loc != string::npos // if it matches a location
		|| rel != string::npos // if it matches the released date
		|| view != string::npos // view date
		|| ser == target) { // series number
		return true;
	}
	else
		return false;
}
