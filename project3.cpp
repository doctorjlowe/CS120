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

void searchVideos(vector<Video*> &videos, string target) {
	bool found = false;
	int i = 0;
	cout << "Searching..." << endl;
	for (i = 0; i < videos.size(); ++i) {
		// checks every field
		if (videos.at(i)->searchTarget(target)) {
			found = true;
			videos.at(i)->displayAll(); // if target is found in any fields, print all information for index
		}	// if
	}	// for
	// if no matches are found, print message
	if (!found)
		cout << "No matches found for your entry." << endl;
} // print any found matches

void Remove(vector<Video*> &videos) {

}

int main(){

	Person newPerson;
	// Movie newMovie;
	// Television newTelevision;
	vector<Person> persons;
	vector<Video*> videos;
	string searchEntry;
	string person_file_name = "Persons.dat";
	string video_file_name = "Videos.dat";
	string movie_start = "<movie>";
	string name_start = "<name>";
	string audience_start = "<audience>";
	string location_start = "<location>";
	string director_start = "<director>";
	string templine;
	string comm;
	unsigned int stringPos = 0;
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
      
      while ((templine.find(movie_start)) < std::string::npos) {
    		templine.erase(0, stringPos + movie_start.length());
    		cout << "Movie" << endl;
		}	// while movie
		
      while ((templine.find(name_start)) < std::string::npos) {
      	if (templine[0] == '\t') { templine.erase(0, 1); }
    		templine.erase(0, stringPos + name_start.length());
    		cout << templine << endl;
		}	// while
		
      while ((templine.find(audience_start)) < std::string::npos) {
    		templine.erase(0, stringPos + audience_start.length());
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
		// TODO add to videos
	}
	else if (comm == "print") { // print videos
		display(videos); // FIXME: working?
	}
	else if (comm == "quit") {
		break; // quit program
	}
	else if (comm == "remove") {

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
		// TODO: search Television items by episode description
	}
	else if (comm == "search help") {
		cout << "Fields and format of entry while searching:" << endl;
		cout << "name - ";
		cout << "date - mm/dd/yy (leading zeros required)";
	}
	else
		cout << "Input not recognized.\n";
	} while (comm != "quit"); // end loop
	// continue to allow input until user enters 'q' (quit)
   
   #ifdef _WIN32
      system("pause");
   #endif

   return 0;
}	// main()
