#include "OBJFace.h"

#include "OBJDocument.h"

Arc::OBJFace Arc::OBJFace::INVALID = OBJFace(nullptr);

Arc::Vector3 Arc::OBJFace::getVertex( const int& index ) const
{
	if ( ! isValid())
		return Vector3::NEGATIVE_ONE;

	return (m_VertexIndexes.hasIndex(index) ? mp_Document->getVertex(m_VertexIndexes[index]) : Vector3::NEGATIVE_ONE);
}

Arc::Vector3 Arc::OBJFace::getNormal( const int& index ) const
{
	if ( ! isValid())
		return Vector3::NEGATIVE_ONE;

	return (m_NormalIndexes.hasIndex(index) ? mp_Document->getNormal(m_NormalIndexes[index]) : Vector3::NEGATIVE_ONE);
}

void Arc::OBJFace::addVertex( int vertexInd, int normalInd /*= -1 */ )
{
	m_VertexIndexes.add(vertexInd);

	if (normalInd != -1)
		m_NormalIndexes.add(normalInd);
}
