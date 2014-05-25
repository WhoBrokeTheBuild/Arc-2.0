#include "Socket.h"

bool Arc::Socket::connectTo( const IPAddress& addr, const unsigned int& port, const SocketType& type )
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

bool Arc::Socket::connectTo( const string& hostname, const unsigned int& port, const SocketType& type )
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

	m_State = SOCKET_STATE_CLOSED;
}

bool Arc::Socket::hasData( int timeoutMS /*= -1*/ )
{
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(m_Socket, &fds);

	int timeoutSec = timeoutMS / 1000;
	int timeoutUS = (timeoutMS % 1000) * 1000;

	timeval tv;
	tv.tv_sec = timeoutSec;
	tv.tv_usec = timeoutUS;

	int result = select(m_Socket + 1, &fds, 0, 0, &tv);

	if (result < 0)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("select() failed");
		disconnect();
		return false;
	}

	return (result == 1);
}

#if defined(ARC_OS_WINDOWS)

Arc::Socket::Socket( const SOCKET& socket, const SocketType& type ) 

#elif defined(ARC_OS_LINUX)

Arc::Socket::Socket( const int& socket, const SocketType& type ) 

#endif;
	: m_Socket(socket),
	  m_Address(),
	  m_Port(0),
	  m_Type(type),
	  m_State(SOCKET_STATE_OPEN)
{
	char buf[INET_ADDRSTRLEN] = "";
	struct sockaddr_in name;
	socklen_t len = sizeof(name);
	int res;

	res = getpeername(socket, (struct sockaddr *)&name, &len);

	if (res == 0)
	{
		inet_ntop(AF_INET, &name.sin_addr, buf, sizeof buf);
	}
	else
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("getpeername() failed");
		disconnect();
		return;
	}

	m_Address = IPAddress(inet_ntoa(name.sin_addr));
	m_Port = name.sin_port;
}

string Arc::Socket::recvString(void)
{
	string buf;
	char ch;

	do 
	{
		ch = recvChar();
		buf += ch;
	} 
	while (ch != 0);

	return buf;
}
