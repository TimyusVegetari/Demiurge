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
	GLfloat Radians ( GLfloat const & fDegrees ) {
		return fDegrees * (DRIMI_fPI / 180.f);
	}

	DRIMI_VECTORIZE_VEC(Radians)

  ////////////////////////////////////////////////////////////
	GLfloat Degrees ( GLfloat const & fRadians ) {
		return fRadians * (180.f / DRIMI_fPI);
	}

	DRIMI_VECTORIZE_VEC(Degrees)

  ////////////////////////////////////////////////////////////
	GLfloat Sin ( GLfloat const & fAngle ) {
		return std::sin (fAngle);
	}

	DRIMI_VECTORIZE_VEC(Sin)

  ////////////////////////////////////////////////////////////
	GLfloat Cos ( GLfloat const & fAngle ) {
		return std::cos (fAngle);
	}

	DRIMI_VECTORIZE_VEC(Cos)

  ////////////////////////////////////////////////////////////
	GLfloat Tan ( GLfloat const & fAngle ) {
		return std::tan (fAngle);
	}

	DRIMI_VECTORIZE_VEC(Tan)

  ////////////////////////////////////////////////////////////
	GLfloat Asin ( GLfloat const & fX ) {
		return std::asin (fX);
	}

	DRIMI_VECTORIZE_VEC(Asin)

  ////////////////////////////////////////////////////////////
	GLfloat Acos ( GLfloat const & fX ) {
		return std::acos (fX);
	}

	DRIMI_VECTORIZE_VEC(Acos)

  ////////////////////////////////////////////////////////////
	GLfloat Atan2 ( GLfloat const & fY, GLfloat const & fX ) {
		return std::atan2 (fY, fX);
	}

	DRIMI_VECTORIZE_VEC_VEC(Atan2)

  ////////////////////////////////////////////////////////////
	GLfloat Atan ( GLfloat const & fX ) {
		return std::atan (fX);
	}

	DRIMI_VECTORIZE_VEC(Atan)

  ////////////////////////////////////////////////////////////
	GLfloat Sinh ( GLfloat const & fAngle ) {
		return std::sinh (fAngle);
	}

	DRIMI_VECTORIZE_VEC(Sinh)

  ////////////////////////////////////////////////////////////
	GLfloat Cosh ( GLfloat const & fAngle ) {
		return std::cosh (fAngle);
	}

	DRIMI_VECTORIZE_VEC(Cosh)

  ////////////////////////////////////////////////////////////
	GLfloat Tanh ( GLfloat const & fAngle ) {
		return std::tanh (fAngle);
	}

	DRIMI_VECTORIZE_VEC(Tanh)

  ////////////////////////////////////////////////////////////
	GLfloat Asinh ( GLfloat const & fX ) {
		return (fX < 0.f ? -1.f : (fX > 0.f ? 1.f : 0.f)) * drimi::Log (std::abs (fX) + drimi::Sqrt (1.f + fX * fX));
	}

	DRIMI_VECTORIZE_VEC(Asinh)

  ////////////////////////////////////////////////////////////
	GLfloat Acosh ( GLfloat const & fX ) {
		if (fX < 1.f)
			return 0.f;
		return drimi::Log (fX + drimi::Sqrt (fX * fX - 1.f));
	}

	DRIMI_VECTORIZE_VEC(Acosh)

  ////////////////////////////////////////////////////////////
	GLfloat Atanh ( GLfloat const & fX ) {
		if (std::abs (fX) >= 1.f)
			return 0.f;
		return 0.5f * drimi::Log ((1.f + fX) / (1.f - fX));
	}

	DRIMI_VECTORIZE_VEC(Atanh)

} // namespace drimi
