/* This file is part of ArcGame.
 *
 * ArcGame is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ArcGame is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcGame; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author: Stephen Lane-Walsh
 *
 */

#ifndef ARC_GAME_ARC_GAME_VERSION_H
#define ARC_GAME_ARC_GAME_VERSION_H

#include <Arc/ArcCore.h>
#include <Arc/Types.h>

namespace Arc
{

#define ARC_AUDIO_MAJOR_VERSION 0
#define ARC_AUDIO_MINOR_VERSION 1
#define ARC_AUDIO_PATCH_VERSION 0

	inline Arc_uint8_t ArcGame_GetMajorVersion( void )
	{
		return ARC_AUDIO_MAJOR_VERSION;
	}

	inline Arc_uint8_t ArcGame_GetMinorVersion( void )
	{
		return ARC_AUDIO_MINOR_VERSION;
	}

	inline Arc_uint8_t ArcGame_GetPatchVersion( void )
	{
		return ARC_AUDIO_PATCH_VERSION;
	}

	inline Arc_Version ArcGame_GetVersion( void )
	{
		Arc_Version current;
		current.Major = ARC_AUDIO_MAJOR_VERSION;
		current.Minor = ARC_AUDIO_MINOR_VERSION;
		current.Patch = ARC_AUDIO_PATCH_VERSION;
		return current;
	}

	inline string ArcGame_GetVersionString( void )
	{
		char version[15];

#if defined(ARC_OS_WINDOWS)

		sprintf_s(version, "%d.%d.%d", ARC_AUDIO_MAJOR_VERSION, ARC_AUDIO_MINOR_VERSION, ARC_AUDIO_PATCH_VERSION);

#else

		sprintf(version, "%d.%d.%d", ARC_AUDIO_MAJOR_VERSION, ARC_AUDIO_MINOR_VERSION, ARC_AUDIO_PATCH_VERSION);

#endif

		return string(version);
	}

	inline bool ArcGame_AboveVersion( Arc_uint8_t major, Arc_uint8_t minor, Arc_uint8_t patch )
	{
		return ( (major >= ARC_AUDIO_MAJOR_VERSION) && (minor >= ARC_AUDIO_MINOR_VERSION) && (patch >= ARC_AUDIO_PATCH_VERSION) );
	}

	inline bool ArcGame_AboveVersion( const Arc_Version& version )
	{
		return ArcGame_AboveVersion(version.Major, version.Minor, version.Patch);
	}

} // namespace Arc

#endif // ARC_GAME_ARC_GAME_VERSION_H
