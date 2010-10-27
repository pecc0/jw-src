//priject includes
#include "JWSphere.h"

//cppunit includes
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

using namespace jw;

class TestJWSphere: public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( TestJWSphere );
		/*CPPUNIT_TEST( testFunctionName );*/
		CPPUNIT_TEST( testOctahedronGetTriangleVertex );
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

	/*Test functions go here*/
	/*void testFunctionName() {...}*/
	void testOctahedronGetTriangleVertex()
	{
		JWSphere shpere;
		//vertexes of triangle 0b000
		CPPUNIT_ASSERT(0b000 == shpere.getTriangleVertex(0b000, 0, 0));
		CPPUNIT_ASSERT(0b001 == shpere.getTriangleVertex(0b000, 0, 1));
		CPPUNIT_ASSERT(0b010 == shpere.getTriangleVertex(0b000, 0, 2));

		//vertexes of triangle 0b001
		CPPUNIT_ASSERT(0b001 == shpere.getTriangleVertex(0b001, 0, 0));
		CPPUNIT_ASSERT(0b000 == shpere.getTriangleVertex(0b001, 0, 1));
		CPPUNIT_ASSERT(0b011 == shpere.getTriangleVertex(0b001, 0, 2));

		//vertexes of triangle 0b010
		CPPUNIT_ASSERT(0b010 == shpere.getTriangleVertex(0b010, 0, 0));
		CPPUNIT_ASSERT(0b110 == shpere.getTriangleVertex(0b010, 0, 1));
		CPPUNIT_ASSERT(0b000 == shpere.getTriangleVertex(0b010, 0, 2));

		//vertexes of triangle 0b011
		CPPUNIT_ASSERT(0b011 == shpere.getTriangleVertex(0b011, 0, 0));
		CPPUNIT_ASSERT(0b000 == shpere.getTriangleVertex(0b011, 0, 1));
		CPPUNIT_ASSERT(0b110 == shpere.getTriangleVertex(0b011, 0, 2));

		//TODO the 3 triangles from the souther hemisphere

		//vertexes of triangle 0b111
		CPPUNIT_ASSERT(0b111 == shpere.getTriangleVertex(0b111, 0, 0));
		CPPUNIT_ASSERT(0b011 == shpere.getTriangleVertex(0b111, 0, 1));
		CPPUNIT_ASSERT(0b110 == shpere.getTriangleVertex(0b111, 0, 2));
	}

};
CPPUNIT_TEST_SUITE_REGISTRATION( TestJWSphere );

int main()
{
	TestJWSphere test;
	test.testOctahedronGetTriangleVertex();

	CPPUNIT_NS::TestResult testResult;
	CPPUNIT_NS::TestResultCollector testsCollector;
	testResult.addListener(&testsCollector);
	CPPUNIT_NS::BriefTestProgressListener progress;
	testResult.addListener(&progress);
	CPPUNIT_NS::TestRunner runner;
	runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	runner.run(testResult);
	CPPUNIT_NS::CompilerOutputter outCompiler(&testsCollector, std::cerr);
	outCompiler.write();

	return (testsCollector.wasSuccessful() ? 0 : 1);
}
