#include <iostream>
#include <string>
#include <list>
#include "Student.h"
#include "StudentSort.h"
using namespace std;

/*
 * Initialize classList, a list of Student *, 
 * from fileName in the present working directory.
 *
 */
void initializeFromFile(list<Student *> &classList, char * fileName){
  FILE * fptr = fopen(fileName, "r");
  unsigned long id = 0;
  char lastName[100];
  char firstName[100];
  double gpa = 0;
  while(fscanf(fptr, "%lu %s %s %lf\n", &id, lastName, firstName, &gpa) > 0){
    string last = lastName;
    string first = firstName;
    Student * s = new Student(id, last, first, gpa);
    classList.push_back(s);
  }
  fclose(fptr);
}

/*
 * This program will process a command line argument as shown below
 *   ./main.out <studentFile> 
 * where <studentFile> is the name of the file in the present
 * working directory that contains students formatted by the following:
 * id lastName firstName gpa
 * where gpa is followed by a newline character.
 */
int main(int argc, char ** argv){

  if(argc != 2){
    cout << "Error: must have two command line arguments as shown below." << endl;
    cout << "./main.out studentList.txt" << endl;
  }
  else{
    list<Student *> classRoll;
    cout << "Number of students = " << Student::getNumberOfStudents() << endl;
    initializeFromFile(classRoll, argv[1]);
    for(Student * s : classRoll){
      s->print();
    }
    cout << "Number of students = " << Student::getNumberOfStudents() << endl;
        
    cout << "Sorting students by id" << endl;
    studentSort(classRoll, 1);
    list<Student *>::iterator itor;
    for(itor = classRoll.begin(); itor != classRoll.end(); itor++) (*itor)->print();
    
    cout << "Sorting students by last name then by first name" << endl;
    studentSort(classRoll, 2);
    for(itor = classRoll.begin(); itor != classRoll.end(); itor++) (*itor)->print();
    
    cout << "Sorting students by gpa" << endl;
    studentSort(classRoll, 3);
    for(Student * s : classRoll) s->print();

    cout << "Student with a min gpa: ";
    itor = classRoll.begin();    
    cout << (*itor)->getFirstName() << " " << (*itor)->getLastName() << endl;
    
    cout << "Student with a max gpa: ";
    itor = classRoll.end();
    itor--;
    cout << (*itor)->getFirstName() << " " << (*itor)->getLastName() << endl;
    
    cout << "Student with a second highest gpa: ";
    itor--;
    cout << (*itor)->getFirstName() << " " << (*itor)->getLastName() << endl;

    
    for(Student * s: classRoll){
      delete s;
    }
    cout << "Number of students = " << Student::getNumberOfStudents() << endl;  
  }
  return 0;
}
