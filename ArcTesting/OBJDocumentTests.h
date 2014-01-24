#include <Arc/OBJDocument.h>
#include <Arc/TestGroup.h>

using namespace Arc;

TestResult Arc_OBJDocument_SimpleCube( void )
{
	const string cube =
		"# This is a test comment\n"
		"v 1.000000 -1.000000 -1.000000\n"
		"v 1.000000 -1.000000 1.000000\n"
		"v -1.000000 -1.000000 1.000000\n"
		"v -1.000000 -1.000000 -1.000000\n"
		"v 1.000000 1.000000 -1.000000\n"
		"v 1.000000 1.000000 1.000000\n"
		"v -1.000000 1.000000 1.000000\n"
		"v -1.000000 1.000000 -1.000000\n"
		"f 1 2 3 4\n"
		"f 5 8 7 6\n"
		"f 1 5 6 2\n"
		"f 2 6 7 3\n"
		"f 3 7 8 4\n"
		"f 5 1 4 8\n";

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
		{ 1, 2, 3, 4 },
		{ 5, 8, 7, 6 },
		{ 1, 5, 6, 2 },
		{ 2, 6, 7, 3 },
		{ 3, 7, 8, 4 },
		{ 5, 1, 4, 8 },
	};

	OBJDocument doc = OBJDocument::LoadString(cube);

	if (doc.getNumVertices() != NUM_VERTICES)
		return TestGroup::Failure("Invalid number of vertices");

	if (doc.getNumFaces() != NUM_FACES)
		return TestGroup::Failure("Invalid number of faces");

	bool correctVerts = true;
	bool correctFaces = true;

	for (unsigned int i = 0; i < NUM_VERTICES; ++i)
	{
		if (vertices[i] != doc.getVertex(i))
		{
			correctVerts = false;
			break;
		}
	}

	if ( ! correctVerts)
		return TestGroup::Failure("Invalid vertex data");

	for (unsigned int i = 0; i < NUM_FACES; ++i)
	{
		const OBJFace& face = doc.getFace(i);

		if (face.getNumVertices() != 4)
		{
			correctFaces = false;
			break;
		}

		for (unsigned int j = 0; j < 4; ++j)
		{
			if (face.getVertex(j) != doc.getVertex(faces[i][j] - 1))
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

void TestGroup_Arc_OBJDocument( TestGroup& test )
{
	test.addTest("Arc_OBJDocument_SimpleCube", Arc_OBJDocument_SimpleCube);
}