//priject includes
#include "JWTriangle.h"

//cppunit includes
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

class TestJWTriangle : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestJWTriangle );
	/*CPPUNIT_TEST( testFunctionName );*/
	CPPUNIT_TEST( testIsUpside );
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

	void testIsUpside()
	{
		JWTriangle triangle(0b000, 0b001, 0b100, 0b010);

		CPPUNIT_ASSERT( triangle.isUpside() );
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestJWTriangle );

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