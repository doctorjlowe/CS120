/****************************************************************
File:             project3.cpp
Description:      database for a movie library

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#include <cstdlib>	// std::atoi
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

struct Link {
   char iMov;
   char iPer;
};

int searchPeople(vector<Person> &persons, Person target);
// pre-declare this one since it's needed by others

void addVideo(vector<Video*> &videos, vector<Person> &people) {
   Video* newAddVid;
   vector<Person> addDirectors;
   vector<Person> addActors;
   string templine;
   string templine2;
   unsigned int tempInt = 0;
   unsigned int tempInt2 = 0;
   unsigned int tempInt3 = 0;
   char choice = 'n';
   bool badInput = false;

   cout << "Which type to add?(Movie, Television, Computer) ";
   cin >> templine;
   if (templine == "Movie") {
   	cout << "Is this movie part of a series? [y/N] ";
   	choice = tolower( getchar() );
   	if(choice == 'n'){  // not series
      	newAddVid = new Movie();
   		}	// if 'n'
   	else {	// series
   		cout << "Give the name of the series: ";
   		cin >> templine;
	  		cout << "Which installment in a series is it? ";
	  		cin >> tempInt;
            do{	// verify input
					badInput = false;
					if(!cin){
						badInput = true;
						cin.clear();
						cin.ignore();
						cout << endl << "Please enter a number: ";
						cin >> tempInt;
					}	// if !cin
            } while(badInput);
      	newAddVid = new Movie(templine, tempInt);
      } // else 'y'
   }	// if Movie
   else if (templine == "Television") { // season, episode, episodeDesc
      cout << "How many seasons are in it? ";
      cin >> tempInt;
      cout << "How many episodes are in each season? ";
      cin >> tempInt2;
      newAddVid = new Television(tempInt, tempInt2);
   }	// if Television
   else if (templine == "Computer") {
      cout << "What is the homepage (Enter nothing to skip)? ";
      cin >> templine;
      cout << "What is the source of the video (domain)? ";
      cin >> templine2;
      newAddVid = new Computer(templine, templine2);
   }	// if Computer
   else {
      cout << "Not a valid type.";
      return; // TODO: should reprint first message
   }	// else - end of type ifs

   // name
   cout << "What is the Name of the video? ";
   cin.ignore();
   getline(cin, templine);
   newAddVid->setName(templine);

   // audience
   cout << "What is the Audience of the video? ";
   cin >> templine;
   newAddVid->setAudience(templine);

   // location
   cout << "What is the Location of the video? ";
   cin.ignore();
   getline(cin, templine);
   newAddVid->setLocation(templine);

   // release date
   cout << "What was its Release Date?" << endl << "Month: ";
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
   if (!searchPeople(people, templine))
	   people.push_back(templine); // add an actor to the people vector
   else
	   // TODO: link entry to existing actor

   // actors
   cout << "Enter the actor(s): "; // TODO: add multiple
   cin.ignore();
   getline(cin, templine);
   if (!searchPeople(people, templine))
		people.push_back(templine); // add an actor to the people vector
   else
	   // TODO: link entry to existing actor
   // TODO: alphabetize vector entry?
   videos.push_back(newAddVid); // if not, use this
   delete newAddVid;
} // End addVideo

void display(vector<Video*> &videos, vector<Person> &persons, vector<Link> &directors, vector<Link> &actors) { // displays all objects in vector
	int currDir;
	int currAct;
	cout << "Name\t\t\tAudience Director\tActor" << endl;
	for (int i = 0; i < videos.size(); ++i) {
		videos.at(i)->display();
		persons.at(directors.at(i).iPer).display(); // display the person in directors
		persons.at(actors.at(i).iPer).display(); // display the person in actors
		cout << endl;
	}
}	// display

// video to be edited (from vector), whole vector of People, designated field to search
void editVideo(Video* &vid, vector<Person> &persons, string field) {
	string entry;
	unsigned int n;
	int j = 0;
	unsigned short m, d, y;

	if (field == "directors" || field == "actors") {
		cout << "Enter number of " << field << ": ";
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cout << "Enter " << field.substr(0, field.length() - 1) << ": ";
			getline(cin, entry);
			m = searchPeople(persons, entry);
			if (j == -1) { // if searchPeople did not find the person, add them
				persons.push_back(entry);
				// TODO: link in actors and directors
			}	// if
			else {
				// TODO: link in actors and directors
			}	// else
		}	// for
	}	// if

	cout << "Enter new " << field << ": ";
	getline(cin, entry);

	if (field == "name") {
		vid->setName(entry);
	}	// if name
	else if (field == "audience") {
		vid->setAudience(entry);
	}	// if audience
	else if (field == "location") {
		vid->setLocation(entry);
	}	// if location
	else if (field == "actors") {
		cout << "Enter number of actors: ";
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cout << "Enter actor: ";
			getline(cin, entry);
			if (searchPeople(persons, entry) != -1) // if the entry is not found in persons, add it
				persons.push_back(entry);
		}	// for
	}	// if actors
	else if (field == "released") {
		cout << "Enter new Month: ";
		cin >> m;
		cout << "Enter new Day: ";
		cin >> d;
		cout << "Enter new Year: ";
		cin >> y;
		Date newDate(y, m, d);
		vid->setReleased(newDate);
	}	// if released
	else if (field == "viewed") {
		cout << "Enter new Month: ";
		cin >> m;
		cout << "Enter new Day: ";
		cin >> d;
		cout << "Enter new Year: ";
		cin >> y;
		Date newDate(y, m, d);
		vid->setViewed(newDate);
	}	// if viewed
	else if (field == "runtime") {
		cout << "Enter new runtime: ";
		cin >> n;
		vid->setRuntimeMinutes(n);
	}	// if runtime
	else {
		cout << "Error: this is not a valid field choice." << endl;
	}	// else invalid field
}	// editVideo

// removes any matched items from the videos vector
void remove(vector<Video*> &videos, vector<int> matches) {
   for (int i = 0; i < matches.size(); ++i) {
      videos.erase(videos.begin() + matches.at(i)); // should erase any matched items from the vector
   }	// for
}	// remove

int searchPeople(vector<Person> &persons, Person target) {
   bool found = false;
   int i;
   cout << "Searching..." << endl;
   for (i = 0; i < persons.size(); ++i) {
      // checks every field
      if (persons.at(i).getFirstName() == target.getFirstName()) {
         //cout << "First match" << endl;
         if (persons.at(i).getLastName() == target.getLastName()) {
            //cout << "Last match" << endl;
            found = true;
            return i;
         }  // if last
      }  // if first
      // else cout << persons.at(i).getFirstName() << ", " << target.getFirstName() << endl;
   }  // for
   // if no matches are found, print message
   if (!found) {
      cout << "No matches found for this person." << endl;
   	i = -1;
   }	// if
   return i;
}	// searchPeople

vector<int> searchVideos(const vector<Video*> &videos, string target) {	// print any found matches
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
      }  // if
   }  // for
   // if no matches are found, print message
   if (!found)
      cout << "No matches found for this video." << endl;
   return returnVector;
} // searchVideos

unsigned char split (const string& s, char c, vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);
   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);
      if (j == string::npos) v.push_back(s.substr(i, s.length()));
   }  // while
   return v.size();
}  // split(

int main(){

   Person newPerson;
   // Movie newMovie;
   // Television newTelevision;
   vector<Person> persons;
   vector<Video*> videos;
   vector<Link> actors;
   vector<Link> directors;
   vector<int> matches;
   string person_file_name = "Persons.dat";
   string video_file_name = "Videos.dat";
   string movie_start = "<movie>";
   string tv_start = "<television>";
   string computer_start = "<computer>";
   string name_start = "<name>";
   string audience_start = "<audience>";
   string location_start = "<location>";
   string director_start = "<director>";
   string actor_start = "<actor>";
   string released_start = "<released>";
   string season_start = "<season>";
   string episode_start = "<episode>";
   string homepage_start = "<homepage>";
   string source_start = "<source>";
   string movie_stop = "</movie>";
   string tv_stop = "</television>";
   string computer_stop = "</computer>";
   string name_stop = "</name>";
   string audience_stop = "</audience>";
   string location_stop = "</location>";
   string director_stop = "</director>";
   string actor_stop = "</actor>";
   string released_stop = "</released>";
   string season_stop = "</season>";
   string episode_stop = "</episode>";
   string homepage_stop = "</homepage>";
   string source_stop = "</source>";
   string templine;
   string tempName;
   string comm;
   string searchEntry;
   size_t stringPos = 0;
   unsigned int tempInt = 0;
   vector<string> temp(5);
   int i = 0;
   int iReturn = 0;
   kind importKind = NONE;
   Video* importVideo = NULL;
   Link newLink;
   unsigned char words = 0;
   vector<string> nameVec (4);
   vector<unsigned char> dateVec(3);
   int tempPerson, tempVideo;
   
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
         cout << "Lineage: " << newPerson.getLineage() << endl;   */
      }  // if Person
   }  // while
   
   personReader.close();   // close input file
   
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
      }  // while movie start

	  while ((templine.find(tv_start)) < std::string::npos) {
		  templine.erase(0, tv_start.length());
		  importKind = TELEVISION;
		  importVideo = new Television;
	  }  // while television start

	  while ((templine.find(computer_start)) < std::string::npos) {
		  templine.erase(0, computer_start.length());
		  importKind = COMPUTER;
		  importVideo = new Computer;
	  }  // while computer start
      
      while ((templine.find(name_start)) < std::string::npos) {
         if (templine[0] == '\t') templine.erase(0, 1);
         templine.erase(0, name_start.length());
         stringPos = templine.find(name_stop);
         if (stringPos < std::string::npos) {
            templine.erase(stringPos, stringPos + name_stop.length()); }
         importVideo->setName(templine);
      }  // while name
      
      while ((templine.find(audience_start)) < std::string::npos) {
         if (templine[0] == '\t') templine.erase(0, 1);
         templine.erase(0, audience_start.length());
         stringPos = templine.find(audience_stop);
         if (stringPos < std::string::npos) {
            templine.erase(stringPos, stringPos + audience_stop.length()); }
         importVideo->setAudience(templine);
      }  // while audience
      
      while ((templine.find(location_start)) < std::string::npos) {
         if (templine[0] == '\t') templine.erase(0, 1);
         templine.erase(0, location_start.length());
         stringPos = templine.find(location_stop);
         if (stringPos < std::string::npos) {
            templine.erase(stringPos, stringPos + location_stop.length()); }
         importVideo->setLocation(templine);
      }  // while location

	  while ((templine.find(season_start)) < std::string::npos) {
		  if (templine[0] == '\t') templine.erase(0, 1);
		  templine.erase(0, season_start.length());
		  stringPos = templine.find(season_stop);
		  if (stringPos < std::string::npos) {
			  templine.erase(stringPos, stringPos + season_stop.length());
		  }
		  if (typeid(importVideo) == typeid(Television))
			  dynamic_cast<Television*>(importVideo)->setSeason(templine); // TODO: setEpisode not written
	  }  // while season

	  while ((templine.find(episode_start)) < std::string::npos) {
		  if (templine[0] == '\t') templine.erase(0, 1);
		  templine.erase(0, episode_start.length());
		  stringPos = templine.find(episode_stop);
		  if (stringPos < std::string::npos) {
			  templine.erase(stringPos, stringPos + episode_stop.length());
		  }
		  if (typeid(importVideo) == typeid(Television))
			  dynamic_cast<Television*>(importVideo)->setEpisode(templine); // TODO: setEpisode not written
	  }  // while episode

	  while ((templine.find(homepage_start)) < std::string::npos) {
		  if (templine[0] == '\t') templine.erase(0, 1);
		  templine.erase(0, homepage_start.length());
		  stringPos = templine.find(homepage_stop);
		  if (stringPos < std::string::npos) {
			  templine.erase(stringPos, stringPos + homepage_stop.length());
		  }
		  if (typeid(importVideo) == typeid(Computer))
			  dynamic_cast<Computer*>(importVideo)->setHomepage(templine);
	  }  // while homepage

	  while ((templine.find(source_start)) < std::string::npos) {
		  if (templine[0] == '\t') templine.erase(0, 1);
		  templine.erase(0, source_start.length());
		  stringPos = templine.find(source_stop);
		  if (stringPos < std::string::npos) {
			  templine.erase(stringPos, stringPos + source_stop.length());
		  }
		  if (typeid(importVideo) == typeid(Computer))
			  dynamic_cast<Computer*>(importVideo)->setSource(templine);
	  }  // while source
      
      while ((templine.find(director_start)) < std::string::npos) {
         if (templine[0] == '\t') templine.erase(0, 1);
         templine.erase(0, director_start.length());
         stringPos = templine.find(director_stop);
         if (stringPos < std::string::npos) {
            templine.erase(stringPos, stringPos + director_stop.length()); }

         words = split(templine, ' ', nameVec);
         /* note that one hazard of this method is that last names including 
         'del' or 'van' will be split with the first part being counted as
         a middle name.  This will be a problem if such a person does have
         a middle name. */
		 cout << templine;
         newPerson.setName(nameVec.at(0), 0);
         switch (words) {
            case 1:
               break;
            case 2:
               newPerson.setName(nameVec.at(1), 1);
               cout << "Last: " << nameVec.at(1) << endl;
               break;
			case 3:
            /* note that there is no simple way to detect a person with 
            lineage but no middle name. */
               newPerson.setName(nameVec.at(1), 2);
               cout << "Middle: " << nameVec.at(1) << endl;
               newPerson.setName(nameVec.at(2), 1);
               cout << "Last: " << nameVec.at(2) << endl;
               break;
            case 4:
               newPerson.setName(nameVec.at(1), 2);
               cout << "Middle: " << nameVec.at(1) << endl;
               newPerson.setName(nameVec.at(2), 1);
               cout << "Last: " << nameVec.at(2) << endl;
               newPerson.setName(nameVec.at(3), 3);
               cout << "Lineage: " << nameVec.at(3) << endl;
               break;
            default:
               cout << words << "is invalid for: " << templine << endl;
               break;
         }  // switch
         nameVec.resize(0);
         words = 0;

         if (videos.size() == 0) newLink.iMov = 0;
         else newLink.iMov = videos.size() - 1;
         iReturn = searchPeople(persons, newPerson); // returned index of person
         if (iReturn == -1) { // if not already in persons, add it
            persons.push_back(newPerson);
            cout << "Adding new director." << endl;
            newLink.iPer = persons.size() - 1;
         }
         else { // if found,
            newLink.iPer = iReturn;
            cout << "That director is already in the database." << endl;
         }	// else
         directors.push_back(newLink);
      }  // while director

     while ((templine.find(actor_start)) < std::string::npos) {
        if (templine[0] == '\t') templine.erase(0, 1);
        templine.erase(0, actor_start.length());
        stringPos = templine.find(actor_stop);
        if (stringPos < std::string::npos) {
           templine.erase(stringPos, stringPos + actor_stop.length()); }

         words = split(templine, ' ', nameVec);
		 cout << importVideo->getName() << endl;
		 cout << templine << endl;
         newPerson.setName(nameVec.at(0), 0);
         switch (words) {
            case 1:
               break;
            case 2:
               newPerson.setName(nameVec.at(1), 1);
               cout << "Last: " << nameVec.at(1) << endl;
               break;
            case 3:
            /* note that there is no simple way to detect a person with 
            lineage but no middle name. */
               newPerson.setName(nameVec.at(1), 2);
               cout << "Middle: " << nameVec.at(1) << endl;
               newPerson.setName(nameVec.at(2), 1);
               cout << "Last: " << nameVec.at(2) << endl;
               break;
            case 4:
               newPerson.setName(nameVec.at(1), 2);
               cout << "Middle: " << nameVec.at(1) << endl;
               newPerson.setName(nameVec.at(2), 1);
               cout << "Last: " << nameVec.at(2) << endl;
               newPerson.setName(nameVec.at(3), 3);
               cout << "Lineage: " << nameVec.at(3) << endl;
               break;
            default:
               cout << words << "is invalid for: " << templine << endl;
               break;
         }  // switch
         nameVec.resize(0);
         words = 0;

        	if (videos.size() == 0) newLink.iMov = 0;
        	else newLink.iMov = videos.size() - 1;
        	iReturn = searchPeople(persons, newPerson); // returned index of person
        	// cout << "iReturn: " << iReturn << endl;
         if (iReturn == -1) { // if not already in persons, add it
            persons.push_back(newPerson);
            cout << "Adding new actor." << endl;
            newLink.iPer = persons.size() - 1;
         }
         else { // if found,
            newLink.iPer = iReturn;
            cout << "That director is already in the database." << endl;
         }	// else
         actors.push_back(newLink);
     }   // while actor
	 
     while ((templine.find(released_start)) < std::string::npos) {
         if (templine[0] == '\t') templine.erase(0, 1);
         templine.erase(0, released_start.length());
         stringPos = templine.find(released_stop);
         if (stringPos < std::string::npos) {
            templine.erase(stringPos, stringPos + released_stop.length()); }
         words = split(templine, ' ', nameVec);
		// cout << "split\n";
         dateVec.at(0) = atoi(nameVec.at(0).c_str());
	//	 cout << "datv1\n";
         dateVec.at(1) = atoi(nameVec.at(1).c_str());
		// cout << "datev2\n";
         dateVec.at(2) = atoi(nameVec.at(2).c_str());
		 //cout << "datev3\n";
         Date importDate(dateVec.at(0), dateVec.at(1), dateVec.at(2));
		 //cout << "import\n";
         importVideo->setReleased(importDate);
		// cout << "import2\n";
     }   // while released
      
      while ((templine.find(movie_stop)) < std::string::npos) {
         templine.erase(0, movie_stop.length());
         if (importKind != MOVIE) {
            cout << "Wrong importKind" << endl;
            break;
         }  // if
         else {
            videos.push_back(importVideo);
            delete importVideo;
         }  // else
      }  // while movie stop

	  while ((templine.find(tv_stop)) < std::string::npos) {
		  templine.erase(0, tv_stop.length());
		  if (importKind != TELEVISION) {
			  cout << "Wrong importKind" << endl;
			  break;
		  }  // if
		  else {
			  	videos.push_back(importVideo);
            delete importVideo;
		  }  // else
	  }  // while tv stop

	  while ((templine.find(computer_stop)) < std::string::npos) {
		  templine.erase(0, computer_stop.length());
		  if (importKind != COMPUTER) {
			  cout << "Wrong importKind" << endl;
			  break;
		  }  // if
		  else {
			  	videos.push_back(importVideo);
            delete importVideo;
		  }  // else
	  }  // while computer stop
     i++; // increment index store for actors and directors vectors
   }  // while !videoReader.eof()
   
   videoReader.close(); // close input file

   do {
	   cout << endl;
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
		   cout << "people = display entire list of Persons" << endl;
		   cout << "print = print entire list of Videos" << endl;
		   cout << "actors = display actor link table" << endl;
		   cout << "directors = display director link table" << endl;
		   cout << "quit = quit program" << endl;
		   cout << "save = save changes to list of Videos to external file" << endl;
	   } // if help
	   else if (comm == "add") { // add new entry
		   addVideo(videos, persons);
		   cout << "Add sucessful." << endl;
	   }	// if add
	   else if (comm == "description search") {
		   cout << "Enter something to search all episode descriptions (for TV shows):" << endl;
		   getline(cin, searchEntry);
		   for (i = 0; i < videos.size(); ++i) {
			   if (typeid(videos.at(i)) == typeid(Television)) { // FIXME: does this work?
				   if (dynamic_cast<Television*>(videos.at(i))->searchDesc(searchEntry))
					   videos.at(i)->displayAll();
			   }	// if typeid
		   } // for
		   // TODO: else, print error message
	   }
	   else if (comm == "edit" || comm == "loan") {
		   cout << "Enter something to search (be specific): ";
		   getline(cin, searchEntry);
		   matches = searchVideos(videos, searchEntry);
		   if (matches.size() == 0) {
			   cout << "No match found, try again." << endl;
			   continue; // return to top since no matches found
		   }
		   cout << "Do you want to change this (y/n)? " << endl;
		   videos.at(matches.at(0))->displayAll();
		   cout << endl;
		   cin >> templine;
		   if (templine == "n")
			   continue;
		   else if (templine == "y") {
			   // do nothing
		   } // if y
		   else {
			   cout << "not a valid choice" << endl;
			   continue;
		   } // else
		   if (comm == "edit") {
			   cout << "Now choose a field to edit -" << endl;
			   cout << "Name, Audience, Location, release date, viewed date, runtime minutes." << endl;
			   cout << "Choose a field to edit: ";
			   cin >> templine;
			   editVideo(videos.at(matches.at(0)), persons, templine); // call function to edit matched index
		   }	// if edit	
		   else if (comm == "loan")
			   editVideo(videos.at(matches.at(0)), persons, "location");
		   cout << "Update sucessful." << endl; // FIXME: working?
	   } // if edit || loan
	   else if (comm == "help search") {
		   cout << "Fields and format of entry while searching:" << endl;
		   cout << "name - Movie Title Case Sensative" << endl;
		   cout << "date - mm/dd/yy (leading zeros required)" << endl;
		   cout << "audience - G or PG or PG-13 or R" << endl;
		   cout << "location - ex. Bill's House or Garage" << endl;
		   cout << "director - ex. Jackson or Peter Jackson" << endl;
		   cout << "actor - ex. Cruise or Tom Cruise" << endl;
		   cout << "runtime minutes - 135 or 60" << endl;
	   }	// if help search
	   else if (comm == "people") { // print persons
		   for (i = 0; i < persons.size(); ++i) {
			   cout << persons.at(i).getFirstName() << endl;
		   }	// for
	   }	// people
	   else if (comm == "print") { // print videos
		   display(videos, persons, directors, actors);
	   }	// if print
	   else if (comm == "actors") { // print link table
		   for (i = 0; i < actors.size(); ++i) {
			   tempVideo = actors.at(i).iMov;
			   tempPerson = actors.at(i).iPer;
			   cout << videos.at(tempVideo)->getName() << ", " << persons.at(tempPerson).getLastName() << endl;
		   } // for
	   }	// if actors
	   else if (comm == "directors") { // print link table
		   for (i = 0; i < directors.size(); ++i) {
			   tempVideo = directors.at(i).iMov;
			   tempPerson = directors.at(i).iPer;
			   cout << videos.at(tempVideo)->getName() << ", " << persons.at(tempPerson).getLastName() << endl;
		   } // for
	   }	// if directors
	   else if (comm == "quit") {
		   break; // quit program
	   }	// if quit
	   else if (comm == "remove") {
		   cout << "Enter something to remove: ";
		   getline(cin, searchEntry);
		   matches = searchVideos(videos, searchEntry);
		   if (matches.size() != 0) { // if items were matched, then do the following
			   cout << "Do you want to remove all of these results (y/n)? ";
			   cin >> templine;
			   if (templine == "y") {
				   remove(videos, matches);
				   cout << "Items removed." << endl;
			   }
		   }	// if matches
	   } // if remove
	   else if (comm == "save") { // NOT USABLE YET
		   ofstream out;
		   out.open("Videos.dat");
		   if (!out.is_open()) {
			   cout << "Unable to find file to save to." << endl;
			   continue; // TODO: WORKING? should stop save process
		   }
		   // FIXME: I expect it will delete the leading comments without proper precautions
		   for (i = 0; i < videos.size(); ++i) {
			   out << movie_start << endl;
			   out << "\t" << name_start << videos.at(i)->getName() << name_stop << endl;
			   out << "\t" << audience_start << videos.at(i)->getAudience() << audience_stop << endl;
			   out << "\t" << location_start << videos.at(i)->getLocation() << location_stop << endl;
			   out << "\t" << director_start << persons.at(i) << director_stop << endl; // TODO: change operator<< maybe?
			   // TODO: fit mulitple people
			   out << "\t" << actor_start << persons.at(directors.at(i).iPer) << actor_stop << endl;
			   out << "\t" << released_start << videos.at(i)->getReleased() << released_stop << endl;
			   out << movie_stop << endl;
		   }
		   out.close();
	   } // if save
	   else if (comm == "search") { // search vectors for entries
		   cout << "Enter something to search: ";
		   getline(cin, searchEntry);
		   searchVideos(videos, searchEntry); // search videos vector for the searchEntry
	   }	// if search
	   else
		   cout << "Input not recognized.\n";
   } while (comm != "quit"); // end loop
	// continue to allow input until user enters "quit"
   
   #ifdef _WIN32
      system("pause");
   #endif

   return 0;
}  // main()
