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

class Movie : public Vids::Video {
public:
	Movie();
	Movie(unsigned int series);
	void display(); // displays information for all objects of Video type
	void displayAll();
	bool searchTarget(string target);
	void setSeriesNum(unsigned int sn) { seriesNum = sn; }
private:
	unsigned int seriesNum;
};

#endif
