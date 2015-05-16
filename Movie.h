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

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Video.h"

class Movie : public Vids::Video {
public:

	Movie();
	Movie(string series, unsigned int series);
	void display(); 
	void displayAll();

	bool searchTarget(string target);
	string getSeries() { return series; }
	unsigned char getSeriesNum() { return seriesNum; }
	void setSeries(string s) { series = s; }
	void setSeriesNum(unsigned int sn) { seriesNum = sn; }
private:
	string series;
	unsigned char seriesNum;
};

#endif
