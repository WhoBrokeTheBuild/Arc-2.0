#include <Arc/StringFunctions.h>
#include <Arc/TestGroup.h>

#include <iostream>

using namespace Arc;

TestResult Test_Arc_Basename( void )
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

TestResult Test_Arc_Dirname( void )
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

TestResult Test_Arc_StringGetLower( void )
{
	string testToLower = "aBcDeFg";

	string result = Arc_StringGetLower(testToLower);

	if (result != "abcdefg")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringToLower( void )
{
	string testToLower = "aBcDeFg";

	Arc_StringToLower(testToLower);

	if (testToLower != "abcdefg")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringGetUpper( void )
{
	string testToUpper = "aBcDeFg";

	string result = Arc_StringGetUpper(testToUpper);

	if (result != "ABCDEFG")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringToUpper( void )
{
	string testToUpper = "aBcDeFg";

	Arc_StringToUpper(testToUpper);

	if (testToUpper != "ABCDEFG")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringGetUCWords( void )
{
	string testUCWords = "hello world";

	string result = Arc_StringGetUCWords(testUCWords);

	if (result != "Hello World")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringUCWords( void )
{
	string testUCWords = "hello world";

	Arc_StringUCWords(testUCWords);

	if (testUCWords != "Hello World")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringGetUCFirst( void )
{
	string testUCFirst = "hello world";

	string result = Arc_StringGetUCFirst(testUCFirst);

	if (result != "Hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringUCFirst( void )
{
	string testUCFirst = "hello world";

	Arc_StringUCFirst(testUCFirst);

	if (testUCFirst != "Hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TrimLeft( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	Arc_TrimLeft(testTrim);

	if (testTrim != "hello world  \r\n\t")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_TrimRight( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	Arc_TrimRight(testTrim);

	if (testTrim != "\r\n\t  hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_Trim( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	Arc_Trim(testTrim);

	if (testTrim != "hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_GetTrimLeft( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	string result = Arc_GetTrimLeft(testTrim);

	if (result != "hello world  \r\n\t")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_GetTrimRight( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	string result = Arc_GetTrimRight(testTrim);

	if (result != "\r\n\t  hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_GetTrim( void )
{
	string testTrim = "\r\n\t  hello world  \r\n\t";

	string result = Arc_GetTrim(testTrim);

	if (result != "hello world")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringSplit( void )
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

TestResult Test_Arc_StringJoin( void )
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

TestResult Test_Arc_Substring( void )
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

TestResult Test_Arc_StringReplaceAll( void )
{
	string testReplaceAll = "abc 123 a bc, abcabc";

	Arc_StringReplaceAll(testReplaceAll, "abc", "qwerty");

	if (testReplaceAll != "qwerty 123 a bc, qwertyqwerty")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

TestResult Test_Arc_StringReplaceNext( void )
{
	string testReplaceNext = "abc 123 a bc, abcabc";

	Arc_StringReplaceNext(testReplaceNext, "abc", "qwerty");
	Arc_StringReplaceNext(testReplaceNext, "abc", "qwerty");

	if (testReplaceNext != "qwerty 123 a bc, qwertyabc")
		return TestGroup::Failure("Invalid Result");

	return TestGroup::Success();
}

void TestGroup_Arc_StringFunctions( TestGroup& test )
{
	test.addTest("Arc_Basename",          Test_Arc_Basename);
	test.addTest("Arc_Dirname",           Test_Arc_Dirname);

	test.addTest("Arc_StringGetLower",    Test_Arc_StringGetLower);
	test.addTest("Arc_StringToLower",     Test_Arc_StringToLower);

	test.addTest("Arc_StringGetUpper",    Test_Arc_StringGetUpper);
	test.addTest("Arc_StringToUpper",     Test_Arc_StringToUpper);

	test.addTest("Arc_StringGetUCWords",  Test_Arc_StringGetUCWords);
	test.addTest("Arc_StringUCWords",	  Test_Arc_StringUCWords);

	test.addTest("Arc_StringGetUCFirst",  Test_Arc_StringGetUCFirst);
	test.addTest("Arc_StringUCFirst",     Test_Arc_StringUCFirst);

	test.addTest("Arc_TrimLeft",          Test_Arc_TrimLeft);
	test.addTest("Arc_TrimRight",         Test_Arc_TrimRight);
	test.addTest("Arc_Trim",              Test_Arc_Trim);

	test.addTest("Arc_GetTrimLeft",       Test_Arc_GetTrimLeft);
	test.addTest("Arc_GetTrimRight",      Test_Arc_GetTrimRight);
	test.addTest("Arc_GetTrim",           Test_Arc_GetTrim);

	test.addTest("Arc_StringSplit",       Test_Arc_StringSplit);
	test.addTest("Arc_StringJoin",        Test_Arc_StringJoin);

	test.addTest("Arc_Substring",         Test_Arc_Substring);

	test.addTest("Arc_StringReplaceAll",  Test_Arc_StringReplaceAll);
	test.addTest("Arc_StringReplaceNext", Test_Arc_StringReplaceNext);
}