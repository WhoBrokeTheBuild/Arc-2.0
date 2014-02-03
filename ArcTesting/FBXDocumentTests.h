#include <Arc/FBXDocument.h>
#include <Arc/TestGroup.h>

using namespace Arc;

TestResult Arc_FBXDocument_ASCII_Header( void )
{
	const string header =
		"; This is a test comment\n"
		"FBXHeaderExtension:  {\n"
		"    FBXHeaderVersion: 1003\n"
		"    FBXVersion: 6100\n"
		"    CreationTimeStamp:  {\n"
		"        Version: 1000\n"
		"        Year: 2014\n"
		"        Month: 01\n"
		"        Day: 23\n"
		"        Hour: 12\n"
		"        Minute: 34\n"
		"        Second: 56\n"
		"        Millisecond: 1234\n"
		"    }\n"
		"    Creator: \"Test Creator Ext\"\n"
		"    OtherFlags:  {\n"
		"        FlagTestOff: 0\n"
		"        FlagTestOn: 1\n"
		"    }\n"
		"}\n"
		"CreationTime: \"2014-01-23 12:34:56:000\"\n"
		"Creator: \"Test Creator\"\n";

	const int HEADER_VERSION = 1003;
	const int VERSION = 6100;

	const int TIME_STAMP_VERSION = 1000;
	const int TIME_STAMP_YEAR = 2014;
	const int TIME_STAMP_MONTH = 01;
	const int TIME_STAMP_DAY = 23;
	const int TIME_STAMP_HOUR = 12;
	const int TIME_STAMP_MINUTE = 34;
	const int TIME_STAMP_SECOND = 56;
	const int TIME_STAMP_MILLISECOND = 1234;

	const string CREATOR_EXT = "Test Creator Ext";
	const string CREATOR = "Test Creator";
	const string CREATION_TIME = "2014-01-23 12:34:56:000";

	Map<string, bool> flags;
	flags.add("FlagTestOff", false);
	flags.add("FlagTestOn", true);

	FBXDocument doc = FBXDocument::LoadString(header, FBXDocument::FBX_TYPE_ASCII);

	if (doc.getHeader().getVersion() != VERSION)
		return TestGroup::Failure("Invalid version");

	if (doc.getHeader().getHeaderVersion() != HEADER_VERSION)
		return TestGroup::Failure("Invalid header version");

	if (doc.getHeader().getCreator() != CREATOR_EXT)
		return TestGroup::Failure("Invalid creator extension");

	if (doc.getCreator() != CREATOR)
		return TestGroup::Failure("Invalid creator");

	if (doc.getCreationTime() != CREATION_TIME)
		return TestGroup::Failure("Invalid creation time");

	if (doc.getHeader().getTimeStamp().getVersion() != TIME_STAMP_VERSION)
		return TestGroup::Failure("Invalid time stamp version");

	if (doc.getHeader().getTimeStamp().getYear() != TIME_STAMP_YEAR)
		return TestGroup::Failure("Invalid time stamp year");

	if (doc.getHeader().getTimeStamp().getMonth() != TIME_STAMP_MONTH)
		return TestGroup::Failure("Invalid time stamp month");

	if (doc.getHeader().getTimeStamp().getDay() != TIME_STAMP_DAY)
		return TestGroup::Failure("Invalid time stamp day");

	if (doc.getHeader().getTimeStamp().getHours() != TIME_STAMP_HOUR)
		return TestGroup::Failure("Invalid time stamp hours");

	if (doc.getHeader().getTimeStamp().getMinutes() != TIME_STAMP_MINUTE)
		return TestGroup::Failure("Invalid time stamp minutes");

	if (doc.getHeader().getTimeStamp().getSeconds() != TIME_STAMP_SECOND)
		return TestGroup::Failure("Invalid time stamp seconds");

	if (doc.getHeader().getTimeStamp().getMilliseconds() != TIME_STAMP_MILLISECOND)
		return TestGroup::Failure("Invalid time stamp milliseconds");

	bool hasFlags = true;

	for (auto it = flags.itConstBegin(); it != flags.itConstEnd(); ++it)
	{
		if ( ! doc.getHeader().hasFlag(it->first) || doc.getHeader().getFlag(it->first) != it->second)
		{
			hasFlags = false;
			break;
		}
	}

	if ( ! hasFlags)
		return TestGroup::Failure("Invalid header flags");

	return TestGroup::Success();
}

