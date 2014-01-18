/* This file is part of ArcData.
 * 
 * ArcData is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcData is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcData; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_DATA_CSV_DOCUMENT_H
#define ARC_DATA_CSV_DOCUMENT_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include "CSVRow.h"

namespace Arc
{

class CSVDocument
	: public ManagedObject
{
public:

	static CSVDocument LoadFile( const string& filename );
	static CSVDocument LoadFileWithHeadings( const string& filename );
	static CSVDocument LoadString( const string& data );
	static CSVDocument LoadStringWithHeadings( const string& data );

	virtual ~CSVDocument( void );

	virtual inline string getClassName( void ) const { return "CSV Document"; }

private:

	CSVDocument( void );

	bool m_UseHeadings;

	Map<string, int> m_Headings;

	ArrayList<CSVRow> m_Rows;

}; // class CSVDocument

}; // namespace Arc

#endif // ARC_DATA_CSV_DOCUMENT_H