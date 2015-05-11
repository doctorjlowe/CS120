/****************************************************************
File:             Television.cpp
Description:      class definitions

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#include "Television.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace Vids;

Television::Television() {
	season = 0;
	episode = 0;
	episodeDesc;
}	// default constructor

Television::Television(unsigned int season, unsigned int episode) {
	this->season = season;
	this->episode = episode;
	episodeDesc.resize(season * episode);
}	// parameterized constructor

void Television::display() { // order: name, audience, 1st director, 1st actor, runtime
	if (name != "") {
		string shortName = name;
		cout << left << fixed << setw(28) << Truncate(shortName, 24); // Truncate in Video class
	}
	cout << left << fixed << setw(6) << audience;
	/*	if (directors.size() != 0) {
		string shortDirector = directors.at(0).getFirstName();
		cout << left << fixed << setw(21) << Truncate(shortDirector, 17);
	}
	if (actors.size() != 0) {
		string shortActors = actors.at(0).getFirstName();
		cout << left << fixed << setw(12) << Truncate(shortActors, 12);
	}	*/
	cout << left << fixed << setw(4) << runtimeMinutes;
	cout << left << fixed << setw(3) << season;
	cout << endl;

}// displays information for all objects of Video type

void Television::displayAll() {
	cout << "Name: " << name << endl;
	cout << "Audience: " << audience << endl;
	cout << "Runtime Minutes: " << runtimeMinutes << endl;
	cout << "Total Seasons: " << season << endl;
	cout << "Episodes per Season: " << episode << endl;
	cout << "Location: " << location << endl;

	cout << "Director(s): ";
	// TODO: print directors here?
	cout << endl;

	cout << "Actor(s): ";
	// print actors here?
	cout << endl;

	cout << "Date Released: " << released;
	cout << "Date Viewed: " << viewed;
}	// displayAll

bool Television::searchTarget(string target) {
	string seas = to_string(season); // turns season into string
	string ep = to_string(episode); // turns episode into string
	if (getRuntimeMinutes().find(target) != string::npos // search string of runtimeMinutes
		|| name.find(target) != string::npos // search name
		|| audience == target // if audience rating is equivalent
		|| location.find(target) != string::npos // if it matches a location
		|| dateToString(released).find(target) != string::npos // if it matches the released date
		|| dateToString(viewed).find(target) != string::npos
		|| seas.find(target)
		|| ep.find(target)) { // if it matches the viewed date
		return true;
	}	// if
	else
		return false;
}	// searchTarget

bool Television::searchDesc(string target) { // searches descriptions of episodes
	for (int i = 0; i < episodeDesc.size(); ++i) {
		if (episodeDesc.at(i).find(target) != string::npos) {
			return true;
		}
	}
	return false; // if not found matching descriptions, return false
}
