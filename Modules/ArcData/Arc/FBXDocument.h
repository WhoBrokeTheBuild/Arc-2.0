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
#include "FBXDefinitions.h"
#include "FBXObjects.h"

namespace Arc
{

typedef string FBXType;

class FBXDocument
	: public ManagedObject
{
public:

	static FBXDocument INVALID;

	static FBXType FBX_TYPE_ASCII;

	static FBXType FBX_TYPE_BINARY;

	FBXDocument( void )
		: m_Header(),
		  m_Definitions(),
		  m_Objects(),
		  m_CreationTime(),
		  m_Creator()
	{ }

	FBXDocument( const FBXDocument& rhs )
		: m_Header(rhs.m_Header),
		  m_Definitions(rhs.m_Definitions),
		  m_Objects(rhs.m_Objects),
		  m_CreationTime(rhs.m_CreationTime),
		  m_Creator(rhs.m_Creator)
	{ }

	virtual inline ~FBXDocument( void ) { }

	virtual inline string getClassName( void ) const { return "Arc FBX Document"; }

	void loadFile( const string& filename, const FBXType& type );
	
	void loadString( const string& data, const FBXType& type );
	
	void loadBuffer( Buffer& data, const FBXType& type );

	inline FBXHeader& getHeader( void ) { return m_Header; }

	inline FBXDefinitions& getDefinitions( void ) { return m_Definitions; }

	inline FBXObjects& getObjects( void ) { return m_Objects; }

	inline string getCreationTime( void ) const { return m_CreationTime; }

	inline void setCreationTime( string creationTime ) { m_CreationTime = creationTime; }

	inline string getCreator( void ) const { return m_Creator; }

	inline void setCreator( string creator ) { m_Creator = creator; }

private:

	static void StripQuotes( string& str );

	void loadBufferASCII( Buffer& data );

	void loadBufferBinary( Buffer& data );

	FBXHeader m_Header;

	FBXDefinitions m_Definitions;

	FBXObjects m_Objects;
	
	string m_CreationTime;

	string m_Creator;

}; // class CSVDocument

} // namespace Arc

#endif // ARC_DATA_FBX_DOCUMENT_H
