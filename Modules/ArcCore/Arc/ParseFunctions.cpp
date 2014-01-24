#include "ParseFunctions.h"

short Arc::Arc_ParseShort( const string& str )
{
	std::stringstream ss;
	ss << str;

	short val;
	ss >> val;

	return val;
}

int Arc::Arc_ParseInt( const string& str )
{
	std::stringstream ss;
	ss << str;

	int val;
	ss >> val;

	return val;
}

long Arc::Arc_ParseLong( const string& str )
{
	std::stringstream ss;
	ss << str;

	long val;
	ss >> val;

	return val;
}

float Arc::Arc_ParseFloat( const string& str )
{
	std::stringstream ss;
	ss << str;

	float val;
	ss >> val;

	return val;
}

double Arc::Arc_ParseDouble( const string& str )
{
	std::stringstream ss;
	ss << str;

	double val;
	ss >> val;

	return val;
}

bool Arc::Arc_ParseBool( const string& str )
{
	if (Arc_StringGetLower(str) == "true")
		return true;

	return false;
}
