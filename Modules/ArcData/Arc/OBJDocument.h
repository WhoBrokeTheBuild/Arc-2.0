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

#ifndef ARC_DATA_OBJ_DOCUMENT_H
#define ARC_DATA_OBJ_DOCUMENT_H

#include <cstdlib>

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>
#include <Arc/ParseFunctions.h>

#include "OBJFace.h"

namespace Arc
{

class OBJDocument
	: public ManagedObject
{
public:

	static OBJDocument LoadFile( const string& filename );

	static OBJDocument LoadString( const string& data );

	static OBJDocument LoadBuffer( Buffer& data );

	OBJDocument( const OBJDocument& rhs )
		: m_Vertices(rhs.m_Vertices),
		  m_Normals(rhs.m_Normals),
		  m_Faces(rhs.m_Faces)
	{
		OBJFace* pFace;
		for (auto it = m_Faces.itBegin(); it != m_Faces.itEnd(); ++it)
		{
			pFace = &(*it);
			pFace->setDocument(this);
		}
	}

	virtual inline ~OBJDocument( void ) { }

	virtual inline string getClassName( void ) const { return "Arc OBJ Document"; }

	inline unsigned int getNumVertices( void ) const { return m_Vertices.getSize(); }

	inline unsigned int getNumNormals( void ) const { return m_Normals.getSize(); }

	inline unsigned int getNumFaces( void ) const { return m_Faces.getSize(); }

	inline Vector3 getVertex( const int& index ) const { return (m_Vertices.hasIndex(index) ? m_Vertices[index] : Vector3::NEGATIVE_ONE); }

	inline Vector3 getNormal( const int& index ) const { return (m_Normals.hasIndex(index) ? m_Normals[index] : Vector3::NEGATIVE_ONE); }

	inline const OBJFace& getFace( const int& index ) const { return (m_Faces.hasIndex(index) ? m_Faces[index] : OBJFace::INVALID); }

private:

	OBJDocument( void )
		: m_Vertices(),
		  m_Normals(),
		  m_Faces()
	{ }

	inline void addVertex( const Vector3& vertex ) { m_Vertices.add(vertex); }

	inline void addNormal( const Vector3& normal ) { m_Normals.add(normal); }

	inline void addFace( const OBJFace& face ) { m_Faces.add(face); }

	ArrayList<Vector3> m_Vertices;

	ArrayList<Vector3> m_Normals;

	ArrayList<OBJFace> m_Faces;

}; // class CSVDocument

}; // namespace Arc

#endif // ARC_DATA_OBJ_DOCUMENT_H