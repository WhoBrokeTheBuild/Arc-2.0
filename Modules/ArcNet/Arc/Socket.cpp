#include "Socket.h"

bool Arc::Socket::connectTo( IPAddress addr, unsigned int port, SocketType type )
{
	m_Address = addr;
	m_Port = port;
	m_Type = type;

	m_State = SOCKET_STATE_CLOSED;

	if (m_Type == SOCKET_TYPE_TCP)
	{
		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	else if (m_Type == SOCKET_TYPE_UDP)
	{
		m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(m_Port);

	Arc_uint8_t* rawAddr = m_Address.getRawData();

#if defined(ARC_OS_WINDOWS)

	saddr.sin_addr.S_un.S_un_b.s_b1 = rawAddr[0];
	saddr.sin_addr.S_un.S_un_b.s_b2 = rawAddr[1];
	saddr.sin_addr.S_un.S_un_b.s_b3 = rawAddr[2];
	saddr.sin_addr.S_un.S_un_b.s_b4 = rawAddr[3];

#elif defined(ARC_OS_LINUX)

	uint8_t* addr = (uint8_t*)saddr.sin_addr.s_addr;
	addr[0] = rawAddr[0];
	addr[1] = rawAddr[1];
	addr[2] = rawAddr[2];
	addr[3] = rawAddr[3];

#endif

	int result = connect(m_Socket, (sockaddr*)&saddr, sizeof saddr);
	if (result == SOCKET_ERROR)
	{
		//setError("connect() failed");
		m_State = SOCKET_STATE_ERROR;
		disconnect();
		return false;
	}

	m_State = SOCKET_STATE_OPEN;
	return true;
}

bool Arc::Socket::connectTo( const string& hostname, unsigned int port, SocketType type )
{
	return connectTo(Arc_HostnameLookup(hostname), port, type);
}

void Arc::Socket::disconnect( void )
{
#if defined(ARC_OS_WINDOWS)

	closesocket(m_Socket);

#elif defined(ARC_OS_LINUX)

	close(m_Socket);

#endif
}

int Arc::Socket::sendString( const string& data, const bool& withNullTerm /*= true */ )
{
	return 0;
}

int Arc::Socket::sendBuffer( const char* buffer, const int& length )
{
	return 0;
}

int Arc::Socket::sendBuffer( const Buffer& buffer )
{
	return 0;
}
