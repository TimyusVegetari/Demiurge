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

#include <DRIMI/Mathematics/Config.hpp>

namespace drimi {

  ////////////////////////////////////////////////////////////
  GLfloat Pow ( GLfloat const & fBase, GLfloat const & fExponent ) {
    return std::pow (fBase, fExponent);
  }

	DRIMI_VECTORIZE_VEC_VEC(Pow)

  ////////////////////////////////////////////////////////////
  GLfloat Exp ( GLfloat const & fX ) {
		return std::exp (fX);
  }

	DRIMI_VECTORIZE_VEC(Exp)

  ////////////////////////////////////////////////////////////
  GLfloat Log ( GLfloat const & fX ) {
    assert (fX > 0.f);
		return std::log (fX);
  }

	DRIMI_VECTORIZE_VEC(Log)

  ////////////////////////////////////////////////////////////
  GLfloat Exp2 ( GLfloat const & fX ) {
		return std::exp (0.693147f * fX);
  }

	DRIMI_VECTORIZE_VEC(Exp2)

  ////////////////////////////////////////////////////////////
  GLfloat Log2 ( GLfloat const & fX ) {
    assert (fX > 0.f);
    return std::log (fX) / 0.693147f;
  }

	DRIMI_VECTORIZE_VEC(Log2)

  ////////////////////////////////////////////////////////////
	GLfloat Sqrt ( GLfloat const & fX ) {
		return std::sqrt (fX);
  }

	DRIMI_VECTORIZE_VEC(Sqrt)

  ////////////////////////////////////////////////////////////
	GLfloat InverseSqrt ( GLfloat const & fX ) {
    assert (fX > 0.f);
		return 1.f / std::sqrt (fX);
  }

	DRIMI_VECTORIZE_VEC(InverseSqrt)

} // namespace drimi
