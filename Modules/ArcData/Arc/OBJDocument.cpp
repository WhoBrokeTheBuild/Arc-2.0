#include "OBJDocument.h"

Arc::OBJDocument Arc::OBJDocument::LoadFile( const string& filename )
{
	return LoadBuffer(Buffer::LoadFromFile(filename));
}

Arc::OBJDocument Arc::OBJDocument::LoadString( const string& data )
{
	return LoadBuffer(Buffer(data));
}

Arc::OBJDocument Arc::OBJDocument::LoadBuffer( Buffer& data )
{
	OBJDocument doc;
	string line;

	while ( ! data.endOfBuffer())
	{
		line = data.readNextLine();

		std::cout << line << std::endl;
	}

	return doc;
}
