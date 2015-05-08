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

#include "Video.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Computer : public Vids::Video {
public:
	Computer();
	Computer(string homepage, string source);
	string getSource() const { return source; }
	string getHomepage() const { return homepage; }
	bool searchMore(string target); // TODO: used to search additonal fields in derived classes

	void display();
	void displayAll();
private:
	string homepage;
	string source;
};

#endif
