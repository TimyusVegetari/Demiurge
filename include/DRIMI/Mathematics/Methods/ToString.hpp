////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Mathematics.
// Copyright (C) 2015-2016 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file ToString.hpp
 * \brief Methods to convert numerics to strings.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015-2016
 *
 */

#ifndef DRIMI_MATHEMATICS_ToString
#define DRIMI_MATHEMATICS_ToString

#if defined(DRIMI_MATHEMATICS_MESSAGES)
# pragma message("DRIMI: DRIMI_MATHEMATICS_ToString extension included")
#endif

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <sstream>

namespace drimi {

  ////////////////////////////////////////////////////////////
  /// \brief Converts unsigned int to string.
  ///
  /// \return String of the numeric value.
  ///
  ////////////////////////////////////////////////////////////
  std::string ToString ( const GLuint& uiValue );

  ////////////////////////////////////////////////////////////
  /// \brief Converts float to string.
  ///
  /// \return String of the numeric value.
  ///
  ////////////////////////////////////////////////////////////
  std::string ToString ( const GLfloat& fValue );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_ToString
