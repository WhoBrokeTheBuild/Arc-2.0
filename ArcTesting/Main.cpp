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

#include "ArcCore_StandardTypesTests.h"
#include "ArcCore_StringFunctionsTests.h"
#include "ArcCore_RandomFunctionsTests.h"

#include "ArcData_OBJDocumentTests.h"
#include "ArcData_PLYDocumentTests.h"

#include "ArcNet_IPAddressTests.h"

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

	TestGroup_ArcCore_StandardTypes(unitTests);
	TestGroup_ArcCore_StringFunctions(unitTests);
	TestGroup_ArcCore_RandomFunctions(unitTests);

	TestGroup_ArcData_OBJDocument(unitTests);
	TestGroup_ArcData_PLYDocument(unitTests);

	TestGroup_ArcNet_IPAddress(unitTests);

	unitTests.runTests(true);

	cout << endl << "Passed " << unitTests.getNumPassed() << "/" << unitTests.getNumTests() << " Tests" << endl << endl;

	if (Arc_GetMemoryAllocationCount() > 0)
		Arc_PrintMemoryAllocations();

	system("PAUSE");

	return 0;
}