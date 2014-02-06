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

#include "StandardTypesTests.h"
#include "StringFunctionsTests.h"
#include "RandomFunctionsTests.h"
#include "OBJDocumentTests.h"
#include "PLYDocumentTests.h"

using namespace std;
using namespace Arc;

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

	TestGroup unitTests;

	TestGroup_Arc_StandardTypes(unitTests);
	TestGroup_Arc_StringFunctions(unitTests);
	TestGroup_Arc_RandomFunctions(unitTests);
	TestGroup_Arc_OBJDocument(unitTests);
	TestGroup_Arc_PLYDocument(unitTests);

	unitTests.runTests(true);

	cout << endl << "Passed " << unitTests.getNumPassed() << "/" << unitTests.getNumTests() << " Tests" << endl << endl;

	if (Arc_GetMemoryAllocationCount() > 0)
		Arc_PrintMemoryAllocations();

	system("PAUSE");

	return 0;
}