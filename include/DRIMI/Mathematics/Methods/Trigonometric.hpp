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
 * \file Trigonometric.hpp
 * \brief Trigonometric methods.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014
 *
 */

#ifndef DRIMI_MATHEMATICS_Trigonometric
#define DRIMI_MATHEMATICS_Trigonometric

#if defined(DRIMI_MATHEMATICS_MESSAGES)
# pragma message("DRIMI: DRIMI_MATHEMATICS_Trigonometric extension included")
#endif

namespace drimi {

  ////////////////////////////////////////////////////////////
  /// \brief Converts degrees to radians.
  ///
  /// \return Radians value.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Radians (
    GLfloat const & fDegrees
  );

  ////////////////////////////////////////////////////////////
  /// \brief Converts radians to degrees.
  ///
  /// \return Degrees value.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Degrees (
    GLfloat const & fRadians
  );

  ////////////////////////////////////////////////////////////
  /// \brief The standard trigonometric sine function.
  /// The values returned by this function will range from [-1, 1].
  ///
  /// \return Sine value.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Sin (
    GLfloat const & fAngle
  );

  ////////////////////////////////////////////////////////////
  /// \brief The standard trigonometric cosine function.
  /// The values returned by this function will range from [-1, 1].
  ///
  /// \return Cosine value.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Cos (
    GLfloat const & fAngle
  );

  ////////////////////////////////////////////////////////////
  /// \brief The standard trigonometric tangent function.
  ///
  /// \return Tangent value.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Tan (
    GLfloat const & fAngle
  );

  ////////////////////////////////////////////////////////////
  /// \brief Arc sine. Returns an angle whose sine is x.
  /// The range of values returned by this function is [-PI/2, PI/2].
  /// Results are undefined if |x| > 1.
  ///
  /// \return Arc sine value.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Asin (
    GLfloat const & fX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Arc cosine. Returns an angle whose sine is x.
  /// The range of values returned by this function is [0, PI].
  /// Results are undefined if |x| > 1.
  ///
  /// \return Arc cosine value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Acos (
    GLfloat const & fX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Arc tangent. Returns an angle whose tangent is y/x.
  /// The signs of x and y are used to determine what
  /// quadrant the angle is in. The range of values returned
  /// by this function is [-PI, PI]. Results are undefined
  /// if x and y are both 0.
  ///
  /// \return Arc tangent value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Atan (
    GLfloat const & fY,
    GLfloat const & fX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Arc tangent. Returns an angle whose tangent is y_over_x.
  /// The range of values returned by this function is [-PI/2, PI/2].
  ///
  /// \return Arc tangent value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Atan (
    GLfloat const & fYOverX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Returns the hyperbolic sine function, (exp(x) - exp(-x)) / 2.
  ///
  /// \return Hyperbolic sine value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Sinh (
    GLfloat const & fAngle
  );

  ////////////////////////////////////////////////////////////
  /// \brief Returns the hyperbolic cosine function, (exp(x) + exp(-x)) / 2.
  ///
  /// \return Hyperbolic cosine value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Cosh (
    GLfloat const & fAngle
  );

  ////////////////////////////////////////////////////////////
  /// \brief Returns the hyperbolic tangent function, sinh(angle) / cosh(angle).
  ///
  /// \return Hyperbolic tangent value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Tanh (
    GLfloat const & fAngle
  );

  ////////////////////////////////////////////////////////////
  /// \brief Arc hyperbolic sine; returns the inverse of sinh.
  ///
  /// \return Arc hyperbolic sine.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Asinh (
    GLfloat const & fX
  );

  ////////////////////////////////////////////////////////////
  /// \brief Arc hyperbolic cosine; returns the non-negative inverse
  /// of cosh. Results are undefined if x < 1.
  ///
  /// \return Arc hyperbolic cosine.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Acosh (
    GLfloat const & fX
  );

	/*  */
  ////////////////////////////////////////////////////////////
  /// \brief Arc hyperbolic tangent; returns the inverse of tanh.
  /// Results are undefined if abs(x) >= 1.
  ///
  /// \return Arc hyperbolic tangent value.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Atanh (
    GLfloat const & fX
  );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Trigonometric
