#include <iostream>

#include <Arc/ArcCore.h>
#include <Arc/ArcAudio.h>
#include <Arc/ArcData.h>
#include <Arc/ArcEffect.h>
#include <Arc/ArcGraphics.h>
#include <Arc/ArcNet.h>
#include <Arc/ArcUI.h>
#include <Arc/ArcGame.h>
#include <Arc/ArcScript.h>

using namespace std;
using namespace Arc;

int testsPassed = 0;
int testsTotal = 0;

void testStringFuncs( void )
{
	string result;



	string testToLower = "aBcDeFg";

	testsTotal++;
	result = Arc_StringGetLower(testToLower);

	if (result == "abcdefg")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringGetLower' Test" << endl;



	testsTotal++;
	Arc_StringToLower(testToLower);

	if (testToLower == "abcdefg")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringToLower' Test" << endl;



	string testToUpper = "aBcDeFg";

	testsTotal++;
	result = Arc_StringGetUpper(testToUpper);

	if (result == "ABCDEFG")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringGetUpper' Test" << endl;



	testsTotal++;
	Arc_StringToUpper(testToUpper);

	if (testToUpper == "ABCDEFG")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringToUpper' Test" << endl;



	string testUCWords = "hello world";

	testsTotal++;
	result = Arc_StringGetUCWords(testUCWords);

	if (result == "Hello World")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringGetUCWords' Test" << endl;



	testsTotal++;
	Arc_StringUCWords(testUCWords);

	if (testUCWords == "Hello World")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringUCWords' Test" << endl;



	string testUCFirst = "hello world";

	testsTotal++;
	result = Arc_StringGetUCFirst(testUCFirst);

	if (result == "Hello world")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringGetUCFirst' Test" << endl;



	testsTotal++;
	Arc_StringUCFirst(testUCFirst);

	if (testUCFirst == "Hello world")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringUCFirst' Test" << endl;



	string testSplit = "a,b,c";

	testsTotal++;
	ArrayList<string> splitResult = Arc_StringSplit(testSplit, ',');

	if (splitResult[0] == "a" && splitResult[1] == "b" && splitResult[2] == "c")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringSplit' Test" << endl;



	ArrayList<string> testJoin;
	testJoin.add("a");
	testJoin.add("b");
	testJoin.add("c");

	testsTotal++;
	result = Arc_StringJoin(",", testJoin);

	if (result == "a,b,c")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringJoin' Test" << endl;


	string testSubstr = "Hello, World!";

	testsTotal++;
	result = Arc_Substring(testSubstr, 2, 6);

	if (result == "llo, W")
		testsPassed++;
	else
		cerr << "Failed 'Arc_Substring' Test 1" << endl;



	testsTotal++;
	result = Arc_Substring(testSubstr, 2);

	if (result == "llo, World!")
		testsPassed++;
	else
		cerr << "Failed 'Arc_Substring' Test 2" << endl;



	string testReplaceAll = "abc 123 a bc, abcabc";

	testsTotal++;
	Arc_StringReplaceAll(testReplaceAll, "abc", "qwerty");

	if (testReplaceAll == "qwerty 123 a bc, qwertyqwerty")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringReplaceAll' Test" << endl;




	string testReplaceNext = "abc 123 a bc, abcabc";

	testsTotal++;
	Arc_StringReplaceNext(testReplaceNext, "abc", "qwerty");
	Arc_StringReplaceNext(testReplaceNext, "abc", "qwerty");

	if (testReplaceNext == "qwerty 123 a bc, qwertyabc")
		testsPassed++;
	else
		cerr << "Failed 'Arc_StringReplaceNext' Test" << endl;

}

void testRandomFuncs( void )
{
	const int SAMPLE_SIZE = 200;

	int intMin = -10, intMax = 10;
	float fltMin = -10.0f, fltMax = 10.0f;
	double dblMin = -10.0, dblMax = 10.0;
	bool passed = true;

	testsTotal++;
	for (int i = 0; i < SAMPLE_SIZE; ++i)
	{
		int rand = Arc_RandInt(intMin, intMax);
		if (rand < intMin || rand > intMax)
			passed = false;
	}

	if (passed)
		testsPassed++;
	else
		cerr << "Failed 'Arc_RandInt' Test" << endl;

	passed = true;

	testsTotal++;
	for (int i = 0; i < SAMPLE_SIZE; ++i)
	{
		float rand = Arc_RandFloat(fltMin, fltMax);
		if (rand < fltMin || rand > fltMax)
			passed = false;
	}

	if (passed)
		testsPassed++;
	else
		cerr << "Failed 'Arc_RandFloat' Test" << endl;

	passed = true;

	testsTotal++;
	for (int i = 0; i < SAMPLE_SIZE; ++i)
	{
		double rand = Arc_RandDouble(dblMin, dblMax);
		if (rand < dblMin || rand > dblMax)
			passed = false;
	}

	if (passed)
		testsPassed++;
	else
		cerr << "Failed 'Arc_RandDouble' Test" << endl;

	passed = true;
}

int main( int argc, char* argv[] )
{
	
	cout << "Using Arc Version: " << Arc_GetVersionString() << endl;
	cout << "Using Arc Audio Version: " << ArcAudio_GetVersionString() << endl;
	cout << "Using Arc Data Version: " << ArcData_GetVersionString() << endl;
	cout << "Using Arc Effect Version: " << ArcEffect_GetVersionString() << endl;
	cout << "Using Arc Graphics Version: " << ArcGraphics_GetVersionString() << endl;
	cout << "Using Arc Net Version: " << ArcNet_GetVersionString() << endl;
	cout << "Using Arc UI Version: " << ArcUI_GetVersionString() << endl;
	cout << "Using Arc Game Version: " << ArcGame_GetVersionString() << endl;
	cout << "Using Arc Scripting Version: " << ArcScript_GetVersionString() << endl << endl;
	
	Arc_InitCore();

	cout << "== Running Unit Tests ==" << endl << endl;

	testRandomFuncs();
	testStringFuncs();

	cout << endl << "Passed " << testsPassed << "/" << testsTotal << " Tests" << endl << endl;

	if (Arc_GetMemoryAllocationCount() > 0)
		Arc_PrintMemoryAllocations();

	system("PAUSE");

	return 0;
}