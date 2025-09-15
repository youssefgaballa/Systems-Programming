#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

/*
 * This class represents a Student object
 * where each instance has an id, last name,
 * first name, and gpa. 
 * Last name and first name are pointers to
 * strings stored on the heap.
 * This class also keeps track of the number
 * of students.
 */
class Student{

 private:
  // This student's id.
  unsigned long id;
  // A pointer to this student's last name.
  string * lastName;
  // A pointer to this student's first name.
  string * firstName;
  // This student's gpa (grade point average).
  double gpa;
  // The total number of student objects.
  static int numberOfStudents;

 public:
  /*
   * Default constructor initializes id to zero, gpa to zero,
   * first name to none, and last name to none.
   */
  Student();
  
  /*
   * Constructor that initializes based on its four input parameters.
   */
  Student(unsigned long id, string &lastName, string &firstName, double gpa);
  
  /*
   * Destructor deallocates memory for first name and last name.
   */
  ~Student();
  
  /*
   * Return this student's id.
   */
  unsigned long getId();
  
  /*
   * Return a copy of this student's last name.
   */
  string getLastName();
  
  /*
   * Return a copy of this student's first name.
   */
  string getFirstName();
  
  /*
   * Return this student's gpa.
   */
  double getGpa();

  /*
   * Set this student's gpa to the gpa parameter
   */
  void setGpa(double gpa);

  /*
   * Return the number of students.
   */
  static int getNumberOfStudents();

  /*
   * Print this student's data to standard output.
  */
  void print();  
};

int Student::numberOfStudents = 0;

Student::Student(){
  id = 0;
  lastName = new string("none");
  firstName = new string("none");
  gpa = 0.0;
  numberOfStudents++;
}

Student::Student(unsigned long id, string &lastName, string &firstName, double gpa){
  this->id = id;
  this->lastName = new string(lastName);
  this->firstName = new string(firstName);
  this->gpa = gpa;
  numberOfStudents++;
}

Student::~Student(){
  delete lastName;
  delete firstName;
  numberOfStudents--;
}

unsigned long Student::getId(){
  return this->id;
}

string Student::getLastName(){
  return *(this->lastName);
}

string Student::getFirstName(){
  return *firstName;
}

double Student::getGpa(){
  return gpa;
}

void Student::setGpa(double gpa){
  this->gpa = gpa;
}

int Student::getNumberOfStudents(){
  return numberOfStudents;
}

void Student::print(){
  cout << id << ", ";
  cout << *lastName << ", ";
  cout << *firstName << ", ";
  cout << gpa << endl;
}

#endif
