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
	Vec2f::Vec2f ( void ) {
		x = 0.f;
		y = 0.f;
	}

  ////////////////////////////////////////////////////////////
	Vec2f::Vec2f ( Vec2f const & v2fV ) {
	  x = v2fV.x;
		y = v2fV.y;
	}

  ////////////////////////////////////////////////////////////
	Vec2f::Vec2f ( GLfloat const & fS ) {
		x = fS;
		y = fS;
	}

  ////////////////////////////////////////////////////////////
	Vec2f::Vec2f (
		GLfloat const & fS0,
		GLfloat const & fS1
	) {
		x = fS0;
		y = fS1;
	}

  ////////////////////////////////////////////////////////////
  Vec2f::~Vec2f ( void ) {
  }

  ////////////////////////////////////////////////////////////
  Vec2f::Vec2f ( Vec3f const & v3fV ) {
    x = v3fV.x;
    y = v3fV.y;
  }

  ////////////////////////////////////////////////////////////
  // Accessor methods
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	GLfloat & Vec2f::operator[] ( std::size_t i ) {
		assert(i < 2);
		if (i==0) return x;
		else return y;
	}

  ////////////////////////////////////////////////////////////
	GLfloat const & Vec2f::operator[] ( std::size_t i ) const {
		assert(i < 2);
		if (i==0) return x;
		else return y;
	}

  ////////////////////////////////////////////////////////////
  // Unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec2f& Vec2f::operator= ( Vec2f const & v2fV ) {
		x = v2fV.x;
		y = v2fV.y;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f& Vec2f::operator+= ( GLfloat const & fS ) {
		x += fS;
		y += fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f& Vec2f::operator+= ( Vec2f const & v2fV ) {
		x += v2fV.x;
		y += v2fV.y;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator-= ( GLfloat const & fS ) {
		x -= fS;
		y -= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f& Vec2f::operator-= ( Vec2f const & v2fV ) {
		x -= v2fV.x;
		y -= v2fV.y;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator*= ( GLfloat const & fS ) {
		x *= fS;
		y *= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator*= ( Vec2f const & v2fV ) {
		return (*this = *this * v2fV);
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator/= ( GLfloat const & fS ) {
		x /= fS;
		y /= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator/= ( Vec2f const & v2fV ) {
		return (*this = *this / v2fV);
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator++ ( void ) {
		++x;
		++y;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec2f & Vec2f::operator-- ( void ) {
		--x;
		--y;
		return *this;
	}

  ////////////////////////////////////////////////////////////
  // Binary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec2f operator+ ( Vec2f const & v2fV, GLfloat const & fS ) {
		return Vec2f (
			v2fV.x + fS,
			v2fV.y + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator+ ( GLfloat const & fS, Vec2f const & v2fV ) {
		return Vec2f (
			v2fV.x + fS,
			v2fV.y + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator+ ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
		return Vec2f (
			v2fV1.x + v2fV2.x,
			v2fV1.y + v2fV2.y );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator- ( Vec2f const & v2fV, GLfloat const & fS ) {
		return Vec2f (
			v2fV.x - fS,
			v2fV.y - fS );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator- ( GLfloat const & fS, Vec2f const & v2fV ) {
		return Vec2f (
			fS - v2fV.x,
			fS - v2fV.y );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator- ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
		return Vec2f (
			v2fV1.x - v2fV2.x,
			v2fV1.y - v2fV2.y );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator* ( Vec2f const & v2fV, GLfloat const & fS ) {
		return Vec2f (
			v2fV.x * fS,
			v2fV.y * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator* ( GLfloat const & fS, Vec2f const & v2fV ) {
		return Vec2f (
			v2fV.x * fS,
			v2fV.y * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator* ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
		return Vec2f (
			v2fV1.x * v2fV2.x,
			v2fV1.y * v2fV2.y );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator/ ( Vec2f const & v2fV, GLfloat const & fS ) {
		return Vec2f (
			v2fV.x / fS,
			v2fV.y / fS );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator/ ( GLfloat const & fS, Vec2f const & v2fV ) {
		return Vec2f (
			fS / v2fV.x,
			fS / v2fV.y );
	}

  ////////////////////////////////////////////////////////////
	Vec2f operator/ ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
		return Vec2f (
			v2fV1.x / v2fV2.x,
			v2fV1.y / v2fV2.y );
	}

  ////////////////////////////////////////////////////////////
  // Constant unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec2f const operator- ( Vec2f const & v2fV ) {
		return Vec2f (
			-v2fV.x,
			-v2fV.y );
	}

  ////////////////////////////////////////////////////////////
	Vec2f const operator++ ( Vec2f const & v2fV, int ) {
		return Vec2f (
			v2fV.x + 1.f,
			v2fV.y + 1.f );
	}

  ////////////////////////////////////////////////////////////
	Vec2f const operator-- ( Vec2f const & v2fV, int ) {
		return Vec2f (
			v2fV.x - 1.f,
			v2fV.y - 1.f );
	}

  ////////////////////////////////////////////////////////////
  // Boolean operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
  GLboolean operator== ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
		return (v2fV1.x == v2fV2.x) && (v2fV1.y == v2fV2.y);
	}

  ////////////////////////////////////////////////////////////
  GLboolean operator!= ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) {
		return (v2fV1.x != v2fV2.x) || (v2fV1.y != v2fV2.y);
	}

} // namespace drimi
