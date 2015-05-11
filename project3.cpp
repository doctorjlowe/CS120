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

struct Direct {
	char iMov;
	char iPer;
};

struct Act {
	char iMov;
	char iPer;
};

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

int searchPeople(vector<Person> &persons, string target) {
	bool found = false;
	int i = -1;
	cout << "Searching..." << endl;
	for (i = 0; i < persons.size(); ++i) {
		// checks every field
		if (persons.at(i).searchPeople(target)) {
			found = true;
			return i;
		}	// if
	}	// for
	// if no matches are found, print message
	if (!found)
		cout << "No matches found for your entry." << endl;
	return i;
}

void addVideo(vector<Video*> &videos, vector<Person> &people) {
	Video* newAddVid;
	vector<Person> addDirectors;
	vector<Person> addActors;
	string templine;
	string templine2;
	unsigned int tempInt = 0;
	unsigned int tempInt2 = 0;
	unsigned int tempInt3 = 0;

	cout << "Which type to add?(Movie, Television, Computer) ";
	cin >> templine;
	if (templine == "Movie") {
		cout << "Which installment in a series is it? ";
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

	// name
	cout << "What is the Name of the video? ";
	cin.ignore();
	getline(cin, templine);
	newAddVid->setName(templine);

	// audience
	cout << "What is the audience of the video? ";
	cin >> templine;
	newAddVid->setAudience(templine);

	// location
	cout << "What is the location of the video? ";
	cin.ignore();
	getline(cin, templine);
	newAddVid->setLocation(templine);

	// release date
	cout << "What was its release date?" << endl << "Month: ";
	cin >> tempInt;
	cout << "Day: ";
	cin >> tempInt2;
	cout << "Year: ";
	cin >> tempInt3;
	Date relDate(tempInt3, tempInt, tempInt2); // create new Date obj to fill release date
	newAddVid->setReleased(relDate);

	// viewed date
	cout << "Which date did you watch it?" << endl << "Month: ";
	cin >> tempInt;
	cout << "Day: ";
	cin >> tempInt2;
	cout << "Year: ";
	cin >> tempInt3;
	Date watDate(tempInt3, tempInt, tempInt2); // create new Date obj to fill release date
	newAddVid->setReleased(watDate);

	// directors
	cout << "Enter the director(s): "; // TODO: add multiple
	cin.ignore();
	getline(cin, templine);
	people.push_back(templine); // adds a director to the people vector

	// actors
	cout << "Enter the actor(s): "; // TODO: add multiple
	cin.ignore();
	getline(cin, templine);
	people.push_back(templine); // add an actor to the people vector
	// TODO: alphabetize vector entry?
	videos.push_back(newAddVid); // if not, use this
} // End addVideo

void editVideo(Video* &vid, string field) {
	string entry;
	unsigned int n;
	vector<Person> persons;
	unsigned short m, d, y;
	if (field == "name") {
		cout << "Enter new name: ";
		getline(cin, entry);
		vid->setName(entry);
	}
	else if (field == "audience") {
		cout << "Enter new audience: ";
		getline(cin, entry);
		vid->setAudience(entry);
	}
	else if (field == "location") {
		cout << "Enter a new location: ";
		getline(cin, entry);
		vid->setLocation(entry);
	}
	else if (field == "directors") {
		cout << "Enter number of directors: ";
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cout << "Enter director: ";
			getline(cin, entry);
			persons.push_back(entry);
		}
		vid->setDirectors(persons);
	}
	else if (field == "actors") {
		cout << "Enter number of actors: ";
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cout << "Enter actor: ";
			getline(cin, entry);
			persons.push_back(entry);
		}
		vid->setActors(persons);
	}
	else if (field == "released") {
		cout << "Enter new Month: ";
		cin >> m;
		cout << "Enter new Day: ";
		cin >> d;
		cout << "Enter new Year: ";
		cin >> y;
		Date newDate(y, m, d);
		vid->setReleased(newDate);
	}
	else if (field == "viewed") {
		cout << "Enter new Month: ";
		cin >> m;
		cout << "Enter new Day: ";
		cin >> d;
		cout << "Enter new Year: ";
		cin >> y;
		Date newDate(y, m, d);
		vid->setViewed(newDate);
	}
	else if (field == "runtime") {
		cout << "Enter new runtime: ";
		cin >> n;
		vid->setRuntimeMinutes(n);
	}
	else {
		cout << "Error: this is not a valid field choice." << endl;
	}
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
	vector<Act> actors;
	vector<Direct> directors;
	vector<int> matches;
	string person_file_name = "Persons.dat";
	string video_file_name = "Videos.dat";
	string movie_start = "<movie>";
	string name_start = "<name>";
	string audience_start = "<audience>";
	string location_start = "<location>";
	string director_start = "<director>";
	string actor_start = "<actor>";
	string movie_stop = "</movie>";
	string name_stop = "</name>";
	string audience_stop = "</audience>";
	string location_stop = "</location>";
	string director_stop = "</director>";
	string actor_stop = "</actor>";
	string templine;
	string comm;
	string searchEntry;
	size_t stringPos = 0;
	unsigned int tempInt = 0;
	vector<string> temp(5);
	int i = 0;
	kind importKind = NONE;
	Video* importVideo = NULL;
	Act newActor;
	Direct newDirector;
   
   //cout << "What name should the Person File have?" << std::endl;
   //cin >> person_file_name;
	
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
		persons.push_back(newPerson);
      	/* FIXME: following is debugging output
      	cout << "First: " << newPerson.getFirstName() << endl;
      	cout << "Middle: " << newPerson.getMiddleName() << endl;
      	cout << "Last: " << newPerson.getLastName() << endl;
      	cout << "Lineage: " << newPerson.getLineage() << endl;	*/
      }	// if Person
   }  // while
   
   personReader.close();	// close input file
   
   //cout << "What name should the Video File have?" << std::endl;
   //cin >> video_file_name;
	
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
    		templine.erase(0, movie_start.length());
    		importKind = MOVIE;
    		importVideo = new Movie;
		}	// while movie start
		
      while ((templine.find(name_start)) < std::string::npos) {
      	if (templine[0] == '\t') templine.erase(0, 1);
    		templine.erase(0, name_start.length());
    		stringPos = templine.find(name_stop);
    		if (stringPos < std::string::npos) {
    			templine.erase(stringPos, stringPos + name_stop.length()); }
    		importVideo->setName(templine);
		}	// while name
		
      while ((templine.find(audience_start)) < std::string::npos) {
      	if (templine[0] == '\t') templine.erase(0, 1);
    		templine.erase(0, audience_start.length());
    		stringPos = templine.find(audience_stop);
    		if (stringPos < std::string::npos) {
    			templine.erase(stringPos, stringPos + audience_stop.length()); }
    		importVideo->setAudience(templine);
		}	// while audience
		
      while ((templine.find(location_start)) < std::string::npos) {
      	if (templine[0] == '\t') templine.erase(0, 1);
    		templine.erase(0, location_start.length());
    		stringPos = templine.find(location_stop);
    		if (stringPos < std::string::npos) {
    			templine.erase(stringPos, stringPos + location_stop.length()); }
    		importVideo->setLocation(templine);
		}	// while location
		
      while ((templine.find(director_start)) < std::string::npos) {
      	if (templine[0] == '\t') templine.erase(0, 1);
    		templine.erase(0, director_start.length());
    		stringPos = templine.find(director_stop);
    		if (stringPos < std::string::npos) {
    			templine.erase(stringPos, stringPos + director_stop.length()); }
    		cout << templine << endl;
			// TODO: add in director to persons
			if (videos.size() == 0)
				newDirector.iMov = 0;
			else
				newDirector.iMov = videos.size() - 1;
			newDirector.iPer = searchPeople(persons, templine);
			directors.push_back(newDirector);
		}	// while director

	  while ((templine.find(actor_start)) < std::string::npos) {
		  if (templine[0] == '\t') templine.erase(0, 1);
		  templine.erase(0, actor_start.length());
		  stringPos = templine.find(actor_stop);
		  if (stringPos < std::string::npos) {
			  templine.erase(stringPos, stringPos + director_stop.length());
		  }
		  cout << templine << endl;
<<<<<<< HEAD
		  // TODO: add in actor to persons
=======
		  persons.push_back(templine); // pushback entry of director
		  importVideo->setActors(persons);
>>>>>>> origin/master
	  }	// while actor
      
      while ((templine.find(movie_stop)) < std::string::npos) {
    		templine.erase(0, movie_stop.length());
    		if (importKind != MOVIE) {
    			cout << "Wrong importKind" << endl;
    			break;
    		}	// if
    		else {
    			cout << "Closing Movie" << endl;
    			videos.push_back(importVideo);
    		}	// else
		}	// while movie stop
	  i++; // increment index store for actors and directors vectors
   }  // while !videoReader.eof()
   
   videoReader.close();	// close input file

	do {
	cout << "Enter a command (help = command list): ";
	getline(cin, comm); // choice of command
	
	if (comm == "help") { // help/display command list
		cout << "COMMANDS:" << endl;
		cout << "help search = gives format for search entries" << endl;
		cout << "search = search document for a given entry" << endl;
		cout << "description search = search Television episode descriptions" << endl;
		cout << "add = add a new entry to list" << endl;
		cout << "edit = edit an existing entry" << endl;
		cout << "loan = edit the location of an entry" << endl;
		cout << "remove = remove an item from the list" << endl;
		cout << "print = print entire list of Videos" << endl;
		cout << "quit = quit program" << endl;
		cout << "save = save changes to list of Videos to external file" << endl;
	}
	else if (comm == "add") { // add new entry
		addVideo(videos);
	}
	else if (comm == "description search") {
		cout << "Enter something to search all episode descriptions (for TV shows):" << endl;
		getline(cin, searchEntry);
		for (i = 0; i < videos.size(); ++i) {
			if (typeid(videos.at(i)) == typeid(Television)) { // FIXME: does this work?
				if (dynamic_cast<Television*>(videos.at(i))->searchDesc(searchEntry))
					videos.at(i)->displayAll();
			}
		}
		// TODO: else, print error message
	}
	else if (comm == "edit" || comm == "loan") {
		cout << "Enter something to search (be specific): ";
		getline(cin, searchEntry);
		matches = searchVideos(videos, searchEntry);
		cout << "Do you want to change this (y/n)? " << endl;
		videos.at(matches.at(0))->displayAll();
		cout << endl;
		cin >> templine;
		if (templine == "n")
			continue; // FIXME: goes to top?
		else if (templine == "y") {
			// do nothing
		}
		else {
			cout << "not a valid choice" << endl;
			continue;
		}
		cout << "Choose a field to edit: ";
		// TODO: print field names
		cin >> templine;
		if (comm == "edit")
			editVideo(videos.at(matches.at(0)), templine); // call function to edit matched index
		else if (comm == "loan")
			editVideo(videos.at(matches.at(0)), "location");
		cout << "Update sucessful." << endl; // FIXME: working?
	}
	else if (comm == "help search") {
		cout << "Fields and format of entry while searching:" << endl;
		cout << "name - Movie Title Case Sensative" << endl;
		cout << "date - mm/dd/yy (leading zeros required)" << endl;
		cout << "audience - G or PG or PG-13 or R" << endl;
		cout << "location - ex. Bill's House or Garage" << endl;
		cout << "director - ex. Jackson or Peter Jackson" << endl;
		cout << "actor - ex. Cruise or Tom Cruise" << endl;
		cout << "runtime minutes - 135 or 60" << endl;
	}
	else if (comm == "print") { // print videos
		display(videos); // FIXME: working?
	}
	else if (comm == "quit") {
		break; // quit program
	}
	else if (comm == "remove") {
		cout << "Enter something to remove: ";
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
		getline(cin, searchEntry);
		searchVideos(videos, searchEntry); // search videos vector for the searchEntry
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
