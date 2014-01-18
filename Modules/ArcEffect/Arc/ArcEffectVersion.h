/* This file is part of ArcEffect.
 * 
 * ArcEffect is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcEffect is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcEffect; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_EFFECT_ARC_EFFECT_VERSION_H
#define ARC_EFFECT_ARC_EFFECT_VERSION_H

#include <Arc/ArcCore.h>
#include <Arc/ArcTypes.h>

namespace Arc
{

#define ARC_EFFECT_MAJOR_VERSION 0
#define ARC_EFFECT_MINOR_VERSION 1
#define ARC_EFFECT_PATCH_VERSION 0

inline uint8_t ArcEffect_GetMajorVersion( void )
{
	return ARC_EFFECT_MAJOR_VERSION;
}

inline uint8_t ArcEffect_GetMinorVersion( void )
{
	return ARC_EFFECT_MINOR_VERSION;
}

inline uint8_t ArcEffect_GetPatchVersion( void )
{
	return ARC_EFFECT_PATCH_VERSION;
}

inline Arc_Version ArcEffect_GetVersion( void )
{
	Arc_Version current;
	current.Major = ARC_EFFECT_MAJOR_VERSION;
	current.Minor = ARC_EFFECT_MINOR_VERSION;
	current.Patch = ARC_EFFECT_PATCH_VERSION;
	return current;
}

inline string ArcEffect_GetVersionString( void )
{
	char version[15];

#if defined(ARC_OS_WINDOWS)

	sprintf_s(version, "%d.%d.%d", ARC_EFFECT_MAJOR_VERSION, ARC_EFFECT_MINOR_VERSION, ARC_EFFECT_PATCH_VERSION);

#else

	sprintf(version, "%d.%d.%d", ARC_EFFECT_MAJOR_VERSION, ARC_EFFECT_MINOR_VERSION, ARC_EFFECT_PATCH_VERSION);

#endif

	return string(version);
}

inline bool ArcEffect_AboveVersion( uint8_t major, uint8_t minor, uint8_t patch )
{
	return ( (major >= ARC_EFFECT_MAJOR_VERSION) && (minor >= ARC_EFFECT_MINOR_VERSION) && (patch >= ARC_EFFECT_PATCH_VERSION) );
}

inline bool ArcEffect_AboveVersion( const Arc_Version& version )
{
	return ArcEffect_AboveVersion(version.Major, version.Minor, version.Patch);
}

}; // namespace Arc

#endif // ARC_EFFECT_ARC_EFFECT_VERSION_H