#include "ArcInterop_ScriptNet.h"

#include <Arc/ArcNet.h>
#include <Arc/Socket.h>
#include <Arc/Log.h>

bool Arc::Arc_InteropInit_ScriptNet( void )
{
	if ( ! gp_LuaState)
		return false;

	lua_register(gp_LuaState, "arc_ipaddress_create",  Arc_lua_ipaddress_create);
	lua_register(gp_LuaState, "arc_ipaddress_destroy", Arc_lua_ipaddress_destroy);

	lua_register(gp_LuaState, "arc_ipaddress_getA",   Arc_lua_ipaddress_getA);
	lua_register(gp_LuaState, "arc_ipaddress_getB",   Arc_lua_ipaddress_getB);
	lua_register(gp_LuaState, "arc_ipaddress_getC",   Arc_lua_ipaddress_getC);
	lua_register(gp_LuaState, "arc_ipaddress_getD",   Arc_lua_ipaddress_getD);

	lua_register(gp_LuaState, "arc_ipaddress_setA",   Arc_lua_ipaddress_setA);
	lua_register(gp_LuaState, "arc_ipaddress_setB",   Arc_lua_ipaddress_setB);
	lua_register(gp_LuaState, "arc_ipaddress_setC",   Arc_lua_ipaddress_setC);
	lua_register(gp_LuaState, "arc_ipaddress_setD",   Arc_lua_ipaddress_setD);

	lua_register(gp_LuaState, "arc_hostnameLookup",   Arc_lua_hostnameLookup);

	Arc_RunScript("Arc_IPAddress.lua");

	lua_register(gp_LuaState, "arc_socket_create",  Arc_lua_socket_create);
	lua_register(gp_LuaState, "arc_socket_destroy", Arc_lua_socket_destroy);

	lua_register(gp_LuaState, "arc_socket_connect",    Arc_lua_socket_connect);
	lua_register(gp_LuaState, "arc_socket_disconnect", Arc_lua_socket_disconnect);

	lua_register(gp_LuaState, "arc_socket_isOpen",   Arc_lua_socket_isOpen);
	lua_register(gp_LuaState, "arc_socket_isClosed", Arc_lua_socket_isClosed);
	lua_register(gp_LuaState, "arc_socket_hasError", Arc_lua_socket_hasError);
	lua_register(gp_LuaState, "arc_socket_hasData",  Arc_lua_socket_hasData);

	lua_register(gp_LuaState, "arc_socket_getState",   Arc_lua_socket_getState);
	lua_register(gp_LuaState, "arc_socket_getAddress", Arc_lua_socket_getAddress);

	lua_register(gp_LuaState, "arc_socket_sendString", Arc_lua_socket_sendString);
	lua_register(gp_LuaState, "arc_socket_sendBuffer", Arc_lua_socket_sendBuffer);

	lua_register(gp_LuaState, "arc_socket_sendBool",   Arc_lua_socket_sendBool);
	lua_register(gp_LuaState, "arc_socket_sendChar",   Arc_lua_socket_sendChar);
	lua_register(gp_LuaState, "arc_socket_sendShort",  Arc_lua_socket_sendShort);
	lua_register(gp_LuaState, "arc_socket_sendInt",    Arc_lua_socket_sendInt);
	lua_register(gp_LuaState, "arc_socket_sendLong",   Arc_lua_socket_sendLong);
	lua_register(gp_LuaState, "arc_socket_sendFloat",  Arc_lua_socket_sendFloat);
	lua_register(gp_LuaState, "arc_socket_sendDouble", Arc_lua_socket_sendDouble);

	lua_register(gp_LuaState, "arc_socket_sendInt8",   Arc_lua_socket_sendInt8);
	lua_register(gp_LuaState, "arc_socket_sendUInt8",  Arc_lua_socket_sendUInt8);
	lua_register(gp_LuaState, "arc_socket_sendInt16",  Arc_lua_socket_sendInt16);
	lua_register(gp_LuaState, "arc_socket_sendUInt16", Arc_lua_socket_sendUInt16);
	lua_register(gp_LuaState, "arc_socket_sendInt32",  Arc_lua_socket_sendInt32);
	lua_register(gp_LuaState, "arc_socket_sendUInt32", Arc_lua_socket_sendUInt32);

	lua_register(gp_LuaState, "arc_socket_recvLine",   Arc_lua_socket_recvLine);

	Arc_RunScript("Arc_Socket.lua");

	return true;
}

int Arc::Arc_lua_ipaddress_create( lua_State* pState)
{
	int a = -1;
	if (lua_isnumber(gp_LuaState, 1))
		a = lua_tointeger(gp_LuaState, 1);

	int b = -1;
	if (lua_isnumber(gp_LuaState, 2))
		b = lua_tointeger(gp_LuaState, 2);

	int c = -1;
	if (lua_isnumber(gp_LuaState, 3))
		c = lua_tointeger(gp_LuaState, 3);

	int d = -1;
	if (lua_isnumber(gp_LuaState, 4))
		d = lua_tointeger(gp_LuaState, 4);

	IPAddress* pAddr = nullptr;

	if (a == -1 || b == -1 || c == -1 || d == -1)
	{
		pAddr = New IPAddress();
	}
	else
	{
		pAddr = New IPAddress(a, b, c, d);
	}

	lua_pushinteger(gp_LuaState, (int)pAddr);

	return 1;
}

