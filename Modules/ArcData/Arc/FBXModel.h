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

#ifndef ARC_DATA_FBX_MODEL_H
#define ARC_DATA_FBX_MODEL_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include "FBXProperty.h"

namespace Arc
{

class FBXModel
	: public ManagedObject
{
public:

	static FBXModel INVALID;

	inline FBXModel( void )
		: m_ID(),
		  m_Name(),
		  m_Properties(),
		  m_Vertices()
	{ }

	inline FBXModel( const string& id )
		: m_ID(id),
		  m_Name(),
		  m_Properties(),
		  m_Vertices()
	{ }

	virtual inline string getClassName( void ) const { return "Arc FBX Model"; }

	inline string getID( void ) const { return m_ID; }

	inline void setID( string val ) { m_ID = val; }

	inline string getName( void ) const { return m_Name; }

	inline void setName( string val ) { m_Name = val; }

	inline Map<string, FBXProperty> getProperties( void ) { return m_Properties; }

	inline bool hasProperty( const string& name ) { return m_Properties.containsKey(name); }

	inline FBXProperty& getProperty( const string& name ) { return (hasProperty(name) ? m_Properties[name] : FBXProperty::INVALID); }

	inline void addVertex( Vector3 vertex ) { m_Vertices.add(vertex); }

	inline unsigned int getNumVertices( void ) const { return m_Vertices.getSize(); }

	inline Vector3 getVertex( const int& index ) const { return (m_Vertices.hasIndex(index) ? m_Vertices[index] : Vector3::NEGATIVE_ONE); }

private:

	string m_ID;

	string m_Name;

	Map<string, FBXProperty> m_Properties;

	ArrayList<Vector3> m_Vertices;

}; // class FBXModel

} // namespace Arc

#endif // ARC_DATA_FBX_MODEL_H