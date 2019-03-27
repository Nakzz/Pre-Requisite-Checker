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

string Student::getStudentName() {
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

//		cout << "	Searching for coursenum:  " << courseNumber << " found: "
//				<< courseName << endl;
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
	cout << this->name << endl;
	cout << "Size:  " << courses.size() << endl;
	string className = "";
	int classNum = 0;
	int classCr = 0;

	for (auto it = courses.begin(); it != courses.end(); ++it) {
		className = it->second.first;
		classNum = it->first;
		classCr = it->second.second;
		cout << " " << className << "	" << classNum << "	" << classCr << endl;
	}
}

string ClassList::getCourseName(int courseNumber) {
	string className = "";
		int classNum = 0;


	for (auto it = courses.begin(); it != courses.end(); ++it) {

		classNum= it->first;
		className = it->second.first;

		if (courseNumber == classNum) {
			//cout << "          "<< it->first <<" courseName : " << it->second.first << endl; // Prints name
			return className;
		}
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


	cout << this->name << endl;
	cout << "Size:  " << courses.size() << endl;
		string className = "";
		int classNum = 0;

		for (auto it = courses.begin(); it != courses.end(); ++it) {
			className = it->second.first;
			classNum = it->first;
			cout << " " << className << "	" << classNum << "	" << endl;
		}
}

/**
 * Print the classes that transfer with their equivalents
 */
void OutsideClassList::printClassList(ClassList& cl) {
	string className = "";
	int classNum, outsideClassNum = 0;
	string outsideClassName ="";

	cout << this->name << endl;
	cout << "Size:  " << courses.size() << endl;

	for (auto it = courses.begin(); it != courses.end(); ++it) {
		outsideClassName = it->second.first;
		outsideClassNum = it->first;
		classNum = this->getCourseEquivalent(outsideClassNum);
		className = cl.getCourseName(classNum);




// Print UW course num, UW Course name, outside course name
		// if classNum ==0, dont print

				if (classNum != 0) {
			cout << classNum<< " " << className << " "  << outsideClassName << endl;

		}


	}
}

/**
 * Get the equivalent course
 * pass it a reference to the UW-Madison list and display the outside classes that have UW-Madison equivalents
 */
int OutsideClassList::getCourseEquivalent(int courseNumber) {
	int classNum, outsideClassNum = 0;
	for (auto it = courses.begin(); it != courses.end(); ++it) {
		classNum = it->second.second;
		outsideClassNum = it->first;


		if(courseNumber == outsideClassNum){

//			cout << "MATCH FOUND FOR: " << outsideClassNum << " => " << classNum << endl;
			return classNum;


		}
	}

	return classNum;
}

/**
 * Constructor class that loads student info from file
 *
 * Functions identically to the super class constructor, except that it also fills in the new field.
 */
//StudentWithTransferCredit::StudentWithTransferCredit(std::string name,
//		std::string schoolName) {
//	//TODO: must implement
//}
/**
 * Return name of student's former school
 */
std::string StudentWithTransferCredit::getSchoolName() {
	return this->schoolName;
}

/**
 * Prints student data
 *
 * The internal record within a StudentWithTransferCredit instance has their grades matched to the course
 *  numbers from their old school. printStudent() should figure out which entries have a matching course
 *  in the newSchool ClassList and display only those courses, along with the corresponding grades.
 */
void StudentWithTransferCredit::printStudent(OutsideClassList& oldSchool,
		ClassList& newSchool) {
	//TODO: must implement
}

/**
 * Driver method for the application
 *
 * In your main method, ask for the "new" classlist and print it. Then ask for the "old" outsideclasslist
 * and print it twice (first using the no-parameter print and then using the "new" classlist as a parameter).
 * Finally, ask for the name of a student-with-transfer-credit and print that student's class record using
 * the "old" and "new" classlists above.
 */
int main() {

	std::string classListName;
	std::string outsideClassListName;

	//TEST VARS
	classListName= "UWMadison";
	outsideClassListName = "TestSchool";


	cout << "WELCOME TO THE PREREQ-CHECKER" << endl;
	cout << "Classlist: ";
//	cin >> classListName;


	//Print classlist name
	ClassList classL = ClassList(classListName);
	classL.printClassList();

	cout << "Classlist: ";
//	cin >> outsideClassListName;


	//Print outside classlist name
	OutsideClassList outClass = OutsideClassList(outsideClassListName);
	outClass.printClassList();
	outClass.printClassList(classL);

//	ClassList("UWMadison").printClassList();

//	ClassList("UWMadison").getCourseName(520);

//	Student("TestStudent").printStudent(classL);

//	OutsideClassList outClass = OutsideClassList("TestSchool");
//
//	outClass.printClassList();

}
