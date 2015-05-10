/****************************************************************
File:             project3.cpp
Description:      database for a movie library
Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13
We hereby certify that this program is entirely our own work.
*****************************************************************/

#include <algorithm> // std::copy
#include <fstream> // std::ifstream, std::ofstream
#include <iostream> // std::cout
#include <string> // std::string
#include <vector>

#include "Date.h"
#include "Person.h"
#include "Video.h"
#include "Movie.h"
#include "Television.h"
#include "Computer.h"

using namespace std;
using namespace Vids;

void display(vector<Video*> &videos) { // displays all objects in vector
	for (int i = 0; i < videos.size(); ++i) { videos.at(i)->display(); }
}	// display

vector<int> searchVideos(vector<Video*> &videos, string target) {
	vector<int> returnVector; // remembers all indexes of matched search targets
	bool found = false;
	int i = 0;
	cout << "Searching..." << endl;
	for (i = 0; i < videos.size(); ++i) {
		// checks every field
		if (videos.at(i)->searchTarget(target)) {
			found = true;
			returnVector.push_back(i);
			videos.at(i)->displayAll(); // if target is found in any fields, print all information for index
		}	// if
	}	// for
	// if no matches are found, print message
	if (!found)
		cout << "No matches found for your entry." << endl;
	return returnVector;
} // print any found matches

void addVideo(vector<Video*> &videos) {
	Video* newAddVid;
	string templine;
	string templine2;
	unsigned int tempInt = 0;
	unsigned int tempInt2 = 0;

	cout << "Which type to add?(Movie, Television, Computer) ";
	cin >> templine;
	if (templine == "Movie") {
		cout << "Which instalment in a series is it? ";
		cin >> tempInt;
		newAddVid = new Movie(tempInt);
	}
	else if (templine == "Television") { // season, episode, episodeDesc
		cout << "How many seasons are in it? ";
		cin >> tempInt;
		cout << "How many episodes are in each season? ";
		cin >> tempInt2;
		newAddVid = new Television(tempInt, tempInt2);
	}
	else if (templine == "Computer") {
		cout << "What is the homepage (Enter nothing to skip)? ";
		cin >> templine;
		cout << "What is the source of the video (domain)? ";
		cin >> templine2;
		newAddVid = new Computer(templine, templine2);
	}
	else {
		cout << "Not a valid type.";
		return; // TODO: should reprint first message
	}
	// end ifs
	cout << "What is the Name of the video? ";
	cin >> templine;
	newAddVid->setName(templine);
	cout << "What is the audience of the video? ";
	cin >> templine;
	newAddVid->setAudience(templine);
	cout << "What is the location of the video? ";
	cin >> templine;
	newAddVid->setLocation(templine);
	cout << "Enter the director(s): ";
	// TODO: how to add directors
	cout << "Enter the actor(s): ";
	// TODO: how to add actors
	// TODO: released and viewed and runtime
}

// removes any matched items from the videos vector
void remove(vector<Video*> &videos, vector<int> matches) {
	for (int i = 0; i < matches.size(); ++i) {
		videos.erase(videos.begin() + matches.at(i)); // should erase any matched items from the vector
	}
}

