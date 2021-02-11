#ifndef TestStudent_h
#define TestStudent_h

//Note 1 : Remember to include this header files : <cppunit / extensions / HelperMacros.h> in all the header files(.h) of the test classes you are implementing.
#include <cppunit/extensions/HelperMacros.h>

class StudentTest : public CPPUNIT_NS::TestFixture // Note 2 : Every test class that you wrote must inherit the class CPPUNIT_NS::TestFixture.
{
	//Note 3 : This set of statements are used to assemble a suite of tests.It's also fairly standard. 
	// Just cut and paste and change accordingly to suit your needs. In particular, change StudentTest to the name of your test class and substitute those various test method names with your own.
	CPPUNIT_TEST_SUITE(StudentTest); 
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testAssignAndRetrieveGrades);
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


