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
	Vec3f::Vec3f ( void ) {
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

  ////////////////////////////////////////////////////////////
	Vec3f::Vec3f ( Vec3f const & v3fV ) {
	  x = v3fV.x;
		y = v3fV.y;
		z = v3fV.z;
	}

  ////////////////////////////////////////////////////////////
	Vec3f::Vec3f ( GLfloat const & fS ) {
		x = fS;
		y = fS;
		z = fS;
	}

  ////////////////////////////////////////////////////////////
	Vec3f::Vec3f (
		GLfloat const & fS0,
		GLfloat const & fS1,
		GLfloat const & fS2
	) {
		x = fS0;
		y = fS1;
		z = fS2;
	}

  ////////////////////////////////////////////////////////////
  Vec3f::~Vec3f ( void ) {
  }

  ////////////////////////////////////////////////////////////
  Vec3f::Vec3f ( Vec2f const & v2fV, GLfloat const & fS ) {
    x = v2fV.x;
    y = v2fV.y;
    z = fS;
  }

  ////////////////////////////////////////////////////////////
  Vec3f::Vec3f ( GLfloat const & fS, Vec2f const & v2fV ) {
    x = fS;
    y = v2fV.x;
    z = v2fV.y;
  }

  ////////////////////////////////////////////////////////////
  Vec3f::Vec3f ( Vec4f const & v4fV ) {
    x = v4fV.x;
    y = v4fV.y;
    z = v4fV.z;
  }

  ////////////////////////////////////////////////////////////
  // Accessor methods
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	GLfloat & Vec3f::operator[] ( std::size_t i ) {
		assert(i < 3);
		if (i==0) return x;
		else if (i==1) return y;
		else return z;
	}

  ////////////////////////////////////////////////////////////
	GLfloat const & Vec3f::operator[] ( std::size_t i ) const {
		assert(i < 3);
		if (i==0) return x;
		else if (i==1) return y;
		else return z;
	}

  ////////////////////////////////////////////////////////////
  // Unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec3f& Vec3f::operator= ( Vec3f const & v3fV ) {
		x = v3fV.x;
		y = v3fV.y;
		z = v3fV.z;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f& Vec3f::operator+= ( GLfloat const & fS ) {
		x += fS;
		y += fS;
		z += fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f& Vec3f::operator+= ( Vec3f const & v3fV ) {
		x += v3fV.x;
		y += v3fV.y;
		z += v3fV.z;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator-= ( GLfloat const & fS ) {
		x -= fS;
		y -= fS;
		z -= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f& Vec3f::operator-= ( Vec3f const & v3fV ) {
		x -= v3fV.x;
		y -= v3fV.y;
		z -= v3fV.z;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator*= ( GLfloat const & fS ) {
		x *= fS;
		y *= fS;
		z *= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator*= ( Vec3f const & v3fV ) {
		return (*this = *this * v3fV);
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator/= ( GLfloat const & fS ) {
		x /= fS;
		y /= fS;
		z /= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator/= ( Vec3f const & v3fV ) {
		return (*this = *this / v3fV);
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator++ ( void ) {
		++x;
		++y;
		++z;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec3f & Vec3f::operator-- ( void ) {
		--x;
		--y;
		--z;
		return *this;
	}

  ////////////////////////////////////////////////////////////
  // Binary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec3f operator+ ( Vec3f const & v3fV, GLfloat const & fS ) {
		return Vec3f (
			v3fV.x + fS,
			v3fV.y + fS,
			v3fV.z + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator+ ( GLfloat const & fS, Vec3f const & v3fV ) {
		return Vec3f (
			v3fV.x + fS,
			v3fV.y + fS,
			v3fV.z + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator+ ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) {
		return Vec3f (
			v3fV1.x + v3fV2.x,
			v3fV1.y + v3fV2.y,
			v3fV1.z + v3fV2.z );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator- ( Vec3f const & v3fV, GLfloat const & fS ) {
		return Vec3f (
			v3fV.x - fS,
			v3fV.y - fS,
			v3fV.z - fS );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator- ( GLfloat const & fS, Vec3f const & v3fV ) {
		return Vec3f (
			fS - v3fV.x,
			fS - v3fV.y,
			fS - v3fV.z );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator- ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) {
		return Vec3f (
			v3fV1.x - v3fV2.x,
			v3fV1.y - v3fV2.y,
			v3fV1.z - v3fV2.z );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator* ( Vec3f const & v3fV, GLfloat const & fS ) {
		return Vec3f (
			v3fV.x * fS,
			v3fV.y * fS,
			v3fV.z * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator* ( GLfloat const & fS, Vec3f const & v3fV ) {
		return Vec3f (
			v3fV.x * fS,
			v3fV.y * fS,
			v3fV.z * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator* ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) {
		return Vec3f (
			v3fV1.x * v3fV2.x,
			v3fV1.y * v3fV2.y,
			v3fV1.z * v3fV2.z );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator/ ( Vec3f const & v3fV, GLfloat const & fS ) {
		return Vec3f (
			v3fV.x / fS,
			v3fV.y / fS,
			v3fV.z / fS );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator/ ( GLfloat const & fS, Vec3f const & v3fV ) {
		return Vec3f (
			fS / v3fV.x,
			fS / v3fV.y,
			fS / v3fV.z );
	}

  ////////////////////////////////////////////////////////////
	Vec3f operator/ ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) {
		return Vec3f (
			v3fV1.x / v3fV2.x,
			v3fV1.y / v3fV2.y,
			v3fV1.z / v3fV2.z );
	}

  ////////////////////////////////////////////////////////////
  // Constant unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec3f const operator- ( Vec3f const & v3fV ) {
		return Vec3f (
			-v3fV.x,
			-v3fV.y,
			-v3fV.z );
	}

  ////////////////////////////////////////////////////////////
	Vec3f const operator++ ( Vec3f const & v3fV, int ) {
		return Vec3f (
			v3fV.x + 1.f,
			v3fV.y + 1.f,
			v3fV.z + 1.f );
	}

  ////////////////////////////////////////////////////////////
	Vec3f const operator-- ( Vec3f const & v3fV, int ) {
		return Vec3f (
			v3fV.x - 1.f,
			v3fV.y - 1.f,
			v3fV.z - 1.f );
	}

  ////////////////////////////////////////////////////////////
  // Boolean operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
  GLboolean operator== ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) {
		return (v3fV1.x == v3fV2.x) && (v3fV1.y == v3fV2.y) && (v3fV1.z == v3fV2.z);
	}

  ////////////////////////////////////////////////////////////
  GLboolean operator!= ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) {
		return (v3fV1.x != v3fV2.x) || (v3fV1.y != v3fV2.y) || (v3fV1.z != v3fV2.z);
	}

} // namespace drimi
