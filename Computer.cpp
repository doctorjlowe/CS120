/****************************************************************
File:             Computer.cpp
Description:      class declarations

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#include "Computer.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace Vids;

Computer::Computer(string homepage, string source) {
	this->homepage = homepage;
	this->source = source;
}
void Computer::display() { // order: name, audience, 1st director, 1st actor, runtime
	string shortName = name;
	string shortDirector = directors.at(0).getFirstName();
	string shortActors = actors.at(0).getFirstName();
	cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
	cout << left << fixed << setw(6) << audience;
	cout << left << fixed << setw(21) << Truncate(shortDirector, 17);
	cout << left << fixed << setw(12) << Truncate(shortActors, 12);
	cout << left << fixed << setw(4) << runtimeMinutes;
	cout << endl;
}// displays information for all objects of Video type

void Computer::displayAll() {
	cout << "Name: " << name << endl;
	cout << "Audience: " << audience << endl;
	cout << "Runtime Minutes: " << runtimeMinutes << endl;
	cout << "Location: " << location << endl;

	cout << "Director(s): ";
	for (int i = 0; i < directors.size(); ++i) { // directors
		cout << directors.at(i);
		if (i < directors.size())
			cout << ", "; // if multiple, seperate by comma
	}	// for directors
	cout << endl;

	cout << "Actor(s): ";
	for (int i = 0; i < actors.size(); ++i) { // actors
		cout << actors.at(i);
		if (i < actors.size())
			cout << ", "; // if multiple, seperate by comma
	}	// for actors
	cout << endl;

	cout << "Date Released: " << released;
	cout << "Date Viewed: " << viewed;
	cout << "Homepage: " << homepage << endl;
	cout << "Link to Video: " << source << endl;
}	// displayAll()

bool Computer::searchTarget(string target) {
	if (getRuntimeMinutes().find(target) != string::npos // search string of runtimeMinutes
		|| name.find(target) != string::npos // search name
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
