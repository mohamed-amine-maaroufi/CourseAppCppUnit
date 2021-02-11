# Testing simple course app in using CppUnit

C++ program to create unit tests for simple course application using CppUnit

Download the local copy of CppUnit. Now, unpack the CppUnit archive file to a directory of your choice, in this example we assume it is in the folder of the application "CppUnitTestApp" The above command will create a new directory called 'CppUnitTestApp/cppunit-1.12.1'. Simply go to CppUnitTestApp/cppunit-1.12.1/src and open the CppUnitLibraries.sln in Visual Studio. Right-click on the cppunit project in the Solution Explorer pane and choose Build. After successful compilation, cppunit.lib is produced which we will use for our sample below.
Copy cppunit.lib in the folder "CppUnitTestApp/lib".

Open the application in visual studio (we are usning vs2017).

Modify default project settings, add references to include CppUnit library and header files and include a post-build unit testing command by setting the following from the menu bar:

-  'Project > Properties > C/C++ >  Code Generation > Runtime Library > Multi-threaded Debug DLL' (i.e. expand C/C++ tab, choose 'Code Generation' and choose 'Multithreaded Debug DLL' from 'Runtime Library' combo-box)
-  Go to 'Project > Properties > C/C++ > General'. Put '..\cppunit-1.12.1\include' in the 'Additional Include Directories' text box.
-  Go to 'Project > Properties > Linker > Input'. Put '..\cppunit-1.12.1\lib\cppunit.lib' in the 'Additional Dependences' text box.
-  Go to 'Project > Properties > Build Events > Post-Build Event'. Put '"$(TargetPath)"' in the 'Command Line' textbox . Put 'Unit Tests...' in the 'Description' textbox.

#### Example
In this section, we will describe how you can use CppUnit using an example (the reference section provides the link to download the sample files used for this guide). Take a few minutes to examine the following two classes (.h and .cpp files) to see what they are doing:

- Course.h
```sh
//Course.h
#ifndef Course_h
#define Course_h

#include <string>

class Course {
 public:
  // Default constructor
  Course();

  // Constructor
  Course(std::string nm, int gr);

  // method to get the name of the course
  std::string getCourseName();

  // method to get the grade of the course
  int getCourseGrade();

 private:
  std::string course_name;      // name of this course
  int grade;                    // grade of this course
};
#endif

```

- Course.cpp
```sh
//Course.cpp
#include "Course.h"

// default constructor
Course::Course() {
  course_name = "";
  grade = -1;
}

// constructor
Course::Course(std::string nm, int gr):course_name(nm) {
  grade = gr;
}

// method to get the name of the course
std::string Course::getCourseName() { return course_name; }

// method to get the grade of the course
int Course::getCourseGrade() { return grade; }

```

- Student.h
```sh
//Student.h
#ifndef Student_h
#define Student_h

#include <iostream>
#include <string>
#include "Course.h"

const int MAXNUM = 20;     // Maximum number of courses allowed per student

class Student {
public :
  // Constructor
  Student(std::string nm, std::string no);  
  
  // Method to return student's name
  std::string getStuName();
  
  // Method to return student's number
  std::string getStuNumber();
  
  // Method to assign a grade to a course
  void assignGrade(std::string co, int gr);
  
  // Method to return the grade of a course
  int getGrade(std::string co);
private:
  std::string name;                    // name of the student
  std::string number;                  // the student's number 
  Course course_grades[MAXNUM];        // courses taken by student
  int no_of_courses;                   // the current number of courses taken
};
#endif
```

- TestStudent.h
```sh
//TestStudent.h
#ifndef TestStudent_h
#define TestStudent_h
// Note 1
#include <cppunit/extensions/HelperMacros.h>

class StudentTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
CPPUNIT_TEST_SUITE( StudentTest ); // Note 3 
CPPUNIT_TEST( testConstructor );
CPPUNIT_TEST( testAssignAndRetrieveGrades );
CPPUNIT_TEST_SUITE_END();

public:
void setUp();
void tearDown();

// method to test the constructor
void testConstructor();

// method to test the assigning and retrieval of grades
void testAssignAndRetrieveGrades();
};
#endif

```

Next, create the test class. The following are the test files we wrote for the Student class (called TestStudent.h and TestStudent.cpp):

- Student.cpp
```sh
//Student.cpp
#include "Student.h"

// Constructor
Student::Student(std::string nm, std::string no):name(nm), number(no) {
  no_of_courses = 0;
}

// Method to return student's name
std::string Student::getStuName() { return name; }

// Method to return student's number
std::string Student::getStuNumber() { return number; }

// Method to assign a grade to course
void Student::assignGrade(std::string co, int gr) {
  // check whether the maximum number of courses have been taken
  if (no_of_courses == MAXNUM) {
    std::cout << "You have exceeded the maximum number of courses !\n"; 
    return;
  }
  // create a new course
  Course c(co, gr);
  course_grades[no_of_courses++] = c;
}

// Method to return the grade of a course
int Student::getGrade(std::string co) {
  int i = 0;
  
  while (i < no_of_courses) {
    //check if course name the same as co
    if (course_grades[i].getCourseName() == co)  
      return (course_grades[i].getCourseGrade());
    i++;
  }
  return(-1);
}

```

- TestStudent.cpp
```sh
//TestStudent.cpp
#include <cppunit/config/SourcePrefix.h>
#include "Student.h"
#include "TestStudent.h"

#include <iostream>
#include <string>


void 
StudentTest::setUp()
{
}


void 
StudentTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( StudentTest ); // Note 4 

// method to test the constructor
void StudentTest::testConstructor() {  // Note 5
// create a student object
Student stu("Tan Meng Chee", "94-1111B-13");

// check that the object is constructed correctly - Note 6
std::string student_name = stu.getStuName();
CPPUNIT_ASSERT(student_name == "Tan Meng Chee");
std::string student_number = stu.getStuNumber();
CPPUNIT_ASSERT(student_number == "94-1111B-13");
}

// method to test the assigning and retrieval of grades
void StudentTest::testAssignAndRetrieveGrades() {
// create a student
Student stu("Jimmy", "946302B");

// assign a few grades to this student
stu.assignGrade("cs2102", 60);
stu.assignGrade("cs2103", 70);
stu.assignGrade("cs3215", 80);

// verify that the assignment is correct - Note 7
CPPUNIT_ASSERT_EQUAL(60, stu.getGrade("cs2102"));
CPPUNIT_ASSERT_EQUAL(70, stu.getGrade("cs2103"));

// attempt to retrieve a course that does not exist
CPPUNIT_ASSERT_EQUAL(-1, stu.getGrade("cs21002"));
}

```
Next create the main class to kick start the testing process.

- MainTestApp.cpp
```sh
//MainTestApp.cpp
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char* argv[])
{
// Get the top level suite from the registry
CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

CppUnit::TextUi::TestRunner runner;
runner.addTest(suite);
bool wasSucessful = runner.run();
char* c = (char*) malloc(10 * sizeof (char));
scanf_s (c,"%c");
return wasSucessful ? 0 : 1;
}

```


