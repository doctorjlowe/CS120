/****************************************************************
File:             Movie.h
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
	Movie();	// actually implement the constructor to avoid linker error
	Movie(unsigned int series) {
		seriesNum = series;
	} // TODO: add parametized Video constructor
	void display() { // order: name, audience, 1st director, 1st actor, runtime
		if (name != "") {
			string shortName = name;
			cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
		}
		cout << left << fixed << setw(6) << audience;
		if (directors.size() != 0) {
			string shortDirector = directors.at(0).getFirstName();
			cout << left << fixed << setw(21) << Truncate(shortDirector, 17);
		}
		if (actors.size() != 0) {
			string shortActors = actors.at(0).getFirstName();
			cout << left << fixed << setw(12) << Truncate(shortActors, 12);
		}
		cout << left << fixed << setw(4) << runtimeMinutes;
		cout << endl;

	}// displays information for all objects of Video type
	void displayAll() {
		cout << "Name: " << name << endl;
		cout << "Audience: " << audience << endl;
		cout << "Runtime Minutes: " << runtimeMinutes << endl;
		cout << "Location: " << location << endl;

		cout << "Director(s): ";
		// TODO: add directors here?
		cout << endl;

		cout << "Actor(s): ";
		// TODO: add actors here?
		cout << endl;

		cout << "Date Released: " << released;
		cout << "Date Viewed: " << viewed;
	}

	bool searchTarget(string target) {
		string ser = to_string(seriesNum);
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
	void setSeriesNum(unsigned int sn) { seriesNum = sn; }
private:
	unsigned int seriesNum;
};

#endif
