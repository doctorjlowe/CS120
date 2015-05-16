/****************************************************************
File:             Computer.h
Description:      class declarations

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Video.h"

class Computer : public Vids::Video {
public:
	Computer();
	Computer(string homepage, string source);
	string getSource() const { return source; }
	string getHomepage() const { return homepage; }
	void setSource(string s) { source = s; }
	void setHomepage(string h) { homepage = h; }
	bool searchTarget(string target); // used to search data members

	void display();
	void displayAll();
private:
	string homepage;
	string source;
};

#endif
