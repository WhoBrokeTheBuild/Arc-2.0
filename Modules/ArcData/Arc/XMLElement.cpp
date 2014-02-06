#include "XMLElement.h"

void Arc::XMLElement::attachChildren(void)
{
	XMLElement* pChild;
	auto end = m_Children.itEnd();
	for (auto it = m_Children.itBegin(); it != end; ++it)
	{
		pChild = (*it);
		pChild->setParent(this);
	}
}
