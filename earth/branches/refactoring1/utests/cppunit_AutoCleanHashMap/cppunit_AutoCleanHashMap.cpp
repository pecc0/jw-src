//priject includes
#include "AutoCleanHashMap.h"

//cppunit includes
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

class TestAutoCleanHashMap : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestAutoCleanHashMap );
	/*CPPUNIT_TEST( testFunctionName );*/
	CPPUNIT_TEST_SUITE_END();


public:
	void setUp()
	{
		/*Called befor each test function*/
	}

	void tearDown()
	{
		/*Called after each test function*/
	}

protected:
	/*Test functions go here*/
	/*void testFunctionName() {...}*/


};

CPPUNIT_TEST_SUITE_REGISTRATION( TestAutoCleanHashMap );

int main()
{
	CPPUNIT_NS::TestResult testResult;
	CPPUNIT_NS::TestResultCollector testsCollector;
	testResult.addListener( &testsCollector );
	CPPUNIT_NS::BriefTestProgressListener progress;
	testResult.addListener( &progress );

	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( testResult );

	CPPUNIT_NS::CompilerOutputter outCompiler( &testsCollector, std::cerr );
	outCompiler.write();

	return ( testsCollector.wasSuccessful() ? 0 : 1 );
}
