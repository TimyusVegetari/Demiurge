////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Mathematics.
// Copyright (C) 2011-2015 Acroute Anthony (ant110283@hotmail.fr)
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
	Mat4x4f::Mat4x4f ( void ) {
		GLfloat fZero  = 0.f;
		GLfloat fOne   = 1.f;
		m_v4fValue[0] = Vec4f ( fOne, fZero, fZero, fZero );
		m_v4fValue[1] = Vec4f ( fZero, fOne, fZero, fZero );
		m_v4fValue[2] = Vec4f ( fZero, fZero, fOne, fZero );
		m_v4fValue[3] = Vec4f ( fZero, fZero, fZero, fOne );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f::Mat4x4f ( Mat4x4f const & m4fM ) {
		m_v4fValue[0] = m4fM[0];
		m_v4fValue[1] = m4fM[1];
		m_v4fValue[2] = m4fM[2];
		m_v4fValue[3] = m4fM[3];
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f::Mat4x4f ( GLfloat const & fS ) {
		GLfloat const fZero = 0.f;
		m_v4fValue[0] = Vec4f ( fS, fZero, fZero, fZero );
		m_v4fValue[1] = Vec4f ( fZero, fS, fZero, fZero );
		m_v4fValue[2] = Vec4f ( fZero, fZero, fS, fZero );
		m_v4fValue[3] = Vec4f ( fZero, fZero, fZero, fS );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f::Mat4x4f (
		GLfloat const & fX0, GLfloat const & fY0, GLfloat const & fZ0, GLfloat const & fW0,
		GLfloat const & fX1, GLfloat const & fY1, GLfloat const & fZ1, GLfloat const & fW1,
		GLfloat const & fX2, GLfloat const & fY2, GLfloat const & fZ2, GLfloat const & fW2,
		GLfloat const & fX3, GLfloat const & fY3, GLfloat const & fZ3, GLfloat const & fW3
	) {
		m_v4fValue[0] = Vec4f ( fX0, fY0, fZ0, fW0 );
		m_v4fValue[1] = Vec4f ( fX1, fY1, fZ1, fW1 );
		m_v4fValue[2] = Vec4f ( fX2, fY2, fZ2, fW2 );
		m_v4fValue[3] = Vec4f ( fX3, fY3, fZ3, fW3 );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f::Mat4x4f ( Vec4f const & v4fV0, Vec4f const & v4fV1, Vec4f const & v4fV2, Vec4f const & v4fV3 ) {
		m_v4fValue[0] = v4fV0;
		m_v4fValue[1] = v4fV1;
		m_v4fValue[2] = v4fV2;
		m_v4fValue[3] = v4fV3;
	}

  ////////////////////////////////////////////////////////////
  Mat4x4f::~Mat4x4f ( void ) {
  }

  ////////////////////////////////////////////////////////////
  // Accessor methods
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Vec4f & Mat4x4f::operator[] ( std::size_t i ) {
		assert(i < 4);
		return m_v4fValue[i];
	}

  ////////////////////////////////////////////////////////////
	Vec4f const & Mat4x4f::operator[] ( std::size_t i ) const {
		assert(i < 4);
		return m_v4fValue[i];
	}

  ////////////////////////////////////////////////////////////
  // Unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Mat4x4f& Mat4x4f::operator= ( Mat4x4f const & m4fM ) {
		m_v4fValue[0] = m4fM[0];
		m_v4fValue[1] = m4fM[1];
		m_v4fValue[2] = m4fM[2];
		m_v4fValue[3] = m4fM[3];
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f& Mat4x4f::operator+= ( GLfloat const & fS ) {
		m_v4fValue[0] += fS;
		m_v4fValue[1] += fS;
		m_v4fValue[2] += fS;
		m_v4fValue[3] += fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f& Mat4x4f::operator+= ( Mat4x4f const & m4fM ) {
		m_v4fValue[0] += m4fM[0];
		m_v4fValue[1] += m4fM[1];
		m_v4fValue[2] += m4fM[2];
		m_v4fValue[3] += m4fM[3];
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator-= ( GLfloat const & fS ) {
		m_v4fValue[0] -= fS;
		m_v4fValue[1] -= fS;
		m_v4fValue[2] -= fS;
		m_v4fValue[3] -= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f& Mat4x4f::operator-= ( Mat4x4f const & m4fM ) {
		m_v4fValue[0] -= m4fM[0];
		m_v4fValue[1] -= m4fM[1];
		m_v4fValue[2] -= m4fM[2];
		m_v4fValue[3] -= m4fM[3];
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator*= ( GLfloat const & fS ) {
		m_v4fValue[0] *= fS;
		m_v4fValue[1] *= fS;
		m_v4fValue[2] *= fS;
		m_v4fValue[3] *= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator*= ( Mat4x4f const & m4fM ) {
		return (*this = *this * m4fM);
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator/= ( GLfloat const & fS ) {
		m_v4fValue[0] /= fS;
		m_v4fValue[1] /= fS;
		m_v4fValue[2] /= fS;
		m_v4fValue[3] /= fS;
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator/= ( Mat4x4f const & m4fM ) {
		return (*this = *this / m4fM);
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator++ ( void ) {
		++m_v4fValue[0];
		++m_v4fValue[1];
		++m_v4fValue[2];
		++m_v4fValue[3];
		return *this;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f & Mat4x4f::operator-- ( void ) {
		--m_v4fValue[0];
		--m_v4fValue[1];
		--m_v4fValue[2];
		--m_v4fValue[3];
		return *this;
	}

	////////////////////////////////////////////////////////////
	Mat4x4f Mat4x4f::Transpose ( void ) const {
		Mat4x4f m4fResult (0.f);

		m4fResult[0][0] = m_v4fValue[0][0];
		m4fResult[0][1] = m_v4fValue[1][0];
		m4fResult[0][2] = m_v4fValue[2][0];
		m4fResult[0][3] = m_v4fValue[3][0];

		m4fResult[1][0] = m_v4fValue[0][1];
		m4fResult[1][1] = m_v4fValue[1][1];
		m4fResult[1][2] = m_v4fValue[2][1];
		m4fResult[1][3] = m_v4fValue[3][1];

		m4fResult[2][0] = m_v4fValue[0][2];
		m4fResult[2][1] = m_v4fValue[1][2];
		m4fResult[2][2] = m_v4fValue[2][2];
		m4fResult[2][3] = m_v4fValue[3][2];

		m4fResult[3][0] = m_v4fValue[0][3];
		m4fResult[3][1] = m_v4fValue[1][3];
		m4fResult[3][2] = m_v4fValue[2][3];
		m4fResult[3][3] = m_v4fValue[3][3];

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Mat4x4f::Inverse ( void ) const {
		// Compute the determinants
		GLfloat fSubFactor00 = m_v4fValue[2][2] * m_v4fValue[3][3] - m_v4fValue[3][2] * m_v4fValue[2][3];
		GLfloat fSubFactor01 = m_v4fValue[2][1] * m_v4fValue[3][3] - m_v4fValue[3][1] * m_v4fValue[2][3];
		GLfloat fSubFactor02 = m_v4fValue[2][1] * m_v4fValue[3][2] - m_v4fValue[3][1] * m_v4fValue[2][2];
		GLfloat fSubFactor03 = m_v4fValue[2][0] * m_v4fValue[3][3] - m_v4fValue[3][0] * m_v4fValue[2][3];
		GLfloat fSubFactor04 = m_v4fValue[2][0] * m_v4fValue[3][2] - m_v4fValue[3][0] * m_v4fValue[2][2];
		GLfloat fSubFactor05 = m_v4fValue[2][0] * m_v4fValue[3][1] - m_v4fValue[3][0] * m_v4fValue[2][1];
		GLfloat fSubFactor06 = m_v4fValue[1][2] * m_v4fValue[3][3] - m_v4fValue[3][2] * m_v4fValue[1][3];
		GLfloat fSubFactor07 = m_v4fValue[1][1] * m_v4fValue[3][3] - m_v4fValue[3][1] * m_v4fValue[1][3];
		GLfloat fSubFactor08 = m_v4fValue[1][1] * m_v4fValue[3][2] - m_v4fValue[3][1] * m_v4fValue[1][2];
		GLfloat fSubFactor09 = m_v4fValue[1][0] * m_v4fValue[3][3] - m_v4fValue[3][0] * m_v4fValue[1][3];
		GLfloat fSubFactor10 = m_v4fValue[1][0] * m_v4fValue[3][2] - m_v4fValue[3][0] * m_v4fValue[1][2];
		GLfloat fSubFactor11 = m_v4fValue[1][1] * m_v4fValue[3][3] - m_v4fValue[3][1] * m_v4fValue[1][3];
		GLfloat fSubFactor12 = m_v4fValue[1][0] * m_v4fValue[3][1] - m_v4fValue[3][0] * m_v4fValue[1][1];
		GLfloat fSubFactor13 = m_v4fValue[1][2] * m_v4fValue[2][3] - m_v4fValue[2][2] * m_v4fValue[1][3];
		GLfloat fSubFactor14 = m_v4fValue[1][1] * m_v4fValue[2][3] - m_v4fValue[2][1] * m_v4fValue[1][3];
		GLfloat fSubFactor15 = m_v4fValue[1][1] * m_v4fValue[2][2] - m_v4fValue[2][1] * m_v4fValue[1][2];
		GLfloat fSubFactor16 = m_v4fValue[1][0] * m_v4fValue[2][3] - m_v4fValue[2][0] * m_v4fValue[1][3];
		GLfloat fSubFactor17 = m_v4fValue[1][0] * m_v4fValue[2][2] - m_v4fValue[2][0] * m_v4fValue[1][2];
		GLfloat fSubFactor18 = m_v4fValue[1][0] * m_v4fValue[2][1] - m_v4fValue[2][0] * m_v4fValue[1][1];

		Mat4x4f m4fInverse (
			+ m_v4fValue[1][1] * fSubFactor00 - m_v4fValue[1][2] * fSubFactor01 + m_v4fValue[1][3] * fSubFactor02,
			- m_v4fValue[1][0] * fSubFactor00 + m_v4fValue[1][2] * fSubFactor03 - m_v4fValue[1][3] * fSubFactor04,
			+ m_v4fValue[1][0] * fSubFactor01 - m_v4fValue[1][1] * fSubFactor03 + m_v4fValue[1][3] * fSubFactor05,
			- m_v4fValue[1][0] * fSubFactor02 + m_v4fValue[1][1] * fSubFactor04 - m_v4fValue[1][2] * fSubFactor05,

			- m_v4fValue[0][1] * fSubFactor00 + m_v4fValue[0][2] * fSubFactor01 - m_v4fValue[0][3] * fSubFactor02,
			+ m_v4fValue[0][0] * fSubFactor00 - m_v4fValue[0][2] * fSubFactor03 + m_v4fValue[0][3] * fSubFactor04,
			- m_v4fValue[0][0] * fSubFactor01 + m_v4fValue[0][1] * fSubFactor03 - m_v4fValue[0][3] * fSubFactor05,
			+ m_v4fValue[0][0] * fSubFactor02 - m_v4fValue[0][1] * fSubFactor04 + m_v4fValue[0][2] * fSubFactor05,

			+ m_v4fValue[0][1] * fSubFactor06 - m_v4fValue[0][2] * fSubFactor07 + m_v4fValue[0][3] * fSubFactor08,
			- m_v4fValue[0][0] * fSubFactor06 + m_v4fValue[0][2] * fSubFactor09 - m_v4fValue[0][3] * fSubFactor10,
			+ m_v4fValue[0][0] * fSubFactor11 - m_v4fValue[0][1] * fSubFactor09 + m_v4fValue[0][3] * fSubFactor12,
			- m_v4fValue[0][0] * fSubFactor08 + m_v4fValue[0][1] * fSubFactor10 - m_v4fValue[0][2] * fSubFactor12,

			- m_v4fValue[0][1] * fSubFactor13 + m_v4fValue[0][2] * fSubFactor14 - m_v4fValue[0][3] * fSubFactor15,
			+ m_v4fValue[0][0] * fSubFactor13 - m_v4fValue[0][2] * fSubFactor16 + m_v4fValue[0][3] * fSubFactor17,
			- m_v4fValue[0][0] * fSubFactor14 + m_v4fValue[0][1] * fSubFactor16 - m_v4fValue[0][3] * fSubFactor18,
			+ m_v4fValue[0][0] * fSubFactor15 - m_v4fValue[0][1] * fSubFactor17 + m_v4fValue[0][2] * fSubFactor18 );

		GLfloat fDeterminant = m_v4fValue[0][0] * m4fInverse[0][0] + m_v4fValue[0][1] * m4fInverse[1][0] + m_v4fValue[0][2] * m4fInverse[2][0] + m_v4fValue[0][3] * m4fInverse[3][0];

		m4fInverse /= fDeterminant;
		return m4fInverse;
	}

  ////////////////////////////////////////////////////////////
  // Binary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Mat4x4f operator+ ( Mat4x4f const & m4fM, GLfloat const & fS ) {
		return Mat4x4f (
			m4fM[0] + fS,
			m4fM[1] + fS,
			m4fM[2] + fS,
			m4fM[3] + fS );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator+ ( GLfloat const & fS, Mat4x4f const & m4fM ) {
		return Mat4x4f (
			m4fM[0] + fS,
			m4fM[1] + fS,
			m4fM[2] + fS,
			m4fM[3] + fS );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator+ ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 ) {
		return Mat4x4f (
			m4fM1[0] + m4fM2[0],
			m4fM1[1] + m4fM2[1],
			m4fM1[2] + m4fM2[2],
			m4fM1[3] + m4fM2[3] );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator- ( Mat4x4f const & m4fM, GLfloat const & fS ) {
		return Mat4x4f (
			m4fM[0] - fS,
			m4fM[1] - fS,
			m4fM[2] - fS,
			m4fM[3] - fS );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator- ( GLfloat const & fS, Mat4x4f const & m4fM ) {
		return Mat4x4f (
			fS - m4fM[0],
			fS - m4fM[1],
			fS - m4fM[2],
			fS - m4fM[3] );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator- ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 ) {
		return Mat4x4f (
			m4fM1[0] - m4fM2[0],
			m4fM1[1] - m4fM2[1],
			m4fM1[2] - m4fM2[2],
			m4fM1[3] - m4fM2[3] );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator* ( Mat4x4f const & m4fM, GLfloat const & fS ) {
		return Mat4x4f (
			m4fM[0] * fS,
			m4fM[1] * fS,
			m4fM[2] * fS,
			m4fM[3] * fS );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator* ( GLfloat const & fS, Mat4x4f const & m4fM ) {
		return Mat4x4f (
			m4fM[0] * fS,
			m4fM[1] * fS,
			m4fM[2] * fS,
			m4fM[3] * fS );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator* ( Mat4x4f const & m4fM, Vec4f const & v4fRow ) {
		return Vec4f (
			m4fM[0][0] * v4fRow.x + m4fM[1][0] * v4fRow.y + m4fM[2][0] * v4fRow.z + m4fM[3][0] * v4fRow.w,
			m4fM[0][1] * v4fRow.x + m4fM[1][1] * v4fRow.y + m4fM[2][1] * v4fRow.z + m4fM[3][1] * v4fRow.w,
			m4fM[0][2] * v4fRow.x + m4fM[1][2] * v4fRow.y + m4fM[2][2] * v4fRow.z + m4fM[3][2] * v4fRow.w,
			m4fM[0][3] * v4fRow.x + m4fM[1][3] * v4fRow.y + m4fM[2][3] * v4fRow.z + m4fM[3][3] * v4fRow.w );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator* ( Vec4f const & v4fCol, Mat4x4f const & m4fM ) {
		return Vec4f (
			m4fM[0][0] * v4fCol.x + m4fM[0][1] * v4fCol.y + m4fM[0][2] * v4fCol.z + m4fM[0][3] * v4fCol.w,
			m4fM[1][0] * v4fCol.x + m4fM[1][1] * v4fCol.y + m4fM[1][2] * v4fCol.z + m4fM[1][3] * v4fCol.w,
			m4fM[2][0] * v4fCol.x + m4fM[2][1] * v4fCol.y + m4fM[2][2] * v4fCol.z + m4fM[2][3] * v4fCol.w,
			m4fM[3][0] * v4fCol.x + m4fM[3][1] * v4fCol.y + m4fM[3][2] * v4fCol.z + m4fM[3][3] * v4fCol.w );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator* ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 ) {
		Vec4f const v4fSrcA0 = m4fM1[0];
		Vec4f const v4fSrcA1 = m4fM1[1];
		Vec4f const v4fSrcA2 = m4fM1[2];
		Vec4f const v4fSrcA3 = m4fM1[3];

		Vec4f const v4fSrcB0 = m4fM2[0];
		Vec4f const v4fSrcB1 = m4fM2[1];
		Vec4f const v4fSrcB2 = m4fM2[2];
		Vec4f const v4fSrcB3 = m4fM2[3];

		Mat4x4f m4fResult ( 0.f );
		m4fResult[0] = v4fSrcA0 * v4fSrcB0[0] + v4fSrcA1 * v4fSrcB0[1] + v4fSrcA2 * v4fSrcB0[2] + v4fSrcA3 * v4fSrcB0[3];
		m4fResult[1] = v4fSrcA0 * v4fSrcB1[0] + v4fSrcA1 * v4fSrcB1[1] + v4fSrcA2 * v4fSrcB1[2] + v4fSrcA3 * v4fSrcB1[3];
		m4fResult[2] = v4fSrcA0 * v4fSrcB2[0] + v4fSrcA1 * v4fSrcB2[1] + v4fSrcA2 * v4fSrcB2[2] + v4fSrcA3 * v4fSrcB2[3];
		m4fResult[3] = v4fSrcA0 * v4fSrcB3[0] + v4fSrcA1 * v4fSrcB3[1] + v4fSrcA2 * v4fSrcB3[2] + v4fSrcA3 * v4fSrcB3[3];
		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator/ ( Mat4x4f const & m4fM, GLfloat const & fS ) {
		return Mat4x4f (
			m4fM[0] / fS,
			m4fM[1] / fS,
			m4fM[2] / fS,
			m4fM[3] / fS );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator/ ( GLfloat const & fS, Mat4x4f const & m4fM ) {
		return Mat4x4f (
			fS / m4fM[0],
			fS / m4fM[1],
			fS / m4fM[2],
			fS / m4fM[3] );
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator/ ( Mat4x4f const & m4fM, Vec4f const & v4fRow ) {
		return m4fM.Inverse () * v4fRow;
	}

  ////////////////////////////////////////////////////////////
	Vec4f operator/ ( Vec4f const & v4fCol, Mat4x4f const & m4fM ) {
		return v4fCol * m4fM.Inverse ();
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f operator/ ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 ) {
		return m4fM1 * m4fM2.Inverse ();
	}

  ////////////////////////////////////////////////////////////
  // Constant unary operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
	Mat4x4f const operator- ( Mat4x4f const & m4fM ) {
		return Mat4x4f (
			-m4fM[0],
			-m4fM[1],
			-m4fM[2],
			-m4fM[3] );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f const operator++ ( Mat4x4f const & m4fM, int ) {
		return Mat4x4f (
			m4fM[0] + 1.f,
			m4fM[1] + 1.f,
			m4fM[2] + 1.f,
			m4fM[3] + 1.f );
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f const operator-- ( Mat4x4f const & m4fM, int ) {
		return Mat4x4f (
			m4fM[0] - 1.f,
			m4fM[1] - 1.f,
			m4fM[2] - 1.f,
			m4fM[3] - 1.f );
	}

  ////////////////////////////////////////////////////////////
  // Boolean operators
  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////
  GLboolean operator== ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 ) {
		return (m4fM1[0] == m4fM2[0]) && (m4fM1[1] == m4fM2[1]) && (m4fM1[2] == m4fM2[2]) && (m4fM1[3] == m4fM2[3]);
	}

  ////////////////////////////////////////////////////////////
  GLboolean operator!= ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 ) {
		return (m4fM1[0] != m4fM2[0]) || (m4fM1[1] != m4fM2[1]) || (m4fM1[2] != m4fM2[2]) || (m4fM1[3] != m4fM2[3]);
	}

} // namespace drimi
