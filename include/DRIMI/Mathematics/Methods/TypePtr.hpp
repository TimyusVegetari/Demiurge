////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Mathematics.
// Copyright (C) 2014 Acroute Anthony (ant110283@hotmail.fr)
//
// Demiurge is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Demiurge is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Demiurge.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file TypePtr.hpp
 * \brief Methods for return the constant address to the data of the input parameter.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014
 *
 */

#ifndef DRIMI_MATHEMATICS_TypePtr
#define DRIMI_MATHEMATICS_TypePtr

#if defined(DRIMI_MATHEMATICS_MESSAGES)
# pragma message("DRIMI: DRIMI_MATHEMATICS_TypePtr extension included")
#endif

namespace drimi {

  ////////////////////////////////////////////////////////////
  /// \brief ValuePtr fo Vec2f
  ///
  /// \return Constant address of float.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr ( Vec2f const & v2fVec );
	GLfloat * ValuePtr ( Vec2f & v2fVec );

  ////////////////////////////////////////////////////////////
  /// \brief ValuePtr fo Vec3f
  ///
  /// \return Constant address of float.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr ( Vec3f const & v3fVec );
	GLfloat * ValuePtr ( Vec3f & v3fVec );

  ////////////////////////////////////////////////////////////
  /// \brief ValuePtr fo Vec4f
  ///
  /// \return Constant address of float.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr (Vec4f const & v4fVec );
	GLfloat * ValuePtr (Vec4f & v4fVec );

  ////////////////////////////////////////////////////////////
  /// \brief ValuePtr fo Mat4x4f
  ///
  /// \return Constant address of float.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr ( Mat4x4f const & m4fMat );
	GLfloat * ValuePtr ( Mat4x4f & m4fMat );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_TypePtr
