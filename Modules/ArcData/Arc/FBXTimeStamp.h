/* This file is part of Arc.
 * 
 * Arc is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * Arc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with Arc; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_DATA_FBX_TIME_STAMP_H
#define ARC_DATA_FBX_TIME_STAMP_H

#include <Arc/ManagedObject.h>

#include <Arc/MathFunctions.h>

namespace Arc
{

class FBXTimeStamp
	: public ManagedObject
{
public:

	inline FBXTimeStamp( void )
		: m_Version(),
		  m_Year(),
		  m_Month(),
		  m_Day(),
		  m_Hours(),
		  m_Minutes(),
		  m_Seconds(),
		  m_Milliseconds()
	{ }

	inline FBXTimeStamp( const FBXTimeStamp& rhs )
		: m_Version(rhs.m_Version),
		  m_Year(rhs.m_Year),
		  m_Month(rhs.m_Month),
		  m_Day(rhs.m_Day),
		  m_Hours(rhs.m_Hours),
		  m_Minutes(rhs.m_Minutes),
		  m_Seconds(rhs.m_Seconds),
		  m_Milliseconds(rhs.m_Milliseconds)
	{ }

	virtual inline string getClassName( void ) const { return "Arc FBX Time Stamp"; }

	inline unsigned int getVersion( void ) const { return m_Version; }

	inline void setVersion( unsigned int val ) { m_Version = val; }

	inline unsigned int getYear( void ) const { return m_Year; }

	inline void setYear( unsigned int val ) { m_Year = val; }

	inline unsigned short getMonth( void ) const { return m_Month; }

	inline void setMonth( unsigned short val ) { m_Month = Arc_Clamp(val, (unsigned short)1, (unsigned short)12); }

	inline unsigned short getDay( void ) const { return m_Day; }

	inline void setDay( unsigned short val ) { m_Day = Arc_Clamp(val, (unsigned short)1, (unsigned short)365); }

	inline unsigned short getHours( void ) const { return m_Hours; }

	inline void setHours( unsigned short val ) { m_Hours = Arc_Clamp(val, (unsigned short)0, (unsigned short)23); }

	inline unsigned short getMinutes( void ) const { return m_Minutes; }

	inline void setMinutes( unsigned short val ) { m_Minutes = Arc_Clamp(val, (unsigned short)0, (unsigned short)59); }

	inline unsigned short getSeconds( void ) const { return m_Seconds; }

	inline void setSeconds( unsigned short seconds ) { m_Seconds = Arc_Clamp(seconds, (unsigned short)0, (unsigned short)59); }

	inline unsigned int getMilliseconds( void ) const { return m_Milliseconds; }

	inline void setMilliseconds( unsigned int ms ) { m_Milliseconds = ms; }

private:

	unsigned int m_Version;

	unsigned int m_Year;

	unsigned short m_Month;

	unsigned short m_Day;

	unsigned short m_Hours;

	unsigned short m_Minutes;

	unsigned short m_Seconds;

	unsigned int m_Milliseconds;

};

}; // namespace Arc

#endif // ARC_DATA_FBX_TIME_STAMP_H