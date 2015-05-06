/****************************************************************
File:             Video.h
Description:      class declarations

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Movie : public Vids::Video {
public:
	Movie();
	Movie(unsigned int series) {
		seriesNum = series;
	} // TODO: add parametized Video constructor
	void display() { // order: name, audience, 1st director, 1st actor, runtime
		string shortName = name;
		string shortDirector = directors.at(0).getFirstName();
		string shortActors = actors.at(0).getFirstName();
		cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
		cout << left << fixed << setw(6) << audience;
		cout << left << fixed << setw(21) << Truncate(shortDirector, 17);
		cout << left << fixed << setw(12) << Truncate(shortActors, 12);
		cout << left << fixed << setw(4) << runtimeMinutes;

	}// displays information for all objects of Video type
	void displayAll() {
		cout << "Name: " << name << endl;
		cout << "Audience: " << audience << endl;
		cout << "Runtime Minutes: " << runtimeMinutes << endl;
		cout << "Location: " << location << endl;

		cout << "Director(s): ";
		for (int i = 0; i < directors.size(); ++i) { // directors
			cout << directors.at(i);
			if (i < directors.size())
				cout << ", "; // if multiple, separate by comma
		}
		cout << endl;

		cout << "Actor(s): ";
		for (int i = 0; i < actors.size(); ++i) { // actors
			cout << actors.at(i);
			if (i < actors.size())
				cout << ", "; // if multiple, separate by comma
		}
		cout << endl;

		cout << "Date Released: " << released;
		cout << "Date Viewed: " << viewed;
	}

	bool SearchBool(string selection) {
		bool found = false;

		if (name.find(selection) != string::npos
			|| directors.find(selection) != string::npos
			|| released.find(selection) != string::npos
			|| audience.find(selection) != string::npos
			|| static_cast<string>(runtimeMinutes) == selection // makes more sense to search by whole runtime
			|| location.find(selection) != string::npos) {
			return true;
		}
		else {
			return false;
		}
	}  // SearchBool
private:
	unsigned int seriesNum;
};

#endif
