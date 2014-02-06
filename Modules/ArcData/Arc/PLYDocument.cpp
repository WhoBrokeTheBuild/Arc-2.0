#include "PLYDocument.h"

#include "PLYElementType.h"

Arc::PLYDocument Arc::PLYDocument::INVALID = PLYDocument();

Arc::PLYFormat Arc::PLYDocument::INVALID_FORMAT = "PLYFormat.invalid";

Arc::PLYFormat Arc::PLYDocument::FORMAT_ASCII = "PLYFormat.ascii";

Arc::PLYFormat Arc::PLYDocument::FORMAT_BINARY_LITTLE_ENDIAN = "PLYFormat.binaryLittleEndian";

Arc::PLYFormat Arc::PLYDocument::FORMAT_BINARY_BIG_ENDIAN = "PLYFormat.binaryBigEndian";

void Arc::PLYDocument::loadFile( const string& filename )
{
	m_Filename = filename;
	Buffer buff = Buffer::LoadFromFile(m_Filename);
	loadBuffer(buff);
}

void Arc::PLYDocument::loadString( const string& data )
{
	Buffer buff = Buffer(data);
	loadBuffer(buff);
}

void Arc::PLYDocument::loadBuffer( Buffer& data )
{
	reset();
	loadHeader(data);

	if (getFormat() == PLYDocument::FORMAT_ASCII)
	{
		loadAscii(data);
	}
	else if (getFormat() == PLYDocument::FORMAT_BINARY_BIG_ENDIAN)
	{
		loadBinaryBigEndian(data);
	}
	else if (getFormat() == PLYDocument::FORMAT_BINARY_LITTLE_ENDIAN)
	{
		loadBinaryLittleEndian(data);
	}
}

void Arc::PLYDocument::loadHeader( Buffer& data )
{
	data.resetReadIndex();

	string line;

	line = data.readNextLine();

	if (line != "ply")
		return;

	while ( ! data.endOfBuffer())
	{
		line = data.readNextLine();

		if (line == "end_header")
			break;

		ArrayList<string> parts = Arc_StringSplit(line, " ");

		if (parts.getSize() == 0)
			continue;

		if (parts[0] == "comment")
		{
			addComment(Arc_Substring(line, 7));
			continue;
		}

		if (parts[0] == "format")
		{
			if (parts.getSize() >= 3)
			{
				PLYFormat format = PLYDocument::INVALID_FORMAT;

				if (parts[1] == "ascii")
				{
					format = PLYDocument::FORMAT_ASCII;
				}
				else if (parts[1] == "binary_little_endian")
				{
					format = PLYDocument::FORMAT_BINARY_LITTLE_ENDIAN;
				}
				else if (parts[1] == "binary_big_endian")
				{
					format = PLYDocument::FORMAT_BINARY_BIG_ENDIAN;
				}

				setFormat(format);
				setVersion(Arc_ParseFloat(parts[2]));
			}
			else
			{
				// Error, Format Ignored
			}
		}
		else if (parts[0] == "element")
		{
			if (parts.getSize() >= 3)
			{
				addElementType(parts[1], (unsigned)Arc_ParseInt(parts[2]));
			}
			else
			{
				// Error, Element Ignored
			}
		}
		else if (parts[0] == "property")
		{
			if (parts.getSize() >= 3 && hasLastElementType())
			{
				if (parts[1] == "list")
				{
					if (parts.getSize() >= 5)
					{
						PLYElementType& elmType = getLastElementType();
						elmType.setIsList(true);
						elmType.setListSizeType(parts[2]);
						elmType.setListType(parts[3]);
						elmType.setListName(parts[4]);
					}
					else
					{
						// Error, Property List Ignored
					}
				}
				else
				{
					getLastElementType().addPropertyType(parts[1], parts[2]);
				}
			}
			else
			{
				// Error, Property Ignored
			}
		}

	}
}

void Arc::PLYDocument::addElementType( const string& name, const unsigned int& count )
{
	m_ElementTypes.add(name, PLYElementType(count));
	m_ElementTypesList.add(name);
	m_LastElementType = name;
}

Arc::PLYElement& Arc::PLYDocument::addElement( const string& type )
{
	if ( ! m_ElementTypes.containsKey(type))
		return PLYElement::INVALID;

	m_Elements.add(PLYElement(this));
	m_Elements.getBack().setTypeName(type);

	return m_Elements.getBack();
}

Arc::PLYElement& Arc::PLYDocument::addElement( const int& index )
{
	return (m_ElementTypesList.hasIndex(index) ? addElement(m_ElementTypesList[index]) : PLYElement::INVALID);
}

bool Arc::PLYDocument::hasLastElementType( void ) const
{
	return ( ! m_ElementTypes.isEmpty() );
}

Arc::PLYElementType& Arc::PLYDocument::getLastElementType( void )
{
	if (m_LastElementType == "" || ! m_ElementTypes.containsKey(m_LastElementType))
		return PLYElementType::INVALID;

	return m_ElementTypes[m_LastElementType];
}

