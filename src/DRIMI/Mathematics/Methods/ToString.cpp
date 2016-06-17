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

#include <DRIMI/Mathematics/Config.hpp>
#include <iomanip>    // std::setprecision

namespace drimi {

  ////////////////////////////////////////////////////////////
  std::string ToString ( const GLuint& uiValue ) {
    std::ostringstream oss;
    oss << uiValue;
    return oss.str ();
	}

  ////////////////////////////////////////////////////////////
  std::string ToString ( const GLfloat& fValue ) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision (3) << fValue;
    if (fValue >= 0.f)
      return " "+oss.str ();
    return oss.str ();
	}

} // namespace drimi
