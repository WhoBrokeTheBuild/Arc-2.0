/* This file is part of ArcScript.
 * 
 * ArcScript is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcScript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcScript; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_SCRIPT_ARC_NET_FUNC_H
#define ARC_SCRIPT_ARC_NET_FUNC_H

#include "ArcScript.h"

namespace Arc
{

bool Arc_InitArcNetScript( void );

int Arc_lua_socket_create( lua_State* pState );
int Arc_lua_socket_destroy( lua_State* pState );

int Arc_lua_socket_connect( lua_State* pState );
int Arc_lua_socket_disconnect( lua_State* pState );

int Arc_lua_socket_sendString( lua_State* pState );
int Arc_lua_socket_recvLine( lua_State* pState );

int Arc_lua_socket_isOpen( lua_State* pState );

}

#endif // ARC_SCRIPT_ARC_NET_FUNC_H
