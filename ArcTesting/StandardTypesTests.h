#include <Arc/Types.h>
#include <Arc/TestGroup.h>

using namespace Arc;

TestResult Test_Arc_TypeInt8( void )
{
	if (sizeof(int8_t) != 1)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeUInt8( void )
{
	if (sizeof(uint8_t) != 1)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeInt16( void )
{
	if (sizeof(int16_t) != 2)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeUInt16( void )
{
	if (sizeof(uint16_t) != 2)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeInt32( void )
{
	if (sizeof(int32_t) != 4)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeUInt32( void )
{
	if (sizeof(uint32_t) != 4)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeInt64( void )
{
	if (sizeof(int64_t) != 8)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TypeUInt64( void )
{
	if (sizeof(uint64_t) != 8)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

void TestGroup_Arc_StandardTypes( TestGroup& test )
{
	test.addTest("Test_Arc_TypeInt8",   Test_Arc_TypeInt8);
	test.addTest("Test_Arc_TypeUInt8",  Test_Arc_TypeUInt8);
	test.addTest("Test_Arc_TypeInt16",  Test_Arc_TypeInt16);
	test.addTest("Test_Arc_TypeUInt16", Test_Arc_TypeUInt16);
	test.addTest("Test_Arc_TypeInt32",  Test_Arc_TypeInt32);
	test.addTest("Test_Arc_TypeUInt32", Test_Arc_TypeUInt32);
	test.addTest("Test_Arc_TypeInt64",  Test_Arc_TypeInt64);
	test.addTest("Test_Arc_TypeUInt64", Test_Arc_TypeUInt64);
}