#include "PLYElementType.h"

#include "PLYDocument.h"

Arc::PLYElementType Arc::PLYElementType::INVALID = PLYElementType(~0);

void Arc::PLYElementType::addPropertyType( const string& type, const string& name )
{
	m_PropertyTypes.add(name, type);
	m_PropertyNames.add(name);
}