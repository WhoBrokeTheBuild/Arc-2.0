#include <Arc/TestGroup.h>

#include <Arc/Types.h>

using namespace Arc;

TestResult Test_ArcCore_TypeInt8( void )
{
	if (sizeof(Arc_int8_t) != 1)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeUInt8( void )
{
	if (sizeof(Arc_uint8_t) != 1)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeInt16( void )
{
	if (sizeof(Arc_int16_t) != 2)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeUInt16( void )
{
	if (sizeof(Arc_uint16_t) != 2)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeInt32( void )
{
	if (sizeof(Arc_int32_t) != 4)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeUInt32( void )
{
	if (sizeof(Arc_uint32_t) != 4)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeInt64( void )
{
	if (sizeof(Arc_int64_t) != 8)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TypeUInt64( void )
{
	if (sizeof(Arc_uint64_t) != 8)
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

void TestGroup_ArcCore_StandardTypes( TestGroup& test )
{
	test.addTest("ArcCore_TypeInt8",   Test_ArcCore_TypeInt8);
	test.addTest("ArcCore_TypeUInt8",  Test_ArcCore_TypeUInt8);
	test.addTest("ArcCore_TypeInt16",  Test_ArcCore_TypeInt16);
	test.addTest("ArcCore_TypeUInt16", Test_ArcCore_TypeUInt16);
	test.addTest("ArcCore_TypeInt32",  Test_ArcCore_TypeInt32);
	test.addTest("ArcCore_TypeUInt32", Test_ArcCore_TypeUInt32);
	test.addTest("ArcCore_TypeInt64",  Test_ArcCore_TypeInt64);
	test.addTest("ArcCore_TypeUInt64", Test_ArcCore_TypeUInt64);
}