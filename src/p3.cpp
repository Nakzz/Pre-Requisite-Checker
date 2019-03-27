#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "p3.hpp"

//Create a new student with the given name
//DO NOT MODIFY THIS CONSTRUCTOR
Student::Student(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open student data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,grade;
  int courseNum;
  while(getline(ifs,line)) {
//    std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> grade;
    grades[courseNum] = grade;
  }
}

//DO NOT MODIFY THIS CONSTRUCTOR
ClassList::ClassList(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open classlist data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,courseName;
  int courseNum,credits;
  while(getline(ifs,line)) {
//    std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> credits;
    getline(stst,courseName); //Remainder of the line is course name
    courses[courseNum] = {courseName, credits};
  }
}

//TODO Add methods as necessary for compatability with p3.hpp
// You may add additional helper methods
// You may NOT change the required method signatures in p3.hpp
// You are encouraged to use method stubs so that your code will compile and
//   you can test the early pieces of your program.

int main() {
  //TODO Your code here
}