int Arc::Arc_lua_ipaddress_destroy( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	delete pAddr;

	return 0;
}

int Arc::Arc_lua_ipaddress_getA( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const unsigned char& a = pAddr->getA();
		lua_pushinteger(gp_LuaState, a);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_getB( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const unsigned char& b = pAddr->getB();
		lua_pushinteger(gp_LuaState, b);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_getC( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const unsigned char& c = pAddr->getC();
		lua_pushinteger(gp_LuaState, c);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_getD( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const unsigned char& d = pAddr->getD();
		lua_pushinteger(gp_LuaState, d);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_setA( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const int& a = lua_tointeger(gp_LuaState, 2);
		pAddr->setA(a);
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_setB( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const int& b = lua_tointeger(gp_LuaState, 2);
		pAddr->setB(b);
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_setC( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const int& c = lua_tointeger(gp_LuaState, 2);
		pAddr->setC(c);
	}

	return 0;
}

int Arc::Arc_lua_ipaddress_setD( lua_State* pState)
{
	IPAddress* pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 1);

	if (pAddr)
	{
		const int& d = lua_tointeger(gp_LuaState, 2);
		pAddr->setD(d);
	}

	return 0;
}

int Arc::Arc_lua_hostnameLookup( lua_State* pState)
{
	string hostname = "";
	if (lua_isstring(gp_LuaState, 1))
		hostname = lua_tostring(gp_LuaState, 1);

	const IPAddress& addr = Arc_HostnameLookup(hostname);

	IPAddress* pAddr = New IPAddress(addr);
	lua_pushinteger(gp_LuaState, (int)pAddr);

	return 1;
}

int Arc::Arc_lua_socket_create( lua_State* pState )
{
	Socket* pSock = New Socket();
	//Log::InfoFmt("ArcNet_Func", "Created socket, 0x%x", pSock);

	lua_pushinteger(gp_LuaState, (int)pSock);

	return 1;
}

int Arc::Arc_lua_socket_destroy( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);
	//Log::InfoFmt("ArcNet_Func", "Destroying socket, 0x%x", pSock);

	delete pSock;

	return 0;
}

int Arc::Arc_lua_socket_connect( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	string hostname = "";
	IPAddress* pAddr = nullptr;
	if (lua_isnumber(gp_LuaState, 2))
		pAddr = (IPAddress*)lua_tointeger(gp_LuaState, 2);
	else if (lua_isstring(gp_LuaState, 2))
		hostname = lua_tostring(gp_LuaState, 2);

	int port = -1;
	if (lua_isnumber(gp_LuaState, 3))
		port = lua_tointeger(gp_LuaState, 3);

	if (pSock)
	{
		if (hostname.length() != 0)
		{
			pSock->connectTo(hostname, port, SocketType::SOCKET_TYPE_TCP);
		}
		else if (pAddr != nullptr)
		{
			pSock->connectTo(*pAddr, port, SocketType::SOCKET_TYPE_TCP);
		}
		else
		{
			// Error?
		}
	}

	return 0;
}

int Arc::Arc_lua_socket_disconnect( lua_State* pState )
{
	//Log::Info("ArcNet_Func", "Disconnecting socket");

	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	if (pSock)
	{
		pSock->disconnect();
	}

	return 0;
}

int Arc::Arc_lua_socket_isOpen( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	if (pSock)
	{
		const bool& isOpen = pSock->isOpen();
		lua_pushboolean(gp_LuaState, isOpen);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_socket_isClosed( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	if (pSock)
	{
		const bool& isClosed = pSock->isClosed();
		lua_pushboolean(gp_LuaState, isClosed);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_socket_hasError( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	if (pSock)
	{
		const bool& hasError = pSock->hasError();
		lua_pushboolean(gp_LuaState, hasError);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_socket_hasData( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	if (pSock)
	{
		const bool& hasData = pSock->isOpen();
		lua_pushboolean(gp_LuaState, hasData);
		return 1;
	}

	return 0;
}

int Arc::Arc_lua_socket_getState( lua_State* pState)
{
	return 0;
}

int Arc::Arc_lua_socket_getAddress( lua_State* pState)
{
	return 0;
}

int Arc::Arc_lua_socket_sendString( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);
	string str = lua_tostring(gp_LuaState, 2);

	bool withNullTerm = true;
	if (lua_isboolean(gp_LuaState, 3))
		withNullTerm = (lua_toboolean(gp_LuaState, 3) == TRUE ? true : false);

	if (pSock)
	{
		pSock->sendString(str, withNullTerm);
	}

	return 0;
}

int Arc::Arc_lua_socket_sendBuffer( lua_State* pState)
{
	return 0;
}

int Arc::Arc_lua_socket_sendBool( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendChar( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendShort( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendInt( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendLong( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendFloat( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendDouble( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendInt8( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendUInt8( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendInt16( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendUInt16( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendInt32( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_sendUInt32( lua_State* pState )
{
	return 0;
}

int Arc::Arc_lua_socket_recvLine( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);

	if (pSock)
	{
		const string& line = pSock->recvLine();
		lua_pushstring(gp_LuaState, line.c_str());
		return 1;
	}

	return 0;
}

