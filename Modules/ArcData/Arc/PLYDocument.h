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

#ifndef ARC_DATA_PLY_DOCUMENT_H
#define ARC_DATA_PLY_DOCUMENT_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>

#include "PLYPropertyTypes.h"
#include "PLYElementType.h"
#include "PLYElement.h"

namespace Arc
{

typedef string PLYPropertyType;

typedef string PLYFormat;

class PLYDocument
	: public ManagedObject
{
public:

	static PLYDocument INVALID;

	static PLYFormat INVALID_FORMAT;

	static PLYFormat FORMAT_ASCII;

	static PLYFormat FORMAT_BINARY_LITTLE_ENDIAN;

	static PLYFormat FORMAT_BINARY_BIG_ENDIAN;

	static PLYDocument LoadFile( const string& filename );

	static PLYDocument LoadString( const string& data );

	static PLYDocument LoadBuffer( Buffer& data );

	inline PLYDocument( const PLYDocument& rhs )
		: m_Version(rhs.m_Version),
		  m_Format(rhs.m_Format),
		  m_ElementTypesList(rhs.m_ElementTypesList),
		  m_ElementTypes(rhs.m_ElementTypes),
		  m_Elements(rhs.m_Elements),
		  m_LastElementType(rhs.m_LastElementType)
	{
		PLYElement* pElement;
		for (auto it = m_Elements.itBegin(); it != m_Elements.itEnd(); ++it)
		{
			pElement = &(*it);
			pElement->setDocument(this);
		}
	}

	virtual inline string getClassName( void ) const { return "Arc PLY Document"; }

	inline float getVersion( void ) const { return m_Version; }

	inline void setVersion( const float& version ) { m_Version = version; }

	inline PLYFormat getFormat( void ) const { return m_Format; }

	inline void setFormat( const PLYFormat& format ) { m_Format = format; }

	inline PLYElementType& getElementType( const string & name )
	{
		return (m_ElementTypes.containsKey(name) ? m_ElementTypes[name] : PLYElementType::INVALID);
	}

	inline PLYElementType& getElementType( const int& index )
	{
		return (m_ElementTypesList.hasIndex(index) ? getElementType(m_ElementTypesList[index]) : PLYElementType::INVALID);
	}

	PLYElement& addElement( const string& type );

	inline PLYElement& addElement( const int& index )
	{
		return (m_ElementTypesList.hasIndex(index) ? addElement(m_ElementTypesList[index]) : PLYElement::INVALID); 
	}

	ArrayList<PLYElement> getElementsOfType( const string& type );

	inline ArrayList<PLYElement> getElementsOfType( const int& index )
	{
		return (m_ElementTypesList.hasIndex(index) ? getElementsOfType(m_ElementTypesList[index]) : ArrayList<PLYElement>()); 
	}

private:

	inline PLYDocument( void )
		: m_Version(),
		  m_Format(),
		  m_ElementTypesList(),
		  m_ElementTypes(),
		  m_Elements(),
		  m_LastElementType()
	{ }

	static PLYDocument LoadHeader( Buffer& data );

	static void LoadAscii( PLYDocument& doc, Buffer& data );

	static void LoadBinaryBigEndian( PLYDocument& doc, Buffer& data );

	static void LoadBinaryLittleEndian( PLYDocument& doc, Buffer& data );

	void addElementType( const string& name, const unsigned int& count );

	bool hasLastElementType( void ) const;

	PLYElementType& getLastElementType( void );

	float m_Version;

	PLYFormat m_Format;

	ArrayList<string> m_ElementTypesList;
	
	Map<string, PLYElementType> m_ElementTypes;

	ArrayList<PLYElement> m_Elements;

	string m_LastElementType;

}; // class PLYDocument

} // namespace Arc

#endif // ARC_DATA_PLY_DOCUMENT_H