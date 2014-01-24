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

#ifndef ARC_DATA_CSV_FACE_H
#define ARC_DATA_CSV_FACE_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>

#include "CSVRow.h"

namespace Arc
{

class OBJDocument;

class OBJFace
	: public ManagedObject
{

	friend class OBJDocument;

public:

	virtual ~OBJFace( void );

	virtual inline string getClassName( void ) const { return "Arc OBJ Face"; }

	inline int getNumVertexes( void ) const { return m_VertexIndexes.getSize(); }

	inline int getNumNormals( void ) const { return m_VertexIndexes.getSize(); }

	Vector3 getVertex( const int& index ) const;
	
	Vector3 getNormal( const int& index ) const;

private:

	inline OBJFace( const OBJDocument* pDocument )
		: mp_Document(pDocument)
	{ }

	void addVertex( int vertexInd, int normalInd = -1 );

	const OBJDocument* mp_Document;

	ArrayList<int> m_VertexIndexes;

	ArrayList<int> m_NormalIndexes;

}; // class CSVDocument

}; // namespace Arc

#endif // ARC_DATA_CSV_FACE_H