int main(){

	Person newPerson;
	// Movie newMovie;
	// Television newTelevision;
	vector<Person> persons;
	vector<Video*> videos;
	vector<int> matches;
	string person_file_name = "Persons.dat";
	string video_file_name = "Videos.dat";
	string movie_delimiter = "<movie>";
	string name_delimiter = "<name>";
	string templine;
	string comm;
	string searchEntry;
	unsigned int stringPos = 0;
	unsigned int tempInt = 0;
   vector<string> temp(5);
	int i = 0;
   
   //cout << "What name should the File have?" << std::endl;
   //cin >> file_name;
	
	// open Person file
   ifstream personReader(person_file_name.c_str());
   if (!personReader) {
      cout << "Error: Cannot open Person input file. =[ " << endl;
   
      #ifdef _WIN32
         system("pause");
      #endif
      
      return -1;
      
   }  // if
   // each line of input fills one object
   while (!personReader.eof()) {
      getline(personReader, temp.at(0), '\t');
      if ( personReader.eof() ) break;
      getline(personReader, temp.at(1), '\t');
      getline(personReader, temp.at(2), '\t');
      getline(personReader, temp.at(3), '\t');
      getline(personReader, temp.at(4), '\n');
      
      if (temp.at(0) == "Person") {
      	Person newPerson(temp.at(1), temp.at(3), temp.at(2), temp.at(4));
      	/* FIXME: following is debugging output
      	cout << "First: " << newPerson.getFirstName() << endl;
      	cout << "Middle: " << newPerson.getMiddleName() << endl;
      	cout << "Last: " << newPerson.getLastName() << endl;
      	cout << "Lineage: " << newPerson.getLineage() << endl;	*/
      }	// if Person
   }  // while
   
   personReader.close();	// close input file
	
	// open Video file
   ifstream videoReader(video_file_name.c_str());
   if (!videoReader) {
      cout << "Error: Cannot open Video input file. =[ " << endl;
   
      #ifdef _WIN32
         system("pause");
      #endif
      
      return -1;
      
   }  // if
   // each line of input fills one object
   while (!videoReader.eof()) {
      getline(videoReader, templine);
      if ( videoReader.eof() ) break;
      
      while ((templine.find(movie_delimiter)) < std::string::npos) {
    		templine.erase(0, stringPos + movie_delimiter.length());
    		cout << "Movie" << endl;
		}	// while movie
		
      while ((templine.find(name_delimiter)) < std::string::npos) {
    		templine.erase(0, stringPos + name_delimiter.length() + 1);
    		cout << templine << endl;
		}	// while 
		
   }  // while !videoReader.eof()
   
   videoReader.close();	// close input file

	do {
	cout << "Enter a command (help = command list): ";
	cin >> comm; // choice of command
	
	if (comm == "help") { // help/display command list
		cout << "COMMANDS:" << endl;
		cout << "search help = gives format for search entries" << endl;
		cout << "search = search document for a given entry" << endl;
		cout << "add = add a new entry to list" << endl;
		cout << "remove = remove an item from the list" << endl;
		cout << "print = print entire list of Videos" << endl;
		cout << "quit = quit program" << endl;
		cout << "save = save changes to list of Videos to external file" << endl;
	}
	else if (comm == "add") { // add new entry
		addVideo(videos);
	}
	else if (comm == "print") { // print videos
		display(videos); // FIXME: working?
	}
	else if (comm == "quit") {
		break; // quit program
	}
	else if (comm == "remove") {
		cout << "Enter something to remove: ";
		cin.ignore();
		getline(cin, searchEntry);
		matches = searchVideos(videos, searchEntry);
		if (matches.size() != 0) { // if items were matched, then do the following
			remove(videos, matches);
			cout << "Items removed." << endl;
		}
	}
	else if (comm == "save") {
		// TODO: save list updates
	}
	else if (comm == "search") { // search vectors for entries
		cout << "Enter something to search: ";
		cin.ignore();
		getline(cin, searchEntry);
		searchVideos(videos, searchEntry); // search videos vector for the searchEntry
	}
	else if (comm == "search description") {
		cout << "Enter something to search all episode descriptions (for TV shows):" << endl;
		cin.ignore();
		getline(cin, searchEntry);
		for (i = 0; i < videos.size(); ++i) {
			if () {// TODO: if type is Television, then do the following
				if (dynamic_cast<Television*>(videos.at(i))->searchDesc(searchEntry))
					videos.at(i)->displayAll();
			}
		}
		// TODO: else, print error message
	}
	else if (comm == "search help") {
		cout << "Fields and format of entry while searching:" << endl;
		cout << "name - Movie Title Case Sensative" << endl;
		cout << "date - mm/dd/yy (leading zeros required)" << endl;
		cout << "audience - G or PG or PG-13 or R" << endl;
		cout << "location - ex. Bill's House or Garage" << endl;
		cout << "director - ex. Jackson or Peter Jackson" << endl;
		cout << "actor - ex. Cruise or Tom Cruise" << endl;
		cout << "runtime minutes - 135 or 60" << endl;
	}
	else
		cout << "Input not recognized.\n";
	} while (comm != "quit"); // end loop
	// continue to allow input until user enters 'q' (quit)
   
   #ifdef _WIN32
      system("pause");
   #endif

   return 0;
