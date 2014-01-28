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

#ifndef ARC_DATA_FBX_DEFINITIONS_H
#define ARC_DATA_FBX_DEFINITIONS_H

#include <Arc/ManagedObject.h>

#include <Arc/Map.h>
#include <Arc/ArrayList.h>

namespace Arc
{

class FBXDefinitions
	: public ManagedObject
{
public:

	inline FBXDefinitions( void )
		: m_Version(),
		  m_TypeCounts()
	{ }

	inline FBXDefinitions( const FBXDefinitions& rhs )
		: m_Version(rhs.m_Version),
		  m_TypeCounts(rhs.m_TypeCounts)
	{ }

	virtual inline string getClassName( void ) const { return "Arc FBX Definitions"; }

	inline unsigned int getVersion( void ) const { return m_Version; }

	inline void setVersion( unsigned int val ) { m_Version = val; }

	unsigned int getTotalCount( void ) const;

	ArrayList<string> getAllTypes( void ) const { return m_TypeCounts.getKeys(); }

	bool hasType( const string& type ) const { return m_TypeCounts.containsKey(type); }

	Map<string, unsigned int> getAllTypeCounts( void ) { return m_TypeCounts; }

	unsigned int getTypeCount( const string& type ) { return (hasType(type) ? m_TypeCounts[type] : 0); }

	void setTypeCount( const string& type, const unsigned int& count ) { (hasType(type) ? m_TypeCounts[type] = count : m_TypeCounts.add(type, count)); }

private:

	unsigned int m_Version;
	
	Map<string, unsigned int> m_TypeCounts;
};

}; // namespace Arc

#endif // ARC_DATA_FBX_DEFINITIONS_H