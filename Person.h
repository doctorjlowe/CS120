/****************************************************************
File:             Person.h
Description:      class for storing biographical info

Author:           David && Evan
Class:            CSCI 120
Date:             2015 May 13

We hereby certify that this program is entirely our own work.
*****************************************************************/

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

#include "Date.h"

using namespace std;

namespace Vids
{

	class Person	// represents actors and directors
	{	/* David: This is so rudimentary that it might be better to just go 
	with a struct? */ 
	public:
		Person() 
		{
			firstName = "";
			lastName = "";
			middleName = "";
			lineage = ""; /* David: lineage holds "Sr.", "III", etc.  Not sure 
			if there's a better title for this field. */
			Date tempDay;
			birthday = tempDay;
		 }	// default constructor
		
		Person(string fn, string ln = "", string mn = "", string lng = "")
		{
			firstName = fn;
			lastName = ln;
			middleName = mn;
			lineage = lng;
		}	// parameterized constructor
		
		friend ostream& operator<<(ostream&out, const Person& person)
		{
			out << "Name: " << person.firstName;
			if (person.middleName != "") out << ' ' << person.middleName;
			if (person.lastName != "") out << ' ' << person.lastName;
			if (person.lineage != "") out << ", " << person.lineage;
			out << "Born on: " << person.birthday.getDay() << ' ';
			out << person.birthday.getMonth() << ' ' << person.birthday.getYear();
			out << endl;
			return out;
		}	// << overload
		
		/* David: I haven't provided setters as i don't imagine any of these 
		fields will change very often. */
		
		string getFirstName() const { return firstName; }
		string getLastName() const { return lastName; }
		string getMiddleName() const { return middleName; }
		string getLineage() const { return lineage; }

		bool searchPeople(string target) { // will search directors and actors for matching item
			if (firstName.find(target) != string::npos
				|| middleName.find(target) != string::npos
				|| lastName.find(target) != string::npos
				|| lineage.find(target) != string::npos)
				return true;
			return false;
		} // FIXME: doesn't know what directors or actors are if not in header file
	
	private:
		string firstName;
		string lastName;
		string middleName;
		string lineage;
		Date birthday;
		
	};	// end class Person

} // end namespace Video
#endif
