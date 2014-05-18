#include <Arc/TestGroup.h>

#include <Arc/StringFunctions.h>

#include <iostream>

using namespace Arc;

TestResult Test_ArcCore_Basename( void )
{
	string filePath = "C:\\Testing\\Directory\\File.txt";
	string basename = Arc_Basename(filePath);

	if (basename != "File.txt")
		return TestGroup::Failure("Invalid Result for Windows-Style Paths");

	filePath = "/Testing/Directory/File.txt";
	basename = Arc_Basename(filePath);

	if (basename != "File.txt")
		return TestGroup::Failure("Invalid Result for Linux-Style Paths");

	return TestGroup::Success();
}

TestResult Test_ArcCore_Dirname( void )
{
	string filePath = "C:\\Testing\\Directory\\File.txt";
	string dirname = Arc_Dirname(filePath);

	if (dirname != "C:\\Testing\\Directory")
		return TestGroup::Failure("Invalid Result for Windows-Style Paths");

	filePath = "/Testing/Directory/File.txt";
	dirname = Arc_Dirname(filePath);

	if (dirname != "/Testing/Directory")
		return TestGroup::Failure("Invalid Result for Linux-Style Paths");

	return TestGroup::Success();
}

// TODO: Add Test_Arc_FileExtension

TestResult Test_ArcCore_StringGetLower( void )
{
	string testToLower = "aBcDeFg";

	string result = Arc_StringGetLower(testToLower);

	if (result != "abcdefg")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringToLower( void )
{
	string testToLower = "aBcDeFg";

	Arc_StringToLower(testToLower);

	if (testToLower != "abcdefg")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringGetUpper( void )
{
	string testToUpper = "aBcDeFg";

	string result = Arc_StringGetUpper(testToUpper);

	if (result != "ABCDEFG")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringToUpper( void )
{
	string testToUpper = "aBcDeFg";

	Arc_StringToUpper(testToUpper);

	if (testToUpper != "ABCDEFG")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringGetUCWords( void )
{
	string testUCWords = "hello world";

	string result = Arc_StringGetUCWords(testUCWords);

	if (result != "Hello World")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringUCWords( void )
{
	string testUCWords = "hello world";

	Arc_StringUCWords(testUCWords);

	if (testUCWords != "Hello World")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringGetUCFirst( void )
{
	string testUCFirst = "hello world";

	string result = Arc_StringGetUCFirst(testUCFirst);

	if (result != "Hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringUCFirst( void )
{
	string testUCFirst = "hello world";

	Arc_StringUCFirst(testUCFirst);

	if (testUCFirst != "Hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TrimLeft( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	Arc_TrimLeft(testTrim);

	if (testTrim != "hello world  \r\n\t")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_TrimRight( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	Arc_TrimRight(testTrim);

	if (testTrim != "\r\n\t  hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_Trim( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	Arc_Trim(testTrim);

	if (testTrim != "hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_GetTrimLeft( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	string result = Arc_GetTrimLeft(testTrim);

	if (result != "hello world  \r\n\t")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_GetTrimRight( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	string result = Arc_GetTrimRight(testTrim);

	if (result != "\r\n\t  hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_GetTrim( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	string result = Arc_GetTrim(testTrim);

	if (result != "hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringSplit( void )
{
	string testSplit = "a,b,c";

	ArrayList<string> splitResult = Arc_StringSplit(testSplit, ',');

	if (splitResult[0] != "a" || splitResult[1] != "b" || splitResult[2] != "c")
		return TestGroup::Failure("Invalid Result with character separator");

	testSplit = "a//b//c";

	splitResult = Arc_StringSplit(testSplit, "//");

	if (splitResult[0] != "a" || splitResult[1] != "b" || splitResult[2] != "c")
		return TestGroup::Failure("Invalid Result with string separator");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringJoin( void )
{
	ArrayList<string> testJoin;
	testJoin.add("a");
	testJoin.add("b");
	testJoin.add("c");

	string result = Arc_StringJoin(",", testJoin);

	if (result != "a,b,c")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_Substring( void )
{
	string testSubstr = "Hello, World!";

	string result = Arc_Substring(testSubstr, 2);

	if (result != "llo, World!")
		return TestGroup::Failure("Invalid Result without a Max Length specified");

	result = Arc_Substring(testSubstr, 2, 6);

	if (result != "llo, W")
		return TestGroup::Failure("Invalid Result with a Max Length specified");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringReplaceAll( void )
{
	string testReplaceAll = "abc 123 a bc, abcabc";

	Arc_StringReplaceAll(testReplaceAll, "abc", "qwerty");

	if (testReplaceAll != "qwerty 123 a bc, qwertyqwerty")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_ArcCore_StringReplaceNext( void )
{
	string testReplaceNext = "abc 123 a bc, abcabc";

	Arc_StringReplaceNext(testReplaceNext, "abc", "qwerty");
	Arc_StringReplaceNext(testReplaceNext, "abc", "qwerty");

	if (testReplaceNext != "qwerty 123 a bc, qwertyabc")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

void TestGroup_ArcCore_StringFunctions( TestGroup& test )
{
	test.addTest("ArcCore_Basename",          Test_ArcCore_Basename);
	test.addTest("ArcCore_Dirname",           Test_ArcCore_Dirname);

	test.addTest("ArcCore_StringGetLower",    Test_ArcCore_StringGetLower);
	test.addTest("ArcCore_StringToLower",     Test_ArcCore_StringToLower);

	test.addTest("ArcCore_StringGetUpper",    Test_ArcCore_StringGetUpper);
	test.addTest("ArcCore_StringToUpper",     Test_ArcCore_StringToUpper);

	test.addTest("ArcCore_StringGetUCWords",  Test_ArcCore_StringGetUCWords);
	test.addTest("ArcCore_StringUCWords",	  Test_ArcCore_StringUCWords);

	test.addTest("ArcCore_StringGetUCFirst",  Test_ArcCore_StringGetUCFirst);
	test.addTest("ArcCore_StringUCFirst",     Test_ArcCore_StringUCFirst);

	test.addTest("ArcCore_TrimLeft",          Test_ArcCore_TrimLeft);
	test.addTest("ArcCore_TrimRight",         Test_ArcCore_TrimRight);
	test.addTest("ArcCore_Trim",              Test_ArcCore_Trim);

	test.addTest("ArcCore_GetTrimLeft",       Test_ArcCore_GetTrimLeft);
	test.addTest("ArcCore_GetTrimRight",      Test_ArcCore_GetTrimRight);
	test.addTest("ArcCore_GetTrim",           Test_ArcCore_GetTrim);

	test.addTest("ArcCore_StringSplit",       Test_ArcCore_StringSplit);
	test.addTest("ArcCore_StringJoin",        Test_ArcCore_StringJoin);

	test.addTest("ArcCore_Substring",         Test_ArcCore_Substring);

	test.addTest("ArcCore_StringReplaceAll",  Test_ArcCore_StringReplaceAll);
	test.addTest("ArcCore_StringReplaceNext", Test_ArcCore_StringReplaceNext);
}