#include "OBJFace.h"

#include "OBJDocument.h"

Arc::OBJFace Arc::OBJFace::INVALID = OBJFace(nullptr);

Arc::Vector3 Arc::OBJFace::getVertex( const int& index ) const
{
	if (mp_Document == nullptr)
		return Vector3::NEGATIVE_ONE;

	return (m_VertexIndexes.hasIndex(index) ? mp_Document->getVertex(m_VertexIndexes[index]) : Vector3::NEGATIVE_ONE);
}

Arc::Vector3 Arc::OBJFace::getNormal( const int& index ) const
{
	if (mp_Document == nullptr)
		return Vector3::NEGATIVE_ONE;

	return (m_NormalIndexes.hasIndex(index) ? mp_Document->getNormal(m_NormalIndexes[index]) : Vector3::NEGATIVE_ONE);
}

Arc::Vector2 Arc::OBJFace::getTextureVertex( const int& index ) const
{
	if (mp_Document == nullptr)
		return Vector2::NEGATIVE_ONE;

	return (m_TextureVertexIndexes.hasIndex(index) ? mp_Document->getTextureVertex(m_TextureVertexIndexes[index]) : Vector2::NEGATIVE_ONE);
}
