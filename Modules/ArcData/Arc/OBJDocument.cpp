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
	// TODO(sdl.slane@gmail.com): Implement
	return OBJDocument();
}
