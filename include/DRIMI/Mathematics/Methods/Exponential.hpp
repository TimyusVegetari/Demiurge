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
 * \file Exponential.hpp
 * \brief Methods for exponential, logarithm, power, etc...
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014
 *
 */

#ifndef DRIMI_MATHEMATICS_Exponential
#define DRIMI_MATHEMATICS_Exponential

#if defined(DRIMI_MATHEMATICS_MESSAGES)
# pragma message("DRIMI: DRIMI_MATHEMATICS_Exponential extension included")
#endif

namespace drimi {

  ////////////////////////////////////////////////////////////
  /// \brief Power function.
  ///
  /// \return Base raised to the power exponent.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Pow ( GLfloat const & fBase, GLfloat const & fExponent );

  ////////////////////////////////////////////////////////////
  /// \brief Exponential function.
  ///
  /// \return The natural exponentiation of fX, i.e., e^x.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Exp ( GLfloat const & fX );

  ////////////////////////////////////////////////////////////
  /// \brief Logarithm function.
  ///        Returns the value y which satisfies the equation x = e^y.
  ///        Results are undefined if x <= 0.
  ///
  /// \return The natural logarithm of fX, i.e.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Log ( GLfloat const & fX );

  ////////////////////////////////////////////////////////////
  /// \brief Exponential two function.
  ///
  /// \return Two raised to the fX power.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Exp2 ( GLfloat const & fX );

  ////////////////////////////////////////////////////////////
  /// \brief Logarithm two function.
  ///        Returns the value y, which satisfies
  ///        the equation x = 2 ^ y.
  ///
  /// \return The base 2 log of fX, i.e.
  ///
  ////////////////////////////////////////////////////////////
  GLfloat Log2 ( GLfloat const & fX );

  ////////////////////////////////////////////////////////////
  /// \brief Square root function.
  ///
  /// \return The positive square root of fX.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat Sqrt ( GLfloat const & fX );

  ////////////////////////////////////////////////////////////
  /// \brief Inverse Square root function.
  ///
  /// \return The reciprocal of the positive square root of fX.
  ///
  ////////////////////////////////////////////////////////////
	GLfloat InverseSqrt ( GLfloat const & fX );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Exponential
