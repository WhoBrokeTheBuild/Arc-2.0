#include <Arc/TestGroup.h>

#include <Arc/RandomFunctions.h>

using namespace Arc;

const int TEST_ARC_RAND_SAMPLE_SIZE = 200;

TestResult Test_ArcCore_RandInt( void )
{
	bool passed = true;
	int intMin = -10, intMax = 10;

	for (int i = 0; i < TEST_ARC_RAND_SAMPLE_SIZE; ++i)
	{
		int rand = Arc_RandInt(intMin, intMax);
		if (rand < intMin || rand > intMax)
			passed = false;
	}
	
	if ( ! passed)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_RandFloat( void )
{
	bool passed = true;
	float fltMin = -10.0f, fltMax = 10.0f;

	for (int i = 0; i < TEST_ARC_RAND_SAMPLE_SIZE; ++i)
	{
		float rand = Arc_RandFloat(fltMin, fltMax);
		if (rand < fltMin || rand > fltMax)
			passed = false;
	}

	if ( ! passed)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_RandDouble( void )
{
	bool passed = true;
	double dblMin = -10.0, dblMax = 10.0;

	for (int i = 0; i < TEST_ARC_RAND_SAMPLE_SIZE; ++i)
	{
		double rand = Arc_RandDouble(dblMin, dblMax);
		if (rand < dblMin || rand > dblMax)
			passed = false;
	}

	if ( ! passed)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

void TestGroup_ArcCore_RandomFunctions( TestGroup& test )
{
	test.addTest("ArcCore_RandInt",    Test_ArcCore_RandInt);
	test.addTest("ArcCore_RandFloat",  Test_ArcCore_RandFloat);
	test.addTest("ArcCore_RandDouble", Test_ArcCore_RandDouble);
}