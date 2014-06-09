/* This file is part of ArcInterop.
 * 
 * ArcInterop is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcInterop is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcInterop; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_INTEROP_SCRIPT_NET_H
#define ARC_INTEROP_SCRIPT_NET_H

#include <Arc/ArcScript.h>

namespace Arc
{

bool Arc_InteropInit_ScriptNet( void );

int Arc_lua_ipaddress_create( lua_State* pState);
int Arc_lua_ipaddress_destroy( lua_State* pState); 

int Arc_lua_ipaddress_getA( lua_State* pState);
int Arc_lua_ipaddress_getB( lua_State* pState);
int Arc_lua_ipaddress_getC( lua_State* pState);
int Arc_lua_ipaddress_getD( lua_State* pState);

int Arc_lua_ipaddress_setA( lua_State* pState);
int Arc_lua_ipaddress_setB( lua_State* pState);
int Arc_lua_ipaddress_setC( lua_State* pState);
int Arc_lua_ipaddress_setD( lua_State* pState);

int Arc_lua_hostnameLookup( lua_State* pState);

int Arc_lua_socket_create( lua_State* pState );
int Arc_lua_socket_destroy( lua_State* pState );

int Arc_lua_socket_connect( lua_State* pState );
int Arc_lua_socket_disconnect( lua_State* pState );

int Arc_lua_socket_isOpen( lua_State* pState );
int Arc_lua_socket_isClosed( lua_State* pState );
int Arc_lua_socket_hasError( lua_State* pState );
int Arc_lua_socket_hasData( lua_State* pState );

int Arc_lua_socket_getState( lua_State* pState );
int Arc_lua_socket_getAddress( lua_State* pState );

int Arc_lua_socket_sendString( lua_State* pState );
int Arc_lua_socket_sendBuffer( lua_State* pState );

int Arc_lua_socket_sendBool  ( lua_State* pState );
int Arc_lua_socket_sendChar	 ( lua_State* pState );
int Arc_lua_socket_sendShort ( lua_State* pState );
int Arc_lua_socket_sendInt	 ( lua_State* pState );
int Arc_lua_socket_sendLong	 ( lua_State* pState );
int Arc_lua_socket_sendFloat ( lua_State* pState );
int Arc_lua_socket_sendDouble( lua_State* pState );
int Arc_lua_socket_sendInt8	 ( lua_State* pState );
int Arc_lua_socket_sendUInt8 ( lua_State* pState );
int Arc_lua_socket_sendInt16 ( lua_State* pState );
int Arc_lua_socket_sendUInt16( lua_State* pState );
int Arc_lua_socket_sendInt32 ( lua_State* pState );
int Arc_lua_socket_sendUInt32( lua_State* pState );

int Arc_lua_socket_recvLine( lua_State* pState );

}

#endif // ARC_SCRIPT_ARC_NET_FUNC_H
