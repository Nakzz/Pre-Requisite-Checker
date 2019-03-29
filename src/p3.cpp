#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "p3.hpp"

/**
 * Project:    P3
 * Authors:    Ajmain Naqib
 *
 * Semester:   Spring 2019
 * Course:     CS368
 *
 * Due Date:   March 28th 2019
 * Version:    1.0
 *
 */

using namespace std;

//DO NOT MODIFY THIS CONSTRUCTOR
/**
 * Create a new student with the given name
 *
 * @param name
 */
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

/**
 * Return student's name
 *
 * @return name of the student
 */
string Student::getStudentName() {
	return this->name;
}

/**
 * Print student data
 *
 *@param cl classlist
 */
void Student::printStudent(ClassList& cl) {

	cout << "Student's name is: " << this->name << endl;
//	cout << this->schoolName<< endl;

	string grade, className = "";
	int courseNumber = 0;

	for (auto itS = grades.begin(); itS != grades.end(); ++itS) {

		courseNumber = itS->first;
		grade = itS->second;
		className = cl.getCourseName(courseNumber);

		if (className != "")
			cout << " " << className << ": " << grade << endl;

	}

}

//DO NOT MODIFY THIS CONSTRUCTOR
/**
 * Load classlist info from file
 *
 * @param name
 */
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

/**
 * Print the entire classlist
 *
 */
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

/**
 * Returns the name of course maping to the course number
 *
 * @return name of course
 * @param number of ourse
 */
string ClassList::getCourseName(int courseNumber) {
	string className = "";
	int classNum = 0;

	for (auto it = courses.begin(); it != courses.end(); ++it) {

		classNum = it->first;
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
 *
 * @param name
 */
OutsideClassList::OutsideClassList(string name) :
		ClassList(name) {
}

/**
 * Print the entire classlist..
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
 *
 *@param cl classlist
 */
void OutsideClassList::printClassList(ClassList& cl) {
	string className = "";
	int classNum, outsideClassNum = 0;
	string outsideClassName = "";

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
			cout << classNum << " " << className << " " << outsideClassName
					<< endl;

		}

	}
}

/**
 * Get the equivalent course
 * pass it a reference to the UW-Madison list and display the outside classes that have UW-Madison equivalents
 *
 * @param courseNumber
 */
int OutsideClassList::getCourseEquivalent(int courseNumber) {
	int classNum, outsideClassNum = 0;
	for (auto it = courses.begin(); it != courses.end(); ++it) {
		classNum = it->second.second;
		outsideClassNum = it->first;

		if (courseNumber == outsideClassNum) {

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
 *
 * @param name of the stsudent
 * @param name of the school
 */
StudentWithTransferCredit::StudentWithTransferCredit(string name,
		string schoolName) :
		Student(name) {
	this->schoolName = schoolName;
}
/**
 * Return name of student's former school
 *
 * @return name of the school
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
 *
 * @param oldSchool classlist of old school
 *  *@param newSchool classlist of new school
 */
void StudentWithTransferCredit::printStudent(OutsideClassList& oldSchool,
		ClassList& newSchool) {

	cout << "New student's name is: " << this->name << endl;
//	cout << this->schoolName<< endl;

	string grade, className = "";
	int outsideClassNum = 0;
	for (auto it = grades.begin(); it != grades.end(); ++it) {
		grade = it->second;
		outsideClassNum = it->first;
		className = newSchool.getCourseName(
				oldSchool.getCourseEquivalent(outsideClassNum));

//		if(courseNumber == outsideClassNum){
		if (className != "")
			cout << " " << className << ": " << grade << endl;
//			return classNum;

//		}
	}

}

/**
 * Driver method for the application
 *
 */
int main() {

	std::string classListName;
	std::string outsideClassListName;
	std::string transferStudent;

	//TEST VARS
//	classListName = "UWMadison";
//	outsideClassListName = "TestSchool";
//	transferStudent = "TestTransferStudent";

	//	ask for classlist
	cout << "WELCOME TO THE PREREQ-CHECKER" << endl;
	cout << "Classlist: ";
	cin >> classListName;

	//Print classlist name
	ClassList classL = ClassList(classListName);
	classL.printClassList();

	//	ask for outsideclasslist
	cout << "Classlist: ";
	cin >> outsideClassListName;

	//Print outside classlist name
	OutsideClassList outClass = OutsideClassList(outsideClassListName);
	outClass.printClassList();
	outClass.printClassList(classL);

//	ask for transferstudent
	cout << "Name of student: ";
	cin >> transferStudent;

//	print transferstudent"
	StudentWithTransferCredit transferStu = StudentWithTransferCredit(
			transferStudent, outsideClassListName);
	transferStu.printStudent(outClass, classL);

//Student testS = Student("TestStudent");
//
//testS.printStudent(classL);

}
