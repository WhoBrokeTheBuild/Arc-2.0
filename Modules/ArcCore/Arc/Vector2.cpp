#include "Vector2.h"

void Arc::Vector2::normalize( void )
{
	float length = getLength();
	if (length != 0)
	{
		m_X /= length;
		m_Y /= length;
	}
}

Arc::Vector2 Arc::Vector2::getNormalized( void )
{
	Vector2 copy = *this;
	copy.normalize();
	return copy;
}