#include "OBJObject.h"

#include "OBJDocument.h"
#include "OBJFace.h"
#include "OBJMaterial.h"

Arc::OBJObject Arc::OBJObject::INVALID = OBJObject();

Arc::OBJFace& Arc::OBJObject::getFace( const int& index )
{
	if (mp_Document == nullptr)
		return OBJFace::INVALID;

	int offsetIndex = m_FaceStartInd + index;

	if ( ! Arc_Between(offsetIndex, m_FaceStartInd, m_FaceEndInd))
		return OBJFace::INVALID;

	return mp_Document->getFace(offsetIndex);
}

Arc::OBJMaterial& Arc::OBJObject::getMaterial( void )
{
	if (mp_Document == nullptr)
		return OBJMaterial::INVALID;

	return mp_Document->getMaterial(m_MaterialName);
}
