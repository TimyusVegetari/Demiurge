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
	Vec6f::Vec6f ( void ) {
		x1 = 0.f;
		y1 = 0.f;
		z1 = 0.f;
		x2 = 0.f;
		y2 = 0.f;
		z2 = 0.f;
	}

  ////////////////////////////////////////////////////////////
	Vec6f::Vec6f ( Vec6f const & v6fV ) {
	  x1 = v6fV.x1;
		y1 = v6fV.y1;
		z1 = v6fV.z1;
	  x2 = v6fV.x2;
		y2 = v6fV.y2;
		z2 = v6fV.z2;
	}

  ////////////////////////////////////////////////////////////
	Vec6f::Vec6f ( GLfloat const & fS ) {
		x1 = fS;
		y1 = fS;
		z1 = fS;
		x2 = fS;
		y2 = fS;
		z2 = fS;
	}

  ////////////////////////////////////////////////////////////
	Vec6f::Vec6f (
		GLfloat const & fS0,
		GLfloat const & fS1,
		GLfloat const & fS2,
		GLfloat const & fS3,
		GLfloat const & fS4,
		GLfloat const & fS5
	) {
		x1 = fS0;
		y1 = fS1;
		z1 = fS2;
		x2 = fS3;
		y2 = fS4;
		z2 = fS5;
	}

  ////////////////////////////////////////////////////////////
  Vec6f::~Vec6f ( void ) {
  }

  ////////////////////////////////////////////////////////////
  // Accessor methods
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	GLfloat & Vec6f::operator[] ( std::size_t i ) {
		assert(i < 6);
		if (i==0) return x1;
		else if (i==1) return y1;
		else if (i==2) return z1;
		else if (i==3) return x2;
		else if (i==4) return y2;
		else return z2;
	}

  ////////////////////////////////////////////////////////////
	GLfloat const & Vec6f::operator[] ( std::size_t i ) const {
		assert(i < 6);
		if (i==0) return x1;
		else if (i==1) return y1;
		else if (i==2) return z1;
		else if (i==3) return x2;
		else if (i==4) return y2;
		else return z2;
	}

  ////////////////////////////////////////////////////////////
  // Unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec6f& Vec6f::operator= ( Vec6f const & v6fV ) {
	  x1 = v6fV.x1;
		y1 = v6fV.y1;
		z1 = v6fV.z1;
	  x2 = v6fV.x2;
		y2 = v6fV.y2;
		z2 = v6fV.z2;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f& Vec6f::operator+= ( GLfloat const & fS ) {
		x1 += fS;
		y1 += fS;
		z1 += fS;
		x2 += fS;
		y2 += fS;
		z2 += fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f& Vec6f::operator+= ( Vec6f const & v6fV ) {
		x1 += v6fV.x1;
		y1 += v6fV.y1;
		z1 += v6fV.z1;
		x2 += v6fV.x2;
		y2 += v6fV.y2;
		z2 += v6fV.z2;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator-= ( GLfloat const & fS ) {
		x1 -= fS;
		y1 -= fS;
		z1 -= fS;
		x2 -= fS;
		y2 -= fS;
		z2 -= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f& Vec6f::operator-= ( Vec6f const & v6fV ) {
		x1 -= v6fV.x1;
		y1 -= v6fV.y1;
		z1 -= v6fV.z1;
		x2 -= v6fV.x2;
		y2 -= v6fV.y2;
		z2 -= v6fV.z2;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator*= ( GLfloat const & fS ) {
		x1 *= fS;
		y1 *= fS;
		z1 *= fS;
		x2 *= fS;
		y2 *= fS;
		z2 *= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator*= ( Vec6f const & v6fV ) {
		return (*this = *this * v6fV);
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator/= ( GLfloat const & fS ) {
		x1 /= fS;
		y1 /= fS;
		z1 /= fS;
		x2 /= fS;
		y2 /= fS;
		z2 /= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator/= ( Vec6f const & v6fV ) {
		return (*this = *this / v6fV);
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator++ ( void ) {
		++x1;
		++y1;
		++z1;
		++x2;
		++y2;
		++z2;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Vec6f & Vec6f::operator-- ( void ) {
		--x1;
		--y1;
		--z1;
		--x2;
		--y2;
		--z2;
		return *this;
	}

  ////////////////////////////////////////////////////////////
  // Binary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec6f operator+ ( Vec6f const & v6fV, GLfloat const & fS ) {
		return Vec6f (
			v6fV.x1 + fS,
			v6fV.y1 + fS,
			v6fV.z1 + fS,
			v6fV.x2 + fS,
			v6fV.y2 + fS,
			v6fV.z2 + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator+ ( GLfloat const & fS, Vec6f const & v6fV ) {
		return Vec6f (
			v6fV.x1 + fS,
			v6fV.y1 + fS,
			v6fV.z1 + fS,
			v6fV.x2 + fS,
			v6fV.y2 + fS,
			v6fV.z2 + fS );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator+ ( Vec6f const & v6fV1, Vec6f const & v6fV2 ) {
		return Vec6f (
			v6fV1.x1 + v6fV2.x1,
			v6fV1.y1 + v6fV2.y1,
			v6fV1.z1 + v6fV2.z1,
			v6fV1.x2 + v6fV2.x2,
			v6fV1.y2 + v6fV2.y2,
			v6fV1.z2 + v6fV2.z2 );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator- ( Vec6f const & v6fV, GLfloat const & fS ) {
		return Vec6f (
			v6fV.x1 - fS,
			v6fV.y1 - fS,
			v6fV.z1 - fS,
			v6fV.x2 - fS,
			v6fV.y2 - fS,
			v6fV.z2 - fS );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator- ( GLfloat const & fS, Vec6f const & v6fV ) {
		return Vec6f (
			fS - v6fV.x1,
			fS - v6fV.y1,
			fS - v6fV.z1,
			fS - v6fV.x2,
			fS - v6fV.y2,
			fS - v6fV.z2 );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator- ( Vec6f const & v6fV1, Vec6f const & v6fV2 ) {
		return Vec6f (
			v6fV1.x1 - v6fV2.x1,
			v6fV1.y1 - v6fV2.y1,
			v6fV1.z1 - v6fV2.z1,
			v6fV1.x2 - v6fV2.x2,
			v6fV1.y2 - v6fV2.y2,
			v6fV1.z2 - v6fV2.z2 );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator* ( Vec6f const & v6fV, GLfloat const & fS ) {
		return Vec6f (
			v6fV.x1 * fS,
			v6fV.y1 * fS,
			v6fV.z1 * fS,
			v6fV.x2 * fS,
			v6fV.y2 * fS,
			v6fV.z2 * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator* ( GLfloat const & fS, Vec6f const & v6fV ) {
		return Vec6f (
			v6fV.x1 * fS,
			v6fV.y1 * fS,
			v6fV.z1 * fS,
			v6fV.x2 * fS,
			v6fV.y2 * fS,
			v6fV.z2 * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator* ( Vec6f const & v6fV1, Vec6f const & v6fV2 ) {
		return Vec6f (
			v6fV1.x1 * v6fV2.x1,
			v6fV1.y1 * v6fV2.y1,
			v6fV1.z1 * v6fV2.z1,
			v6fV1.x2 * v6fV2.x2,
			v6fV1.y2 * v6fV2.y2,
			v6fV1.z2 * v6fV2.z2 );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator/ ( Vec6f const & v6fV, GLfloat const & fS ) {
		return Vec6f (
			v6fV.x1 / fS,
			v6fV.y1 / fS,
			v6fV.z1 / fS,
			v6fV.x2 / fS,
			v6fV.y2 / fS,
			v6fV.z2 / fS );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator/ ( GLfloat const & fS, Vec6f const & v6fV ) {
		return Vec6f (
			fS / v6fV.x1,
			fS / v6fV.y1,
			fS / v6fV.z1,
			fS / v6fV.x2,
			fS / v6fV.y2,
			fS / v6fV.z2 );
	}

  ////////////////////////////////////////////////////////////
	Vec6f operator/ ( Vec6f const & v6fV1, Vec6f const & v6fV2 ) {
		return Vec6f (
			v6fV1.x1 / v6fV2.x1,
			v6fV1.y1 / v6fV2.y1,
			v6fV1.z1 / v6fV2.z1,
			v6fV1.x2 / v6fV2.x2,
			v6fV1.y2 / v6fV2.y2,
			v6fV1.z2 / v6fV2.z2 );
	}

  ////////////////////////////////////////////////////////////
  // Constant unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec6f const operator- ( Vec6f const & v6fV ) {
		return Vec6f (
			-v6fV.x1,
			-v6fV.y1,
			-v6fV.z1,
			-v6fV.x2,
			-v6fV.y2,
			-v6fV.z2 );
	}

  ////////////////////////////////////////////////////////////
	Vec6f const operator++ ( Vec6f const & v6fV, int ) {
		return Vec6f (
			v6fV.x1 + 1.f,
			v6fV.y1 + 1.f,
			v6fV.z1 + 1.f,
			v6fV.x2 + 1.f,
			v6fV.y2 + 1.f,
			v6fV.z2 + 1.f );
	}

  ////////////////////////////////////////////////////////////
	Vec6f const operator-- ( Vec6f const & v6fV, int ) {
		return Vec6f (
			v6fV.x1 - 1.f,
			v6fV.y1 - 1.f,
			v6fV.z1 - 1.f,
			v6fV.x2 - 1.f,
			v6fV.y2 - 1.f,
			v6fV.z2 - 1.f );
	}

  ////////////////////////////////////////////////////////////
  // Boolean operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
  GLboolean operator== ( Vec6f const & v6fV1, Vec6f const & v6fV2 ) {
		return (v6fV1.x1 == v6fV2.x1) && (v6fV1.y1 == v6fV2.y1) && (v6fV1.z1 == v6fV2.z1) && (v6fV1.x2 == v6fV2.x2) && (v6fV1.y2 == v6fV2.y2) && (v6fV1.z2 == v6fV2.z2);
	}

  ////////////////////////////////////////////////////////////
  GLboolean operator!= ( Vec6f const & v6fV1, Vec6f const & v6fV2 ) {
		return (v6fV1.x1 != v6fV2.x1) || (v6fV1.y1 != v6fV2.y1) || (v6fV1.z1 != v6fV2.z1) || (v6fV1.x2 != v6fV2.x2) || (v6fV1.y2 != v6fV2.y2) || (v6fV1.z2 != v6fV2.z2);
	}

} // namespace drimi
