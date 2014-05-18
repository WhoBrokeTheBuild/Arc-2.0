#include <Arc/TestGroup.h>

#include <Arc/IPAddress.h>

using namespace Arc;

TestResult Test_ArcNet_IPAddress_ZERO( void )
{
	const IPAddress zero = IPAddress::ZERO;

	if (zero.getA() != 0)
		return TestGroup::Failure("Octet A is incorrect");

	if (zero.getB() != 0)
		return TestGroup::Failure("Octet B is incorrect");

	if (zero.getC() != 0)
		return TestGroup::Failure("Octet C is incorrect");

	if (zero.getD() != 0)
		return TestGroup::Failure("Octet D is incorrect");

	return TestGroup::Success();
}

TestResult Test_ArcNet_IPAddress_operator_equals( void )
{
	IPAddress a = IPAddress(1, 2, 3, 4);
	IPAddress b = IPAddress(1, 2, 3, 4);
	IPAddress c = IPAddress(2, 4, 6, 8);

	if (a == c)
		return TestGroup::Failure("1.2.3.4 == 2.4.6.8");

	if (! (a == b))
		return TestGroup::Failure("1.2.3.4 != 1.2.3.4");

	return TestGroup::Success();
}

TestResult Test_ArcNet_IPAddress_operator_not_equals( void )
{
	if ()
		return TestGroup::Failure("");

	return TestGroup::Success();
}

void TestGroup_ArcNet_IPAddress( TestGroup& test )
{
	test.addTest("ArcNet_IPAddress_ZERO", Test_ArcNet_IPAddress_ZERO);
	test.addTest("ArcNet_IPAddress_operator_equals", Test_ArcNet_IPAddress_operator_equals);
}