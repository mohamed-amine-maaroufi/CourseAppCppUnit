


#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

// Note 8 : Again, this main method is fairly standard.So, you can just cut and paste for your test classes.Just change the class name accordingly.
int main(int argc, char* argv[])
{
	// Get the top level suite from the registry
	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);
	bool wasSucessful = runner.run();
	char* c = (char*)malloc(10 * sizeof(char));
	scanf_s(c, "%c");
	return wasSucessful ? 0 : 1;
}
