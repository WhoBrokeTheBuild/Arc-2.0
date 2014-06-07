/* This file is part of ArcScript.
 *
 * ArcScript is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ArcScript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcScript; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author: Stephen Lane-Walsh
 *
 */

#ifndef ARC_SCRIPT_ARC_SCRIPT_VERSION_H
#define ARC_SCRIPT_ARC_SCRIPT_VERSION_H

#include <Arc/ArcCore.h>
#include <Arc/Types.h>

namespace Arc
{

#define ARC_SCRIPT_MAJOR_VERSION 0
#define ARC_SCRIPT_MINOR_VERSION 1
#define ARC_SCRIPT_PATCH_VERSION 2

inline Arc_uint8_t ArcScript_GetMajorVersion( void )
{
	return ARC_SCRIPT_MAJOR_VERSION;
}

inline Arc_uint8_t ArcScript_GetMinorVersion( void )
{
	return ARC_SCRIPT_MINOR_VERSION;
}

inline Arc_uint8_t ArcScript_GetPatchVersion( void )
{
	return ARC_SCRIPT_PATCH_VERSION;
}

inline Arc_Version ArcScript_GetVersion( void )
{
	Arc_Version current;
	current.Major = ARC_SCRIPT_MAJOR_VERSION;
	current.Minor = ARC_SCRIPT_MINOR_VERSION;
	current.Patch = ARC_SCRIPT_PATCH_VERSION;
	return current;
}

inline string ArcScript_GetVersionString( void )
{
	char version[15];

#if defined(ARC_OS_WINDOWS)

	sprintf_s(version, "%d.%d.%d", ARC_SCRIPT_MAJOR_VERSION, ARC_SCRIPT_MINOR_VERSION, ARC_SCRIPT_PATCH_VERSION);

#else

	sprintf(version, "%d.%d.%d", ARC_SCRIPT_MAJOR_VERSION, ARC_SCRIPT_MINOR_VERSION, ARC_SCRIPT_PATCH_VERSION);

#endif

	return string(version);
}

inline bool ArcScript_AboveVersion( Arc_uint8_t major, Arc_uint8_t minor, Arc_uint8_t patch )
{
	return ( (major >= ARC_SCRIPT_MAJOR_VERSION) && (minor >= ARC_SCRIPT_MINOR_VERSION) && (patch >= ARC_SCRIPT_PATCH_VERSION) );
}

inline bool ArcScript_AboveVersion( const Arc_Version& version )
{
	return ArcScript_AboveVersion(version.Major, version.Minor, version.Patch);
}

} // namespace Arc

#endif // ARC_SCRIPT_ARC_SCRIPT_VERSION_H
