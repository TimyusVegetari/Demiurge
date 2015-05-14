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

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Vec4f.hpp
 * \brief Class of 4 dimensional vector of floats.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef DRIMI_MATHEMATICS_Vec4f
#define DRIMI_MATHEMATICS_Vec4f

////////////////////////////////////////////////////////////
/// \brief Class of 4 dimensional vector of floats
///
////////////////////////////////////////////////////////////
namespace drimi {

class Vec4f {
  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
		GLfloat     x, y, z, w; // No coding style to permit free external access

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a 4 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		Vec4f                       ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor.
    ///
    /// This constructor copy a 4 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		Vec4f                       ( Vec4f const & v4fV );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameter.
    ///
    /// This constructor defines a 4 dimensional vector of floats with
    /// the same value in all the slots.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec4f              ( GLfloat const & fS );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameters.
    ///
    /// This constructor defines a 4 dimensional vector of floats slot by slot.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec4f              (
			GLfloat const & fS0,
			GLfloat const & fS1,
			GLfloat const & fS2,
			GLfloat const & fS3
    );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the 4 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
    ~Vec4f                      ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Convertion constructor.
    ///
    /// This constructor convert a 2 dimensional vector of floats or
    /// 3 dimensional vector of floats and floats.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec4f              ( Vec2f const & v2fV, GLfloat const & fS1, GLfloat const & fS2 );
		explicit Vec4f              ( GLfloat const & fS1, Vec2f const & v2fV, GLfloat const & fS2 );
		explicit Vec4f              ( GLfloat const & fS1, GLfloat const & fS2, Vec2f const & v2fV );
		explicit Vec4f              ( Vec3f const & v3fV, GLfloat const & fS );
		explicit Vec4f              ( GLfloat const & fS, Vec3f const & v3fV );
		explicit Vec4f              ( Vec2f const & v2fV1, Vec2f const & v2fV2 );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Access operators.
    ///
    /// \return Slot value of the 4 dimensional vector.
    ///
    ////////////////////////////////////////////////////////////
		GLfloat & operator[]        ( std::size_t i );
		GLfloat const & operator[]  ( std::size_t i ) const;

    ////////////////////////////////////////////////////////////
    // Unary operators
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Unary operators.
    ///
    ////////////////////////////////////////////////////////////
		Vec4f & operator=           ( Vec4f const & v4fV );
		Vec4f & operator+=          ( GLfloat const & fS );
		Vec4f & operator+=          ( Vec4f const & v4fV );
		Vec4f & operator-=          ( GLfloat const & fS );
		Vec4f & operator-=          ( Vec4f const & v4fV );
		Vec4f & operator*=          ( GLfloat const & fS );
		Vec4f & operator*=          ( Vec4f const & v4fV );
		Vec4f & operator/=          ( GLfloat const & fS );
		Vec4f & operator/=          ( Vec4f const & v4fV );
		Vec4f & operator++          ( void );
		Vec4f & operator--          ( void );
};

////////////////////////////////////////////////////////////
// Binary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Binary operators.
///
////////////////////////////////////////////////////////////
Vec4f operator+             ( Vec4f const & v4fV, GLfloat const & fS );
Vec4f operator+             ( GLfloat const & fS, Vec4f const & v4fV );
Vec4f operator+             ( Vec4f const & v4fV1, Vec4f const & v4fV2 );
Vec4f operator-             ( Vec4f const & v4fV, GLfloat const & fS );
Vec4f operator-             ( GLfloat const & fS, Vec4f const & v4fV );
Vec4f operator-             ( Vec4f const & v4fV1, Vec4f const & v4fV2 );
Vec4f operator*             ( Vec4f const & v4fV, GLfloat const & fS );
Vec4f operator*             ( GLfloat const & fS, Vec4f const & v4fV );
Vec4f operator*             ( Vec4f const & v4fV1, Vec4f const & v4fV2 );
Vec4f operator/             ( Vec4f const & v4fV, GLfloat const & fS );
Vec4f operator/             ( GLfloat const & fS, Vec4f const & v4fV );
Vec4f operator/             ( Vec4f const & v4fV1, Vec4f const & v4fV2 );

////////////////////////////////////////////////////////////
// Constant unary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Constant unary operators.
///
////////////////////////////////////////////////////////////
Vec4f const operator-       ( Vec4f const & v4fV );
Vec4f const operator--      ( Vec4f const & v4fV, int );
Vec4f const operator++      ( Vec4f const & v4fV, int );

////////////////////////////////////////////////////////////
// Boolean operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Boolean operators.
///
////////////////////////////////////////////////////////////
GLboolean operator==        ( Vec4f const & v4fV1, Vec4f const & v4fV2 );
GLboolean operator!=        ( Vec4f const & v4fV1, Vec4f const & v4fV2 );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Vec4f
