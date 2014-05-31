#include "IPAddress.h"

#include "Socket.h"

#include <Arc/ArrayList.h>
#include <Arc/StringFunctions.h>
#include <Arc/ParseFunctions.h>

#include <sstream>

const Arc::IPAddress Arc::IPAddress::ZERO = Arc::IPAddress(0, 0, 0, 0);
const Arc::IPAddress Arc::IPAddress::MAX = Arc::IPAddress(255, 255, 255, 255);

Arc::IPAddress::IPAddress( const string& addr )
{
	m_Quads[0] = m_Quads[1] = m_Quads[2] = m_Quads[3] = 0;

	ArrayList<string> strQuads = Arc_StringSplit(addr, '.', 4);

	if (strQuads.getSize() < 4)
		return;

	for (unsigned int i = 0; i < 4; ++i)
		m_Quads[i] = (Arc_uint8_t)Arc_Clamp(Arc_ParseInt(strQuads[i]), 0, 255);
}

string Arc::IPAddress::toString(void) const
{
	std::stringstream ss;
	ss << "IP Address ["
		<< (int)m_Quads[0] << "."
		<< (int)m_Quads[1] << "."
		<< (int)m_Quads[2] << "."
		<< (int)m_Quads[3] << "]";

	return ss.str();
}

Arc::IPAddress Arc::Arc_HostnameLookup( const string& hostname )
{
	hostent* host = gethostbyname(hostname.c_str());

	if ( ! host)
		return IPAddress::ZERO;

	return IPAddress(host->h_addr_list[0][0],
		             host->h_addr_list[0][1],
		             host->h_addr_list[0][2], 
		             host->h_addr_list[0][3]);
}
