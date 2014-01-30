#include <Arc/PLYDocument.h>
#include <Arc/TestGroup.h>

using namespace Arc;

TestResult Arc_PLYDocument_SimpleCube( void )
{
	const string cube =
		"ply\n"
		"format ascii 1.0\n"
		"comment This is a test comment\n"
		"element vertex 8\n"
		"property float x\n"
		"property float y\n"
		"property float z\n"
		"element face 6\n"
		"property list uchar uint vertex_indices\n"
		"end_header\n"
		"1.000000 -1.000000 -1.000000\n"
		"1.000000 -1.000000 1.000000\n"
		"-1.000000 -1.000000 1.000000\n"
		"-1.000000 -1.000000 -1.000000\n"
		"1.000000 1.000000 -1.000000\n"
		"1.000000 1.000000 1.000000\n"
		"-1.000000 1.000000 1.000000\n"
		"-1.000000 1.000001 -1.000000\n"
		"4 0 1 2 3\n"
		"4 4 7 6 5\n"
		"4 0 4 5 1\n"
		"4 1 5 6 2\n"
		"4 2 6 7 3\n"
		"4 4 0 3 7\n";
		
	const unsigned int NUM_VERTICES = 8;
	const unsigned int NUM_FACES = 6;

	const Vector3 vertices[NUM_VERTICES] = {
		Vector3( 1.0f, -1.0f, -1.0f),
		Vector3( 1.0f, -1.0f,  1.0f),
		Vector3(-1.0f, -1.0f,  1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3( 1.0f,  1.0f, -1.0f),
		Vector3( 1.0f,  1.0f,  1.0f),
		Vector3(-1.0f,  1.0f,  1.0f),
		Vector3(-1.0f,  1.0f, -1.0f),
	};

	const int faces[NUM_FACES][4] = {
		{ 0, 1, 2, 3 },
		{ 4, 7, 6, 5 },
		{ 0, 4, 5, 1 },
		{ 1, 5, 6, 2 },
		{ 2, 6, 7, 3 },
		{ 4, 0, 3, 7 },
	};

	PLYDocument doc = PLYDocument::LoadString(cube);

	ArrayList<PLYElement> cubeVerts = doc.getElementsOfType("vertex");
	ArrayList<PLYElement> cubeFaces = doc.getElementsOfType("face");

	if (cubeVerts.getSize() != NUM_VERTICES)
		return TestGroup::Failure("Invalid number of vertices");

	if (cubeFaces.getSize() != NUM_FACES)
		return TestGroup::Failure("Invalid number of faces");

	bool correctVerts = true;
	bool correctFaces = true;

	for (unsigned int i = 0; i < NUM_VERTICES; ++i)
	{
		if ( vertices[i].getX() != cubeVerts[i].getFloatData("x") && 
			 vertices[i].getY() != cubeVerts[i].getFloatData("y") && 
			 vertices[i].getZ() != cubeVerts[i].getFloatData("z") )
		{
			correctVerts = false;
			break;
		}
	}

	if ( ! correctVerts)
		return TestGroup::Failure("Invalid vertex data");

	for (unsigned int i = 0; i < NUM_FACES; ++i)
	{
		if (cubeFaces[i].getUIntDataListSize() != 4)
		{
			correctFaces = false;
			break;
		}

		for (unsigned int j = 0; j < 4; ++j)
		{
			if (cubeFaces[i].getUIntDataFromList(j) != faces[i][j])
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

void TestGroup_Arc_PLYDocument( TestGroup& test )
{
	test.addTest("Arc_PLYDocument_SimpleCube", Arc_PLYDocument_SimpleCube);
}