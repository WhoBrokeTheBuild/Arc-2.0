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

#ifndef ARC_DATA_FBX_DOCUMENT_H
#define ARC_DATA_FBX_DOCUMENT_H

#include <cstdlib>

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>
#include <Arc/ParseFunctions.h>

#include "FBXHeader.h"

namespace Arc
{

typedef string FBXType;

class FBXDocument
	: public ManagedObject
{
public:

	static FBXType FBX_TYPE_ASCII;

	static FBXType FBX_TYPE_BINARY;

	static FBXDocument LoadFile( const string& filename, const FBXType& type );

	static FBXDocument LoadString( const string& data, const FBXType& type );

	static FBXDocument LoadBuffer( Buffer& data, const FBXType& type );

	FBXDocument( const FBXDocument& rhs )
		: m_Header(rhs.m_Header),
		  m_CreationTime(rhs.m_CreationTime),
		  m_Creator(rhs.m_Creator)
	{ }

	virtual inline ~FBXDocument( void ) { }

	virtual inline string getClassName( void ) const { return "Arc FBX Document"; }

	inline FBXHeader& getHeader( void ) { return m_Header; }

private:

	FBXDocument( void )
	{ }

	FBXHeader m_Header;

	string m_CreationTime;

	string m_Creator;

}; // class CSVDocument

} // namespace Arc

#endif // ARC_DATA_FBX_DOCUMENT_H
