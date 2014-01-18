#include "StringFunctions.h"

const size_t Arc::StringBadPosition = string::npos;
const size_t Arc::StringBadLength = string::npos;

string Arc::Arc_StringBasename( const string& path )
{
	char splitString = (path.find("\\") != StringBadPosition ? '\\' : '/');

	ArrayList<string> parts = Arc_StringSplit(path, splitString);

	return parts[parts.getSize() - 1];
}

void Arc::Arc_StringToLower( string& str )
{
	for (unsigned int i = 0; i < str.length(); ++i)
		str[i] = tolower(str[i]);
}

void Arc::Arc_StringToUpper( string& str )
{
	for (unsigned int i = 0; i < str.length(); ++i)
		str[i] = toupper(str[i]);
}

void Arc::Arc_StringUCWords( string& str )
{
	// TODO(sdl.slane@gmail.com): Implement
}

void Arc::Arc_StringUCFirst( string& str )
{
	// TODO(sdl.slane@gmail.com): Implement
}

string Arc::Arc_StringGetUCWords( const string& str )
{
	// TODO(sdl.slane@gmail.com): Implement
	return "";
}

string Arc::Arc_StringGetUCFirst( const string& str )
{
	// TODO(sdl.slane@gmail.com): Implement
	return "";
}

Arc::ArrayList<string> Arc::Arc_StringSplit( const string& str, const char& sep, const int& limit /*= -1 */ )
{
	ArrayList<string> stringParts;

	unsigned int lastEnd = 0;
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		if (str[i] == sep)
		{
			if (limit != -1 && stringParts.getSize() >= (unsigned)limit - 1)
				break;

			stringParts.add(str.substr(lastEnd, i - lastEnd));
			lastEnd = i + 1;
		}
	}

	if (lastEnd < str.length())
	{
		stringParts.add(str.substr(lastEnd));
	}

	return stringParts;
}

string Arc::Arc_StringJoin( const string& glue, const ArrayList<string>& pieces )
{
	string str;

	for (unsigned int i = 0; i < pieces.getSize(); ++i)
	{
		str += pieces[i];
		if (i != pieces.getSize() - 1)
			str += glue;
	}

	return str;
}

int Arc::Arc_StringReplaceNext( string& str, const string& search, const string& replace )
{
	unsigned int pos = str.find(search);

	if (pos == StringBadPosition)
		return -1;

	str.replace(pos, search.length(), replace);

	return pos;
}

int Arc::Arc_StringReplaceAll( string& str, const string& search, const string& replace )
{
	unsigned int pos = str.find(search);
	unsigned int count = 0;

	// TODO(sdl.slane@gmail.com): Prevent replacing the same text repeatedly
	while (pos != StringBadPosition)
	{
		str.replace(pos, search.length(), replace);
		pos = str.find(search);
		count++;
	}

	return count;
}

string Arc::Arc_Substring( const string& str, const unsigned int& begin, const int& maxLength /*= -1 */ )
{
	if (begin >= str.length())
		return "";

	unsigned int fullMaxLength = (maxLength < 0 ? StringBadLength : unsigned(maxLength));

	return str.substr(begin, fullMaxLength);
}