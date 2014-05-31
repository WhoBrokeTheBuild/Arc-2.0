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
#include <Arc/Log.h>

#include <Arc/Socket.h>
#include <Arc/ServerSocket.h>

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
	Log::AddInfoOutput("stdout");
	Log::AddErrorOutput("stderr");

	Log::InfoFmt("Main", "Using Arc Version: %s", Arc_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Audio Version: %s", ArcAudio_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Data Version: %s", ArcData_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Effect Version: %s", ArcEffect_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Graphics Version: %s", ArcGraphics_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Net Version: %s", ArcNet_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc UI Version: %s", ArcUI_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Game Version: %s", ArcGame_GetVersionString().c_str());
	Log::InfoFmt("Main", "Using Arc Scripting Version: %s", ArcScript_GetVersionString().c_str());
	
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

	Log::CloseOutputs();

	return 0;
}