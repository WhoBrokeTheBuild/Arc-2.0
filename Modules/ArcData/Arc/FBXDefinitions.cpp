#include "FBXDefinitions.h"

unsigned int Arc::FBXDefinitions::getTotalCount( void ) const
{
	unsigned int total = 0;

	auto end = m_TypeCounts.itConstEnd();
	for (auto it = m_TypeCounts.itConstBegin(); it != end; ++it)
		total += it->second;

	return total;
}
