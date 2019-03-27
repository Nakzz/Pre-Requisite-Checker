#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "p3.hpp"

using namespace std;

//Create a new student with the given name
//DO NOT MODIFY THIS CONSTRUCTOR
Student::Student(std::string name) {
	std::ifstream ifs(name + ".txt");
	if (!ifs.is_open()) {
		std::cout << "ERROR: Unable to open student data file " + name + ".txt"
				<< std::endl;
		return;
	}
	this->name = name;
	std::string line, grade;
	int courseNum;
	while (getline(ifs, line)) {
//    std::cout << "Read line: " << line << std::endl;
		std::stringstream stst;
		stst << line;
		stst >> courseNum >> grade;
		grades[courseNum] = grade;
	}
}

string Student::getStudentName(){
	return this->name;
}

/**
 * Print student data
 *TODO: finish implementing from result
 */
void Student::printStudent(ClassList& cl) {

	for (auto itS = grades.begin(); itS != grades.end(); ++itS) {

		auto courseNumber = itS->first;
		auto courseName = cl.getCourseName(courseNumber);

		cout << "	Searching for coursenum:  " << courseNumber << " found: "
				<< courseName << endl;
//			if (courseNumber == it->first){
//				cout << "returning courseName : " << it->second.first << endl; // Prints name
//
//			}

	}

}

//DO NOT MODIFY THIS CONSTRUCTOR
ClassList::ClassList(std::string name) {
	std::ifstream ifs(name + ".txt");
	if (!ifs.is_open()) {
		std::cout
				<< "ERROR: Unable to open classlist data file " + name + ".txt"
				<< std::endl;
		return;
	}
	this->name = name;
	std::string line, courseName;
	int courseNum, credits;
	while (getline(ifs, line)) {
//    std::cout << "Read line: " << line << std::endl;
		std::stringstream stst;
		stst << line;
		stst >> courseNum >> credits;
		getline(stst, courseName); //Remainder of the line is course name
		courses[courseNum] = {courseName, credits};
	}
}

void ClassList::printClassList() {
	for (auto it = courses.begin(); it != courses.end(); ++it) {
		std::cout << "courses : " << it->first << std::endl;
	}
}

string ClassList::getCourseName(int courseNumber) {
	for (auto it = courses.begin(); it != courses.end(); ++it) {

		if (courseNumber == it->first) {
//			cout << it->first <<" courseName : " << it->second.first << endl; // Prints name
			return it->second.first;
		}
//		else {
//			cout << " NOT FOUND : " << courseNumber << endl; // course not found name
//		}
	}

	return "";
}

/**
 * OutsideClassList Constructor that Loads classlist info from file
 */
OutsideClassList::OutsideClassList(string name) :
		ClassList(name) {
}

/**
 * Print the entire classlist.
 * printClassList() should still display the entire classlist, but since we no longer have credit counts
 * we'll want to reimplement this method to just show the course numbers and names.
 */
void OutsideClassList::printClassList() {
//	ClassList::printClassList();
	//TODO: must implement
}

/**
 * Print the classes that transfer with their equivalents
 */
void OutsideClassList::printClassList(ClassList& cl) {
	//TODO: must implement
}

/**
 * Get the equivalent course
 * pass it a reference to the UW-Madison list and display the outside classes that have UW-Madison equivalents
 */
int OutsideClassList::getCourseEquivalent(int courseNumber) {
	//TODO: must implement
}

/**
 * Constructor class that loads student info from file
 */
StudentWithTransferCredit::StudentWithTransferCredit(std::string name, std::string schoolName){
	//TODO: must implement
}

/**
 * Return name of student's former school
 */
std::string StudentWithTransferCredit::getSchoolName(){
	return this->schoolName;
}

/**
 * Prints student data
 */
void StudentWithTransferCredit::printStudent(OutsideClassList& oldSchool, ClassList& newSchool){
	//TODO: must implement
}

int main() {
//	ClassList("UWMadison").printClassList();

//	ClassList("UWMadison").getCourseName(520);

//	ClassList classL = ClassList("UWMadison");

//	Student("TestStudent").printStudent(classL);

	OutsideClassList outClass = OutsideClassList("TestSchool");

	outClass.printClassList();

}