void Arc::PLYDocument::loadAscii( Buffer& data )
{
	string line;

	unsigned int elementIndex = 0;
	unsigned int recordIndex = 0;

	while ( ! data.endOfBuffer())
	{
		line = data.readNextLine();

		if (recordIndex >= getElementType(elementIndex).getExpectedCount())
		{
			elementIndex++;
			recordIndex = 0;
		}

		PLYElementType& type = getElementType(elementIndex);

		PLYElement& elm = addElement(elementIndex);
		recordIndex++;

		ArrayList<string> parts = Arc_StringSplit(line, ' ');

		if (parts.isEmpty())
			continue;

		if (type.isList())
		{
			unsigned int count = Arc_ParseInt(parts[0]);

			if (parts.getSize() == count + 1)
			{
				for (unsigned int i = 1; i <= count; ++i)
				{
					if (type.getListType() == PLYPropertyTypes::PROP_TYPE_CHAR)
					{
						elm.addCharDataToList((char)Arc_ParseShort(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_UCHAR)
					{
						elm.addUCharDataToList((unsigned char)Arc_ParseShort(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_SHORT)
					{
						elm.addShortDataToList(Arc_ParseShort(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_USHORT)
					{
						elm.addUShortDataToList(Arc_ParseShort(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_INT)
					{
						elm.addIntDataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_UINT)
					{
						elm.addUIntDataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_FLOAT)
					{
						elm.addFloatDataToList(Arc_ParseFloat(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_DOUBLE)
					{
						elm.addDoubleDataToList(Arc_ParseDouble(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_INT8)
					{
						elm.addInt8DataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_UINT8)
					{
						elm.addUInt8DataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_INT16)
					{
						elm.addInt16DataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_UINT16)
					{
						elm.addUInt16DataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_INT32)
					{
						elm.addInt32DataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_UINT32)
					{
						elm.addUInt32DataToList(Arc_ParseInt(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_INT64)
					{
						elm.addInt64DataToList(Arc_ParseLong(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_UINT64)
					{
						elm.addUInt64DataToList(Arc_ParseLong(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_FLOAT32)
					{
						elm.addFloat32DataToList(Arc_ParseFloat(parts[i]));
					}
					else if (type.getListType() == PLYPropertyTypes::PROP_TYPE_FLOAT64)
					{
						elm.addFloat64DataToList(Arc_ParseDouble(parts[i]));
					}
				}
			}
			else
			{
				// Error, line ignored
			}
		}
		else
		{
			if (parts.getSize() == type.getNumProperties())
			{
				for (unsigned int i = 0; i < parts.getSize(); ++i)
				{
					if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_CHAR)
					{
						elm.setCharData(type.getPropertyName(i), (char)Arc_ParseShort(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_UCHAR)
					{
						elm.setUCharData(type.getPropertyName(i), (unsigned char)Arc_ParseShort(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_SHORT)
					{
						elm.setShortData(type.getPropertyName(i), Arc_ParseShort(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_USHORT)
					{
						elm.setUShortData(type.getPropertyName(i), Arc_ParseShort(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_INT)
					{
						elm.setIntData(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_UINT)
					{
						elm.setUIntData(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_FLOAT)
					{
						elm.setFloatData(type.getPropertyName(i), Arc_ParseFloat(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_DOUBLE)
					{
						elm.setDoubleData(type.getPropertyName(i), Arc_ParseDouble(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_INT8)
					{
						elm.setInt8Data(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_UINT8)
					{
						elm.setUInt8Data(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_INT16)
					{
						elm.setInt16Data(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_UINT16)
					{
						elm.setUInt16Data(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_INT32)
					{
						elm.setInt32Data(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_UINT32)
					{
						elm.setUInt32Data(type.getPropertyName(i), Arc_ParseInt(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_INT64)
					{
						elm.setInt64Data(type.getPropertyName(i), Arc_ParseLong(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_UINT64)
					{
						elm.setUInt64Data(type.getPropertyName(i), Arc_ParseLong(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_FLOAT32)
					{
						elm.setFloat32Data(type.getPropertyName(i), Arc_ParseFloat(parts[i]));
					}
					else if (type.getPropertyType(i) == PLYPropertyTypes::PROP_TYPE_FLOAT64)
					{
						elm.setFloat64Data(type.getPropertyName(i), Arc_ParseDouble(parts[i]));
					}
				}
			}
			else
			{
				// Error, Line Ignored
			}
		}
	}
}

void Arc::PLYDocument::loadBinaryBigEndian( Buffer& data )
{
	throw std::exception("The method or operation is not implemented.");
}

void Arc::PLYDocument::loadBinaryLittleEndian( Buffer& data )
{
	throw std::exception("The method or operation is not implemented.");
}

Arc::ArrayList<Arc::PLYElement> Arc::PLYDocument::getElementsOfType( const string& type )
{
	ArrayList<Arc::PLYElement> elms;

	auto end = m_Elements.itEnd();
	for (auto it = m_Elements.itBegin(); it != end; ++it)
		if (it->getTypeName() == type)
			elms.add(*it);

	return elms;
}

Arc::ArrayList<Arc::PLYElement> Arc::PLYDocument::getElementsOfType( const int& index )
{
	return (m_ElementTypesList.hasIndex(index) ? getElementsOfType(m_ElementTypesList[index]) : ArrayList<PLYElement>());
}

Arc::PLYElementType& Arc::PLYDocument::getElementType( const string & name )
{
	return (m_ElementTypes.containsKey(name) ? m_ElementTypes[name] : PLYElementType::INVALID);
}

Arc::PLYElementType& Arc::PLYDocument::getElementType( const int& index )
{
	return (m_ElementTypesList.hasIndex(index) ? getElementType(m_ElementTypesList[index]) : PLYElementType::INVALID);
}

void Arc::PLYDocument::reset( void )
{
	m_Version = 0;
	m_Format = INVALID_FORMAT;
	m_ElementTypesList.clear();
	m_ElementTypes.clear();
	m_Elements.clear();
	m_LastElementType = PLYPropertyTypes::PROP_TYPE_INVALID;
}
