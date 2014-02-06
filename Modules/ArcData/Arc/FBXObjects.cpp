#include "FBXObjects.h"

Arc::ArrayList<string> Arc::FBXObjects::getModelNames( void ) const
{
	ArrayList<string> names;

	for (auto it = m_Models.itConstBegin(); it != m_Models.itConstEnd(); ++it)
		names.add(it->first);

	return names;
}
