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

#ifndef ARC_NET_IP_ADDRESS_H
#define ARC_NET_IP_ADDRESS_H

#include <Arc/ManagedObject.h>

namespace Arc
{

struct IPAddress
	: public ManagedObject
{
public:

	// Constant value of 0.0.0.0
	const static IPAddress ZERO;

	inline IPAddress( void )
	{
		m_Quads[0] = m_Quads[1] = m_Quads[2] = m_Quads[3] = 0;
	}

	IPAddress( const string& addr );

	inline IPAddress( const Arc_uint8_t& a, const Arc_uint8_t& b, const Arc_uint8_t& c, const Arc_uint8_t& d )
	{
		m_Quads[0] = a;
		m_Quads[1] = b;
		m_Quads[2] = c;
		m_Quads[3] = d;
	}

	virtual inline ~IPAddress( void ) { }

	virtual inline string getClassName( void ) const { return "IP Address"; }

	inline bool operator==( const IPAddress& rhs ) const
	{
		return ( m_Quads[0] == rhs.m_Quads[0] &&
			     m_Quads[1] == rhs.m_Quads[1] &&
				 m_Quads[2] == rhs.m_Quads[2] &&
				 m_Quads[3] == rhs.m_Quads[3] );
	}

	inline bool operator!=( const IPAddress& rhs ) const
	{
		return !(*this == rhs);
	}

protected:

	Arc_uint8_t m_Quads[4];

	inline Arc_uint8_t* getRawData( void ) { return m_Quads; }

}; // class IPAddress

}; // namespace Arc

#endif // ARC_NET_IP_ADDRESS_H