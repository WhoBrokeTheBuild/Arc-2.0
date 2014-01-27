#include "OBJDocument.h"

Arc::OBJDocument Arc::OBJDocument::LoadFile( const string& filename )
{
    Buffer buff = Buffer::LoadFromFile(filename);
	return OBJDocument::LoadBuffer(buff);
}

Arc::OBJDocument Arc::OBJDocument::LoadString( const string& data )
{
    Buffer buff = Buffer(data);
	return OBJDocument::LoadBuffer(buff);
}

Arc::OBJDocument Arc::OBJDocument::LoadBuffer( Buffer& data )
{
	OBJDocument doc;
	string line;

	data.resetReadIndex();

	while ( ! data.endOfBuffer())
	{
		line = data.readNextLine();

		if (line.length() == 0 || line[0] == '#')
			continue;

		ArrayList<string> parts = Arc_StringSplit(line, ' ');

		if (parts.getSize() == 0)
			continue;

		if (parts[0] == "v")
		{
			float verts[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				verts[i - 1] = Arc_ParseFloat(parts[i]);
			}

			doc.addVertex(Vector3(verts[0], verts[1], verts[2]));
		}
		else if (parts[0] == "vt")
		{

		}
		else if (parts[0] == "vn")
		{
			float verts[3] = { 1.0f, 1.0f, 1.0f };

			for (unsigned int i = 1; i <= 3; ++i)
			{
				if (i >= parts.getSize())
					break;

				verts[i - 1] = Arc_ParseFloat(parts[i]);
			}

			doc.addNormal(Vector3(verts[0], verts[1], verts[2]));
		}
		else if (parts[0] == "f")
		{
			int vertInds[4] = { -1, -1, -1, -1 };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				if (Arc_StringContains(parts[i], "//"))
				{
					ArrayList<string> subParts = Arc_StringSplit(parts[i], '/');

					if (subParts.getSize() == 0)
						break;

					vertInds[i - 1] = Arc_ParseInt(subParts[0]);
				}
				else if (Arc_StringContains(parts[i], "/"))
				{
					ArrayList<string> subParts = Arc_StringSplit(parts[i], '/');

					if (subParts.getSize() == 0)
						break;

					vertInds[i - 1] = Arc_ParseInt(subParts[0]);
				}
				else
				{
					vertInds[i - 1] = Arc_ParseInt(parts[i]);
				}
			}

			OBJFace face = OBJFace(&doc);

			for (int i = 0; i < 4; ++i)
			{
				if (vertInds[i] == -1)
					break;

				face.addVertexIndex(vertInds[i] - 1);
			}

			doc.addFace(face);
		}
	}

	return doc;
}
