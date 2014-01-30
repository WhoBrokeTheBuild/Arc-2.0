#include "PLYElement.h"

#include "PLYDocument.h"

Arc::PLYElement Arc::PLYElement::INVALID = PLYElement();

void Arc::PLYElement::setDocument( PLYDocument* pDocument )
{
	mp_Document = pDocument;
}

Arc::PLYDocument* Arc::PLYElement::getDocument( void )
{
	return mp_Document;
}