#include "ArcNet_Func.h"

#include <Arc/ArcNet.h>
#include <Arc/Socket.h>
#include <Arc/Log.h>

bool Arc::Arc_InitArcNetScript( void )
{
	if ( ! gp_LuaState)
		return false;

	lua_register(gp_LuaState, "arc_socket_create", Arc_lua_socket_create);
	lua_register(gp_LuaState, "arc_socket_destroy", Arc_lua_socket_destroy);
	lua_register(gp_LuaState, "arc_socket_connect", Arc_lua_socket_connect);
	lua_register(gp_LuaState, "arc_socket_disconnect", Arc_lua_socket_disconnect);

	lua_register(gp_LuaState, "arc_socket_sendString", Arc_lua_socket_sendString);
	lua_register(gp_LuaState, "arc_socket_recvLine", Arc_lua_socket_recvLine);

	lua_register(gp_LuaState, "arc_socket_isOpen", Arc_lua_socket_isOpen);

	return true;
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
	//Log::Info("ArcNet_Func", "Connecting socket");

	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);
	
	string hostname = "";
	if (lua_isstring(gp_LuaState, 2))
		hostname = lua_tostring(gp_LuaState, 2);

	int port = -1;
	if (lua_isnumber(gp_LuaState, 3))
		port = lua_tointeger(gp_LuaState, 3);

	if (pSock)
	{
		pSock->connectTo(hostname, port, SocketType::SOCKET_TYPE_TCP);
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

int Arc::Arc_lua_socket_sendString( lua_State* pState )
{
	Socket* pSock = (Socket*)lua_tointeger(gp_LuaState, 1);
	string str = lua_tostring(gp_LuaState, 2);

	bool withNullTerm = true;
	if (lua_isboolean(gp_LuaState, 3))
		withNullTerm = (bool)lua_toboolean(gp_LuaState, 3);

	if (pSock)
	{
		pSock->sendString(str, withNullTerm);
	}

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
