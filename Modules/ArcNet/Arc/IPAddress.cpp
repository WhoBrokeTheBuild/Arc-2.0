#include "IPAddress.h"

#include <Arc/ArrayList.h>
#include <Arc/StringFunctions.h>
#include <Arc/ParseFunctions.h>

const Arc::IPAddress Arc::IPAddress::ZERO = Arc::IPAddress(0, 0, 0, 0);

Arc::IPAddress::IPAddress( const string& addr )
{
	m_Quads[0] = m_Quads[1] = m_Quads[2] = m_Quads[3] = 0;

	ArrayList<string> strQuads = Arc_StringSplit(addr, '.', 4);

	if (strQuads.getSize() < 4)
		return;

	for (unsigned int i = 0; i < 4; ++i)
		m_Quads[i] = (Arc_uint8_t)Arc_Clamp(Arc_ParseInt(strQuads[i]), 0, 255);
}
