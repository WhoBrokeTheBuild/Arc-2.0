#include "XMLDocument.h"

bool Arc::XMLDocument::loadBuffer(Buffer& buffer)
{
	buffer.resetReadIndex();
	
	XMLElement* m_Root = nullptr;
	XMLElement* m_Curr = nullptr;

	bool inTag = false;
	bool inTagName = false;
	bool escapeNextChar = false;
	bool inString = false;
	string tagName = "";
	string tagData = "";

	char ch = buffer.readNextChar();
	char lastCh = '\0';
	char nextCh = '\0';

	while ( ! buffer.endOfBuffer())
	{
		lastCh = ch;
		ch = nextCh;
		nextCh = buffer.readNextChar();

		if (inTag)
		{
			if (m_Curr == nullptr)
			{
				m_Error = "Error occurred reading tag";
				m_HasError = true;
				return false;
			}

			if (inTagName)
			{
				if (ch == ' ')
				{
					inTagName = false;
					m_Curr->setName(tagName);
					tagName = "";
				}
				else
				{
					tagName += ch;
				}
			}

			switch (ch)
			{
			case '>':

				inTag = false;

				break;
			case '/':

				//m_Curr->setIsSingle(true);

				break;
			}
		}
		else
		{
			if (ch == '<')
			{
				inTag = true;
				inTagName = true;
				tagName = "";
			}
			else
			{
				tagData += ch;
			}
		}
	}

	return true;
}
