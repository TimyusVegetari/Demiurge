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
  GLfloat Length ( GLfloat const & fX ) {
    GLfloat fSqr = fX * fX;
		return drimi::Sqrt (fSqr);
  }

  GLfloat Length ( Vec2f const & v2fX ) {
    GLfloat fSqr = v2fX.x * v2fX.x + v2fX.y * v2fX.y;
		return drimi::Sqrt (fSqr);
  }

  GLfloat Length ( Vec3f const & v3fX ) {
    GLfloat fSqr = v3fX.x * v3fX.x + v3fX.y * v3fX.y + v3fX.z * v3fX.z;
		return drimi::Sqrt (fSqr);
  }

  GLfloat Length ( Vec4f const & v4fX ) {
    GLfloat fSqr = v4fX.x * v4fX.x + v4fX.y * v4fX.y + v4fX.z * v4fX.z + v4fX.w * v4fX.w;
		return drimi::Sqrt (fSqr);
  }

  ////////////////////////////////////////////////////////////
  GLfloat Distance ( GLfloat const & fP0, GLfloat const & fP1 ) {
    return Length (fP1 - fP0);
  }

  GLfloat Distance ( Vec2f const & v2fP0, Vec2f const & v2fP1 ) {
    return Length (v2fP1 - v2fP0);
  }

  GLfloat Distance ( Vec3f const & v3fP0, Vec3f const & v3fP1 ) {
    return Length (v3fP1 - v3fP0);
  }

  GLfloat Distance ( Vec4f const & v4fP0, Vec4f const & v4fP1 ) {
    return Length (v4fP1 - v4fP0);
  }

  ////////////////////////////////////////////////////////////
  GLfloat Dot ( GLfloat const & fX, GLfloat const & fY ) {
    return fX * fY;
  }

	GLfloat Dot ( Vec2f const & v2fX, Vec2f const & v2fY ) {
		return v2fX.x * v2fY.x + v2fX.y * v2fY.y;
	}

	GLfloat Dot ( Vec3f const & v3fX, Vec3f const & v3fY ) {
		return v3fX.x * v3fY.x + v3fX.y * v3fY.y + v3fX.z * v3fY.z;
	}

	GLfloat Dot ( Vec4f const & v4fX, Vec4f const & v4fY ) {
		return v4fX.x * v4fY.x + v4fX.y * v4fY.y + v4fX.z * v4fY.z + v4fX.w * v4fY.w;
	}

  ////////////////////////////////////////////////////////////
  Vec3f Cross ( Vec3f const & v3fX, Vec3f const & v3fY ) {
    return Vec3f (
			v3fX.y * v3fY.z - v3fY.y * v3fX.z,
			v3fX.z * v3fY.x - v3fY.z * v3fX.x,
			v3fX.x * v3fY.y - v3fY.x * v3fX.y);
  }

  ////////////////////////////////////////////////////////////
  GLfloat Normalize ( GLfloat const & fX ) {
    return fX < 0.f ? -1.f : 1.f;
  }

  Vec2f Normalize ( Vec2f const & v2fX ) {
    GLfloat fSqr = v2fX.x * v2fX.x + v2fX.y * v2fX.y;
		return v2fX * drimi::InverseSqrt (fSqr);
  }

  Vec3f Normalize ( Vec3f const & v3fX ) {
    GLfloat fSqr = v3fX.x * v3fX.x + v3fX.y * v3fX.y + v3fX.z * v3fX.z;
		return v3fX * drimi::InverseSqrt (fSqr);
  }

  Vec4f Normalize ( Vec4f const & v4fX ) {
    GLfloat fSqr = v4fX.x * v4fX.x + v4fX.y * v4fX.y + v4fX.z * v4fX.z + v4fX.w * v4fX.w;
		return v4fX * drimi::InverseSqrt (fSqr);
  }

  ////////////////////////////////////////////////////////////
  GLfloat Faceforward ( GLfloat const & fN, GLfloat const & fI, GLfloat const & fNref ) {
    return Dot (fNref, fI) < 0.f ? fN : -fN;
  }

  ////////////////////////////////////////////////////////////
	GLfloat Reflect ( GLfloat const & fI, GLfloat const & fN ) {
    return fI - fN * Dot (fN, fI) * 2.f;
  }

  ////////////////////////////////////////////////////////////
	GLfloat Refract ( GLfloat const & fI, GLfloat const & fN, GLfloat const & fEta ) {
    GLfloat fDotValue = Dot (fN, fI);
		GLfloat fK = 1.f - fEta * fEta * (1.f - fDotValue * fDotValue);
		if (fK < 0.f)
			return 0.f;
		else
			return fEta * fI - (fEta * fDotValue + drimi::Sqrt (fK)) * fN;
  }

} // namespace drimi
