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

#ifndef ARC_DATA_FBX_OBJECTS_H
#define ARC_DATA_FBX_OBJECTS_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include "FBXModel.h"

namespace Arc
{

class FBXObjects
	: public ManagedObject
{
public:

	inline FBXObjects( void )
		: m_Models()
	{ }

	inline FBXObjects( const FBXObjects& rhs )
		: m_Models(rhs.m_Models)
	{ }

	virtual inline string getClassName( void ) const { return "Arc FBX Objects"; }

	inline bool hasModel( const string& id ) { return m_Models.containsKey(id); }

	inline void addModel( const string& id ) { m_Models.add(id, FBXModel(id)); }

	inline FBXModel& getModel( const string& id ) { return (hasModel(id) ? m_Models[id] : FBXModel::INVALID); }

	ArrayList<string> getModelNames( void ) const;

private:

	Map<string, FBXModel> m_Models;

}; // class FBXObjects

} // namespace Arc

#endif // ARC_DATA_FBX_OBJECTS_H