/* This file is part of ArcCore.
 * 
 * ArcCore is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcCore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcCore; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_CORE_MATH_FUNCTIONS_H
#define ARC_CORE_MATH_FUNCTIONS_H

namespace Arc
{
	
/* Determines if a value is between two other numbers
 * 
 * @param value: The value to check
 * @param min: The minimum value of the range to check
 * @param max: The maximum value of the range to check
 * @returns: True if the value is between the min and max values or equal to either, False otherwise
 */ 
template <class Number>
static inline bool Arc_between( Number value, Number min, Number max ) 
{ 
	return ( value >= min && value <= max); 
}

}; // namespace Arc

#endif // ARC_CORE_MATH_FUNCTIONS_H