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

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Mat4x4f.hpp
 * \brief Class of 4x4 matrix of floats.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef DRIMI_MATHEMATICS_Mat4x4f
#define DRIMI_MATHEMATICS_Mat4x4f

////////////////////////////////////////////////////////////
/// \brief Class of 4x4 matrix of floats
///
////////////////////////////////////////////////////////////
namespace drimi {

class Mat4x4f {
  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
		Vec4f     m_v4fValue[4];

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a 4x4 matrix of floats.
    ///
    ////////////////////////////////////////////////////////////
		Mat4x4f          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor.
    ///
    /// This constructor copy a 4x4 matrix of floats.
    ///
    ////////////////////////////////////////////////////////////
		Mat4x4f          ( Mat4x4f const & m4fM );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameter.
    ///
    /// This constructor defines a 4x4 matrix of floats with
    /// the same value in all the slots.
    ///
    ////////////////////////////////////////////////////////////
		explicit Mat4x4f ( GLfloat const & fS );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameters.
    ///
    /// This constructor defines a 4x4 matrix of floats slot by slot.
    ///
    ////////////////////////////////////////////////////////////
		explicit Mat4x4f (
			GLfloat const & fX0, GLfloat const & fY0, GLfloat const & fZ0, GLfloat const & fW0,
			GLfloat const & fX1, GLfloat const & fY1, GLfloat const & fZ1, GLfloat const & fW1,
			GLfloat const & fX2, GLfloat const & fY2, GLfloat const & fZ2, GLfloat const & fW2,
			GLfloat const & fX3, GLfloat const & fY3, GLfloat const & fZ3, GLfloat const & fW3
    );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameters.
    ///
    /// This constructor defines a 4x4 matrix of floats line by line.
    ///
    ////////////////////////////////////////////////////////////
		explicit Mat4x4f ( Vec4f const & v4fV0, Vec4f const & v4fV1, Vec4f const & v4fV2, Vec4f const & v4fV3 );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the 4x4 matrix of floats.
    ///
    ////////////////////////////////////////////////////////////
    ~Mat4x4f         ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Access operators.
    ///
    /// \return Vector of the values in a line of the matrix.
    ///
    ////////////////////////////////////////////////////////////
		Vec4f & operator[]        ( std::size_t i );
		Vec4f const & operator[]  ( std::size_t i ) const;

    ////////////////////////////////////////////////////////////
    // Unary operators
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Unary operators.
    ///
    ////////////////////////////////////////////////////////////
		Mat4x4f & operator=       ( Mat4x4f const & m4fM );
		Mat4x4f & operator+=      ( GLfloat const & fS );
		Mat4x4f & operator+=      ( Mat4x4f const & m4fM );
		Mat4x4f & operator-=      ( GLfloat const & fS );
		Mat4x4f & operator-=      ( Mat4x4f const & m4fM );
		Mat4x4f & operator*=      ( GLfloat const & fS );
		Mat4x4f & operator*=      ( Mat4x4f const & m4fM );
		Mat4x4f & operator/=      ( GLfloat const & fS );
		Mat4x4f & operator/=      ( Mat4x4f const & m4fM );
		Mat4x4f & operator++      ( void );
		Mat4x4f & operator--      ( void );
    Mat4x4f   Transpose       ( void ) const;
    Mat4x4f   Inverse         ( void ) const;
};

////////////////////////////////////////////////////////////
// Binary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Binary operators.
///
////////////////////////////////////////////////////////////
Mat4x4f operator+         ( Mat4x4f const & m4fM, GLfloat const & fS );
Mat4x4f operator+         ( GLfloat const & fS, Mat4x4f const & m4fM );
Mat4x4f operator+         ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 );
Mat4x4f operator-         ( Mat4x4f const & m4fM, GLfloat const & fS );
Mat4x4f operator-         ( GLfloat const & fS, Mat4x4f const & m4fM );
Mat4x4f operator-         ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 );
Mat4x4f operator*         ( Mat4x4f const & m4fM, GLfloat const & fS );
Mat4x4f operator*         ( GLfloat const & fS, Mat4x4f const & m4fM );

////////////////////////////////////////////////////////////
/// \brief Multiplicate a line and return a column.
///
////////////////////////////////////////////////////////////
Vec4f operator*           ( Mat4x4f const & m4fM, Vec4f const & v4fV );
Vec4f operator*           ( Vec4f const & v4fV, Mat4x4f const & m4fM );

//Mat2x4f operator*         ( Mat4x4f const & m4fM1, Mat2x4f const & m24fM2 );
//Mat3x4f operator*         ( Mat4x4f const & m4fM1, Mat3x4f const & m34fM2 );
Mat4x4f operator*         ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 );
Mat4x4f operator/         ( Mat4x4f const & m4fM, GLfloat const & fS );
Mat4x4f operator/         ( GLfloat const & fS, Mat4x4f const & m4fM );
Vec4f operator/           ( Mat4x4f const & m4fM, Vec4f const & v4fV );
Vec4f operator/           ( Vec4f & v4fV, Mat4x4f const & m4fM );
Mat4x4f operator/         ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 );

////////////////////////////////////////////////////////////
// Constant unary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Constant unary operators.
///
////////////////////////////////////////////////////////////
Mat4x4f const operator-   ( Mat4x4f const & m4fM );
Mat4x4f const operator--  ( Mat4x4f const & m4fM, int );
Mat4x4f const operator++  ( Mat4x4f const & m4fM, int );

////////////////////////////////////////////////////////////
// Boolean operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Boolean operators.
///
////////////////////////////////////////////////////////////
GLboolean operator==      ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 );
GLboolean operator!=      ( Mat4x4f const & m4fM1, Mat4x4f const & m4fM2 );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Mat4x4f
