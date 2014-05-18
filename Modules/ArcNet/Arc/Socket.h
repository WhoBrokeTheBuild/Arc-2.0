/* This file is part of ArcNet.
 * 
 * ArcNet is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcNet is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcNet; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_NET_SOCKET_H
#define ARC_NET_SOCKET_H

#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>

#include "SocketType.h"
#include "SocketState.h"
#include "IPAddress.h"

#if defined(ARC_OS_WINDOWS)

// Prevent conflict with namespace Arc and Arc()
#define NOGDI

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define ARC_INVALID_SOCKET INVALID_SOCKET

#elif defined(ARC_OS_LINUX)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ARC_INVALID_SOCKET -1

#endif

namespace Arc
{

class Socket
	: public ManagedObject
{
public:

	inline Socket( void )
		: m_Socket(ARC_INVALID_SOCKET),
		  m_Address(),
		  m_Port(0),
		  m_Type(INVALID_SOCKET_TYPE),
		  m_State(SOCKET_STATE_CLOSED)
	{

	}

	inline ~Socket( void ) { disconnect(); }

	virtual inline string getClassName( void ) const { return "Socket"; }

	bool connectTo( IPAddress addr, unsigned int port, SocketType type );
	bool connectTo( const string& hostname, unsigned int port, SocketType type );

	bool disconnect( void );

	inline bool isOpen( void ) const { return (m_State == SOCKET_STATE_OPEN); }
	inline bool isClosed( void ) const { return (m_State == SOCKET_STATE_CLOSED); }
	inline bool hasError( void ) const { return (m_State == SOCKET_STATE_ERROR); }

	inline SocketState getState( void ) const { return m_State; }

	int sendString( const string& data, const bool& withNullTerm = true );
	int sendBuffer( const char* buffer, const int& length );
	int sendBuffer( const Buffer& buffer );

	bool sendBool( const bool& data );
	bool sendChar( const char& data );
	bool sendShort( const short& data );
	bool sendInt( const int& data );
	bool sendLong( const long& data );
	bool sendFloat( const float& data );
	bool sendDouble( const double& data );

	bool sendInt8( const Arc_int8_t& data );
	bool sendUInt8( const Arc_uint8_t& data );
	bool sendInt16( const Arc_int16_t& data );
	bool sendUInt16( const Arc_uint16_t& data );
	bool sendInt32( const Arc_int32_t& data );
	bool sendUInt32( const Arc_uint32_t& data );

	int recvString( const string& data, const bool& withNullTerm = true );
	int recvBuffer( const char* buffer, const int& length );
	int recvBuffer( const Buffer& buffer );

	bool recvBool( const bool& data );
	bool recvChar( const char& data );
	bool recvShort( const short& data );
	bool recvInt( const int& data );
	bool recvLong( const long& data );
	bool recvFloat( const float& data );
	bool recvDouble( const double& data );

	bool recvInt8( const Arc_int8_t& data );
	bool recvUInt8( const Arc_uint8_t& data );
	bool recvInt16( const Arc_int16_t& data );
	bool recvUInt16( const Arc_uint16_t& data );
	bool recvInt32( const Arc_int32_t& data );
	bool recvUInt32( const Arc_uint32_t& data );

protected:
	
#if defined(ARC_OS_WINDOWS)

		// The windows system reference to the socket
        SOCKET m_Socket;

		/* 
		 * @returns: The windows system reference to the socket
		 */
        SOCKET getWinSocket( void ) const { return m_Socket; }

#elif defined(ARC_OS_LINUX)

		// The linux system reference to the socket
        int m_Socket;
		
		/* 
		 * @returns: The linux system reference to the socket
		 */
        int getUnixSocket( void ) const { return m_Socket; }

#endif

		// The address of the destination host
		IPAddress			m_Address;

		// The port to connect to on the destination host
		unsigned int		m_Port;

		// The type of socket (TCP, UDP)
		SocketType			m_Type;

		// The state of the socket (Open, Closed, Error)
		SocketState			m_State;

}; // class Socket

}; // namespace Arc

#endif // ARC_NET_SOCKET_H