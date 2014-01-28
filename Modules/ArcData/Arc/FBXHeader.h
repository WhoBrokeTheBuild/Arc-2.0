/* This file is part of ArcData.
 * 
 * ArcData is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcData is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcData; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_DATA_FBX_OBJECT_H
#define ARC_DATA_FBX_OBJECT_H

#include <Arc/ManagedObject.h>

#include <Arc/Map.h>

#include "FBXTimeStamp.h"

namespace Arc
{

class FBXHeader
	: public ManagedObject
{
public:

	inline FBXHeader( void )
		: m_Version(),
		  m_HeaderVersion(),
		  m_TimeStamp(),
		  m_Creator(),
		  m_Flags()
	{ }

	inline FBXHeader( const FBXHeader& rhs )
		: m_Version(rhs.m_Version),
		  m_HeaderVersion(rhs.m_HeaderVersion),
		  m_TimeStamp(rhs.m_TimeStamp),
		  m_Creator(rhs.m_Creator),
		  m_Flags(rhs.m_Flags)
	{ }

	virtual inline string getClassName( void ) const { return "Arc FBX Header"; }

	inline unsigned int getVersion( void ) const { return m_Version; }

	inline void setVersion( unsigned int version ) { m_Version = version; }

	inline unsigned int getHeaderVersion( void ) const { return m_HeaderVersion; }

	inline void setHeaderVersion( unsigned int headerVersion ) { m_HeaderVersion = headerVersion; }

	inline FBXTimeStamp& getTimeStamp( void ) { return m_TimeStamp; }

	inline void setTimeStamp( const FBXTimeStamp& timeStamp ) { m_TimeStamp = timeStamp; }

	inline string getCreator( void ) const { return m_Creator; }

	inline void setCreator( const string& creator ) { m_Creator = creator; }

	inline bool hasFlag( const string& flag ) { return m_Flags.containsKey(flag); }

	inline bool getFlag( const string& flag ) { return (hasFlag(flag) ? m_Flags[flag] : false); }

	inline void setFlag( const string& flag, const bool& value ) { (hasFlag(flag) ? m_Flags[flag] = value : m_Flags.add(flag, value)); }

private:

	unsigned int m_Version;

	unsigned int m_HeaderVersion;

	FBXTimeStamp m_TimeStamp;
	
	string m_Creator;

	Map<string, bool> m_Flags;

}; // class FBXObject

} // namespace Arc

#endif // ARC_DATA_FBX_OBJECT_H