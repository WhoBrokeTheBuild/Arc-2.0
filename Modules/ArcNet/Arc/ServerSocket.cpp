#include "ServerSocket.h"

#include <sstream>

bool Arc::ServerSocket::bindLocal( unsigned int port, SocketType type )
{
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_Socket == INVALID_SOCKET)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("socket() failed");
		disconnect();
		return;
	}

	struct addrinfo *result = nullptr;
	struct addrinfo hints;
	int res;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	std::stringstream strPort;
	strPort << port;

	res = getaddrinfo(NULL, strPort.str().c_str(), &hints, &result);

	if (res != 0)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("getaddrinfo() failed");
		disconnect();
		freeaddrinfo(result);
		return;
	}

	res = bind(m_Socket, result->ai_addr, (int)result->ai_addrlen);

	if (res == SOCKET_ERROR)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("bind() failed");
		disconnect();
		freeaddrinfo(result);
		return;
	}

	res = listen(m_Socket, SOMAXCONN);

	if (res == SOCKET_ERROR)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("listen() failed");
		disconnect();
		freeaddrinfo(result);
		return;
	}

	freeaddrinfo(result);
}

void Arc::ServerSocket::disconnect( void )
{
#if defined(ARC_OS_WINDOWS)

	closesocket(m_Socket);

#elif defined(ARC_OS_LINUX)

	close(m_Socket);

#endif

	m_State = SOCKET_STATE_CLOSED;
}
