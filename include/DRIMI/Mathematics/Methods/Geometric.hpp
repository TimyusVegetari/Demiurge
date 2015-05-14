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
 * \file Geometric.hpp
 * \brief Geometric methods.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014
 *
 */

#ifndef DRIMI_MATHEMATICS_Geometric
#define DRIMI_MATHEMATICS_Geometric

#if defined(DRIMI_MATHEMATICS_MESSAGES)
# pragma message("DRIMI: DRIMI_MATHEMATICS_Geometric extension included")
#endif

namespace drimi {

  ////////////////////////////////////////////////////////////
  /// \brief Compute the length of x, i.e., sqrt(x * x).
  ///
  /// \return Length of the vectors.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Length (
    GLfloat const & fX
  );
  GLfloat Length (
    Vec2f const & v2fX
  );
  GLfloat Length (
    Vec3f const & v3fX
  );
  GLfloat Length (
    Vec4f const & v4fX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Compute the distance between p0 and p1, i.e., length(p0 - p1).
  ///
  /// \return Distance between the points.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Distance (
    GLfloat const & fP0,
    GLfloat const & fP1
  );
  GLfloat Distance (
    Vec2f const & v2fP0,
    Vec2f const & v2fP1
  );
  GLfloat Distance (
    Vec3f const & v3fP0,
    Vec3f const & v3fP1
  );
  GLfloat Distance (
    Vec4f const & v4fP0,
    Vec4f const & v4fP1
  );

  ////////////////////////////////////////////////////////////
  /// \brief Compute the dot product of x and y, i.e., result = x * y.
  ///
  /// \return Dot product of the vectors.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Dot (
    GLfloat const & fX,
    GLfloat const & fY
  );
	GLfloat Dot (
    Vec2f const & v2fX,
    Vec2f const & v2fY
  );
	GLfloat Dot (
    Vec3f const & v3fX,
    Vec3f const & v3fY
  );
	GLfloat Dot (
    Vec4f const & v4fX,
    Vec4f const & v4fY
  );

  ////////////////////////////////////////////////////////////
  /// \brief Compute the cross product of x and y.
  ///
  /// \return Cross product of the vectors.
  ///
  ////////////////////////////////////////////////////////////
  Vec3f Cross (
    Vec3f const & v3fX,
		Vec3f const & v3fY
  );

  ////////////////////////////////////////////////////////////
  /// \brief Compute a vector in the same direction as x but with length of 1.
  ///
  /// \return Normalized vectors.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Normalize (
    GLfloat const & fX
  );
  Vec2f Normalize (
    Vec2f const & v2fX
  );
  Vec3f Normalize (
    Vec3f const & v3fX
  );
  Vec4f Normalize (
    Vec4f const & v4fX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Check if the normal of the face is in the same
  /// direction with the vector or not.
  ///
  /// \return If dot(Nref, I) < 0.0, return N, otherwise, return -N.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Faceforward (
    GLfloat const & fN,
		GLfloat const & fI,
		GLfloat const & fNref
  );

  ////////////////////////////////////////////////////////////
  /// \brief For the incident vector I and surface orientation N,
  /// returns the reflection direction.
  ///
  /// \return Reflection direction : result = I - 2.0 * dot(N, I) * N.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Reflect (
    GLfloat const & fI,
    GLfloat const & fN
  );

  ////////////////////////////////////////////////////////////
  /// \brief For the incident vector I and surface normal N,
  /// and the ratio of indices of refraction eta,
  /// return the refraction vector.
  ///
  /// \return Refraction vector.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Refract (
    GLfloat const & fI,
		GLfloat const & fN,
		GLfloat const & fEta
  );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Geometric
