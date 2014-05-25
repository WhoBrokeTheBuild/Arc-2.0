#include "ServerSocket.h"

#include <sstream>
#include "Socket.h"

bool Arc::ServerSocket::bindLocal( unsigned int port, SocketType type )
{
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	m_Type = type;
	m_Port = port;

	if (m_Socket == INVALID_SOCKET)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("socket() failed");
		disconnect();
		return false;
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
		return false;
	}

	res = bind(m_Socket, result->ai_addr, (int)result->ai_addrlen);

	if (res == SOCKET_ERROR)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("bind() failed");
		disconnect();
		freeaddrinfo(result);
		return false;
	}

	res = listen(m_Socket, SOMAXCONN);

	if (res == SOCKET_ERROR)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("listen() failed");
		disconnect();
		freeaddrinfo(result);
		return false;
	}

	freeaddrinfo(result);
	m_State = SOCKET_STATE_OPEN;
	return true;
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

Arc::Socket* Arc::ServerSocket::acceptClient( void )
{
#if defined(ARC_OS_WINDOWS)

	SOCKET client;

#elif defined(ARC_OS_LINUX)

	int client;

#endif

	client = accept(m_Socket, NULL, NULL);

	if (client == INVALID_SOCKET)
	{
		m_State = SOCKET_STATE_ERROR;
		//setError("accept() failed");
		disconnect();
		return nullptr;
	}

	Socket* pSocket = New Socket(client, m_Type);
	return pSocket;
}
