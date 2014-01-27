#include "FBXDocument.h"

Arc::FBXType Arc::FBXDocument::FBX_TYPE_ASCII = "FBXType.ascii";

Arc::FBXType Arc::FBXDocument::FBX_TYPE_BINARY = "FBXType.binary";

Arc::FBXDocument Arc::FBXDocument::LoadFile( const string& filename, const FBXType& type )
{
    Buffer buff = Buffer::LoadFromFile(filename);
	return FBXDocument::LoadBuffer(buff, type);
}

Arc::FBXDocument Arc::FBXDocument::LoadString( const string& data, const FBXType& type )
{
    Buffer buff = Buffer(data);
	return FBXDocument::LoadBuffer(buff, type);
}

Arc::FBXDocument Arc::FBXDocument::LoadBuffer( Buffer& data, const FBXType& type )
{
	FBXDocument doc;
	string line;

	ArrayList<string> path;

	data.resetReadIndex();

	while ( ! data.endOfBuffer())
	{
		line = data.readNextLine();

		if (line.length() == 0)
			continue;

		if (line[0] == ';')
			continue;

		if (Arc_StringContains(line, "{"))
		{
			string name = Arc_StringSplit(line, ':', 2)[0];
			Arc_Trim(name);

			path.add(name);
			continue;
		}
		
		if (Arc_StringContains(line, "}"))
		{
			path.popBack();
			continue;
		}

		ArrayList<string> splitLine = Arc_StringSplit(line, ':', 2);

		if (splitLine.getSize() != 2)
			continue;

		string key = splitLine[0];
		string val = splitLine[1];
		
		Arc_Trim(key);
		Arc_Trim(val);

		if ( ! path.isEmpty() && path.contains("FBXHeaderExtension"))
		{
			if ( ! path.isEmpty() && path.contains("CreationTimeStamp"))
			{
				int intVal = Arc_ParseInt(val);

				if (key == "Version")
				{
					doc.getHeader().getTimeStamp().setVersion(intVal);
				}
				else if (key == "Year")
				{
					doc.getHeader().getTimeStamp().setYear(intVal);
				}
				else if (key == "Month")
				{
					doc.getHeader().getTimeStamp().setMonth(intVal);
				}
				else if (key == "Day")
				{
					doc.getHeader().getTimeStamp().setDay(intVal);
				}
				else if (key == "Hour")
				{
					doc.getHeader().getTimeStamp().setHours(intVal);
				}
				else if (key == "Minute")
				{
					doc.getHeader().getTimeStamp().setMinutes(intVal);
				}
				else if (key == "Second")
				{
					doc.getHeader().getTimeStamp().setSeconds(intVal);
				}
				else if (key == "Millisecond")
				{
					doc.getHeader().getTimeStamp().setMilliseconds(intVal);
				}
			}
			if ( ! path.isEmpty() && path.getBack() == "OtherFlags")
			{
				doc.getHeader().setFlag(key, Arc_ParseBool(val));
			}
			else if (key == "FBXHeaderVersion")
			{
				doc.getHeader().setHeaderVersion(Arc_ParseInt(val));
			}
			else if (key == "FBXVersion")
			{
				doc.getHeader().setVersion(Arc_ParseInt(val));
			}
			else if (key == "Creator")
			{
				if (val.length() >= 2 && val[0] == '"' && val[val.length() - 1] == '"')
				{
					doc.getHeader().setCreator(Arc_Substring(val, 1, val.length() - 2));
				}
				else
				{
					// Creator isn't a valid string
				}
			}

		}
	}

	return doc;
}