TestResult Arc_FBXDocument_ASCII_SimpleCube( void )
{
	const string cube =
		"; This is a test comment\n"
		"Objects:  {\n"
		"    Model:  \"Model::Cube\", \"Cube\" {\n"
		"        Vertices: 1.000000,1.000000,-1.000000,1.000000,-1.000000,-1.000000,-1.000000,-1.000000,-1.000000,-1.000000,1.000000,-1.000000,\n"
		"                  1.000000,1.000000,1.000000,1.000000,-1.000000,1.000000,-1.000000,-1.000000,1.000000,-1.000000,1.000000,1.000000\n"
		"        PolygonVertexIndex: 0,1,2,-4,4,7,6,-6,0,4,5,-2,1,5,6,-3,2,6,7,-4,4,0,3,-8\n"
		"    }\n"
		"}\n";

	const unsigned int NUM_VERTICES = 8;
	const unsigned int NUM_FACES = 6;

	const Vector3 vertices[NUM_VERTICES] = {
		Vector3( 1.0f, 1.0f,-1.0f),
		Vector3( 1.0f,-1.0f,-1.0f),
		Vector3(-1.0f,-1.0f,-1.0f),
		Vector3(-1.0f, 1.0f,-1.0f),
		Vector3( 1.0f, 1.0f, 1.0f),
		Vector3( 1.0f,-1.0f, 1.0f),
		Vector3(-1.0f,-1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
	};

	const int faces[NUM_FACES][4] = {
		{ 0, 1, 2, 3 },
		{ 4, 7, 6, 5 },
		{ 0, 4, 5, 1 },
		{ 1, 5, 6, 2 },
		{ 2, 6, 7, 3 },
		{ 4, 0, 3, 7 },
	};

	FBXDocument doc = FBXDocument::LoadString(cube, FBXDocument::FBX_TYPE_ASCII);

	if ( ! doc.getObjects().hasModel("Cube"))
		return TestGroup::Failure("Object not loaded");

	FBXModel& model = doc.getObjects().getModel("Cube");

	if (model.getNumVertices() != NUM_VERTICES)
		return TestGroup::Failure("Invalid number of vertices");

	bool correctVerts = true;
	bool correctFaces = true;

	for (unsigned int i = 0; i < NUM_VERTICES; ++i)
	{
		if (vertices[i] != model.getVertex(i))
		{
			correctVerts = false;
			break;
		}
	}

	if ( ! correctVerts)
		return TestGroup::Failure("Invalid vertex data");

	for (unsigned int i = 0; i < NUM_FACES; ++i)
	{
		if (model.getFaceNumVertices(i) != 4)
		{
			correctFaces = false;
			break;
		}

		for (unsigned int j = 0; j < 4; ++j)
		{
			if (model.getFaceVertex(i, j) != vertices[faces[i][j]])
			{
				correctFaces = false;
				break;
			}
		}
	}

	if ( ! correctFaces)
		return TestGroup::Failure("Invalid face data");

	return TestGroup::Success();
}

void TestGroup_Arc_FBXDocument( TestGroup& test )
{
	test.addTest("Arc_FBXDocument_ASCII_Header", Arc_FBXDocument_ASCII_Header);
	test.addTest("Arc_FBXDocument_ASCII_SimpleCube", Arc_FBXDocument_ASCII_SimpleCube);
}