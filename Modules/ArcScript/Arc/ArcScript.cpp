#include "ArcScript.h"

#include <Arc/ConsoleFunctions.h>
#include <Arc/Log.h>

lua_State* Arc::gp_LuaState = nullptr;

bool Arc::Arc_InitScript( void )
{
	// Create the lua state 
	gp_LuaState = luaL_newstate();

	// Initialize lua's libraries
	luaL_openlibs(gp_LuaState);

	lua_register(gp_LuaState, "arc_pause", Arc_lua_pause);
	lua_register(gp_LuaState, "arc_info", Arc_lua_log_info);
	lua_register(gp_LuaState, "arc_error", Arc_lua_log_error);

	// TODO: Add error checking
	return true;
}

void Arc::Arc_TermScript( void )
{
	lua_close(gp_LuaState);
}

int Arc::Arc_lua_pause( lua_State* pState )
{
	int argc = lua_gettop(pState);

	Arc_Pause();

	return 0;
}

int Arc::Arc_lua_log_info( lua_State* pState )
{
	int argc = lua_gettop(pState);

	Log::Info("Lua", lua_tostring(pState, 1));

	return 0;
}

int Arc::Arc_lua_log_error( lua_State* pState )
{
	int argc = lua_gettop(pState);

	Log::Error("Lua", lua_tostring(pState, 1));

	return 0;
}

void Arc::Arc_RunScript( const string& filename )
{
	int status = luaL_loadfile(gp_LuaState, filename.c_str());

	if (status == 0)
	{
		status = lua_pcall(gp_LuaState, 0, LUA_MULTRET, 0);
	}
	else
	{
		Log::ErrorFmt("Script", "%s", lua_tostring(gp_LuaState, -1));
		lua_pop(gp_LuaState, 1); // remove error message
	}
}
