////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Mathematics.
// Copyright (C) 2014-2015 Acroute Anthony (ant110283@hotmail.fr)
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
  // Constructor(s)/Destructor
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec4f::Vec4f ( void ) {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

  ////////////////////////////////////////////////////////////
	Vec4f::Vec4f ( Vec4f const & v4fV ) {
	  x = v4fV.x;
		y = v4fV.y;
		z = v4fV.z;
		w = v4fV.w;
	}

  ////////////////////////////////////////////////////////////
	Vec4f::Vec4f ( GLfloat const & fS ) {
		x = fS;
		y = fS;
		z = fS;
		w = fS;
	}

  ////////////////////////////////////////////////////////////
	Vec4f::Vec4f (
		GLfloat const & fS0,
		GLfloat const & fS1,
		GLfloat const & fS2,
		GLfloat const & fS3
	) {
		x = fS0;
		y = fS1;
		z = fS2;
		w = fS3;
	}

  ////////////////////////////////////////////////////////////
  Vec4f::~Vec4f ( void ) {
  }

  ////////////////////////////////////////////////////////////
  Vec4f::Vec4f ( Vec2f const & v2fV, GLfloat const & fS1, GLfloat const & fS2 ) {
    x = v2fV.x;
    y = v2fV.y;
    z = fS1;
    w = fS2;
  }

  ////////////////////////////////////////////////////////////
  Vec4f::Vec4f ( GLfloat const & fS1, Vec2f const & v2fV, GLfloat const & fS2 ) {
    x = fS1;
    y = v2fV.x;
    z = v2fV.y;
    w = fS2;
  }

  ////////////////////////////////////////////////////////////
  Vec4f::Vec4f ( GLfloat const & fS1, GLfloat const & fS2, Vec2f const & v2fV ) {
    x = fS1;
    y = fS2;
    z = v2fV.x;
    w = v2fV.y;
  }

  ////////////////////////////////////////////////////////////
  Vec4f::Vec4f ( Vec3f const & v3fV, GLfloat const & fS ) {
    x = v3fV.x;
    y = v3fV.y;
    z = v3fV.z;
    w = fS;
  }

  ////////////////////////////////////////////////////////////
  Vec4f::Vec4f ( GLfloat const & fS, Vec3f const & v3fV ) {
    x = fS;
    y = v3fV.x;
    z = v3fV.y;
    w = v3fV.z;
  }

  ////////////////////////////////////////////////////////////
  Vec4f::Vec4f ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
    x = v2fV1.x;
    y = v2fV1.y;
    z = v2fV2.x;
    w = v2fV2.y;
  }

  ////////////////////////////////////////////////////////////
  // Accessor methods
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	GLfloat & Vec4f::operator[] ( std::size_t i ) {
		assert(i < 4);
		if (i==0) return x;
		else if (i==1) return y;
		else if (i==2) return z;
		else return w;
	}

  ////////////////////////////////////////////////////////////
	GLfloat const & Vec4f::operator[] ( std::size_t i ) const {
		assert(i < 4);
		if (i==0) return x;
		else if (i==1) return y;
		else if (i==2) return z;
		else return w;
	}

  ////////////////////////////////////////////////////////////
  // Unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec4f& Vec4f::operator= ( Vec4f const & v4fV ) {
		x = v4fV.x;
		y = v4fV.y;
		z = v4fV.z;
		w = v4fV.w;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f& Vec4f::operator+= ( GLfloat const & fS ) {
		x += fS;
		y += fS;
		z += fS;
		w += fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f& Vec4f::operator+= ( Vec4f const & v4fV ) {
		x += v4fV.x;
		y += v4fV.y;
		z += v4fV.z;
		w += v4fV.w;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator-= ( GLfloat const & fS ) {
		x -= fS;
		y -= fS;
		z -= fS;
		w -= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f& Vec4f::operator-= ( Vec4f const & v4fV ) {
		x -= v4fV.x;
		y -= v4fV.y;
		z -= v4fV.z;
		w -= v4fV.w;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator*= ( GLfloat const & fS ) {
		x *= fS;
		y *= fS;
		z *= fS;
		w *= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator*= ( Vec4f const & v4fV ) {
		return (*this = *this * v4fV);
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator/= ( GLfloat const & fS ) {
		x /= fS;
		y /= fS;
		z /= fS;
		w /= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator/= ( Vec4f const & v4fV ) {
		return (*this = *this / v4fV);
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator++ ( void ) {
		++x;
		++y;
		++z;
		++w;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec4f & Vec4f::operator-- ( void ) {
		--x;
		--y;
		--z;
		--w;
		return *this;
	}

  ////////////////////////////////////////////////////////////
  // Binary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec4f operator+ ( Vec4f const & v4fV, GLfloat const & fS ) {
		return Vec4f (
			v4fV.x + fS,
			v4fV.y + fS,
			v4fV.z + fS,
			v4fV.w + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator+ ( GLfloat const & fS, Vec4f const & v4fV ) {
		return Vec4f (
			v4fV.x + fS,
			v4fV.y + fS,
			v4fV.z + fS,
			v4fV.w + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator+ ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) {
		return Vec4f (
			v4fV1.x + v4fV2.x,
			v4fV1.y + v4fV2.y,
			v4fV1.z + v4fV2.z,
			v4fV1.w + v4fV2.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator- ( Vec4f const & v4fV, GLfloat const & fS ) {
		return Vec4f (
			v4fV.x - fS,
			v4fV.y - fS,
			v4fV.z - fS,
			v4fV.w - fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator- ( GLfloat const & fS, Vec4f const & v4fV ) {
		return Vec4f (
			fS - v4fV.x,
			fS - v4fV.y,
			fS - v4fV.z,
			fS - v4fV.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator- ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) {
		return Vec4f (
			v4fV1.x - v4fV2.x,
			v4fV1.y - v4fV2.y,
			v4fV1.z - v4fV2.z,
			v4fV1.w - v4fV2.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator* ( Vec4f const & v4fV, GLfloat const & fS ) {
		return Vec4f (
			v4fV.x * fS,
			v4fV.y * fS,
			v4fV.z * fS,
			v4fV.w * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator* ( GLfloat const & fS, Vec4f const & v4fV ) {
		return Vec4f (
			v4fV.x * fS,
			v4fV.y * fS,
			v4fV.z * fS,
			v4fV.w * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator* ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) {
		return Vec4f (
			v4fV1.x * v4fV2.x,
			v4fV1.y * v4fV2.y,
			v4fV1.z * v4fV2.z,
			v4fV1.w * v4fV2.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator/ ( Vec4f const & v4fV, GLfloat const & fS ) {
		return Vec4f (
			v4fV.x / fS,
			v4fV.y / fS,
			v4fV.z / fS,
			v4fV.w / fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator/ ( GLfloat const & fS, Vec4f const & v4fV ) {
		return Vec4f (
			fS / v4fV.x,
			fS / v4fV.y,
			fS / v4fV.z,
			fS / v4fV.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator/ ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) {
		return Vec4f (
			v4fV1.x / v4fV2.x,
			v4fV1.y / v4fV2.y,
			v4fV1.z / v4fV2.z,
			v4fV1.w / v4fV2.w );
	}

  ////////////////////////////////////////////////////////////
  // Constant unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec4f const operator- ( Vec4f const & v4fV ) {
		return Vec4f (
			-v4fV.x,
			-v4fV.y,
			-v4fV.z,
			-v4fV.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f const operator++ ( Vec4f const & v4fV, int ) {
		return Vec4f (
			v4fV.x + 1.f,
			v4fV.y + 1.f,
			v4fV.z + 1.f,
			v4fV.w + 1.f );
	}

  ////////////////////////////////////////////////////////////
	Vec4f const operator-- ( Vec4f const & v4fV, int ) {
		return Vec4f (
			v4fV.x - 1.f,
			v4fV.y - 1.f,
			v4fV.z - 1.f,
			v4fV.w - 1.f );
	}

  ////////////////////////////////////////////////////////////
  // Boolean operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
  GLboolean operator== ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) {
		return (v4fV1.x == v4fV2.x) && (v4fV1.y == v4fV2.y) && (v4fV1.z == v4fV2.z) && (v4fV1.w == v4fV2.w);
	}

  ////////////////////////////////////////////////////////////
  GLboolean operator!= ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) {
		return (v4fV1.x != v4fV2.x) || (v4fV1.y != v4fV2.y) || (v4fV1.z != v4fV2.z) || (v4fV1.w != v4fV2.w);
	}

} // namespace drimi
