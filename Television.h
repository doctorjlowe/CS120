/****************************************************************
File:             Video.h
Description:      class declarations

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#ifndef TELEVISION_H
#define TELEVISION_H

#include "Video.h"
#include <iostream>
#include <iomanip>

class Television : public Vids::Video {
public:
	Television();
	Television(unsigned int season, unsigned int episode);
	unsigned int getSeason() const { return season; }
	unsigned int getEpisode() const { return episode; }
	bool searchTarget(string target); // TODO: used to search additonal fields in derived classes
	// prints description of specific episode; must pass in index of season and episode
	bool searchDesc(string target); // searches descriptions of episodes
	void printDesc(int s, int e) { cout << episodeDesc.at(s * episode + e) << endl; }
	void display();
	void displayAll();
private:
	unsigned int season; // holds max number
	unsigned int episode; // episodes per season
	vector<string> episodeDesc; // holds descriptions of each episode
};

#endif
