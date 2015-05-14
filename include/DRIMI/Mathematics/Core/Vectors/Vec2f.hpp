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
 * \file Vec2f.hpp
 * \brief Class of 2 dimensional vector of floats.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef DRIMI_MATHEMATICS_Vec2f
#define DRIMI_MATHEMATICS_Vec2f

////////////////////////////////////////////////////////////
/// \brief Class of 2 dimensional vector of floats
///
////////////////////////////////////////////////////////////
namespace drimi {

class Vec3f;

class Vec2f {
  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
		GLfloat     x, y; // No coding style to permit free external access

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a 2 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		Vec2f            ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor.
    ///
    /// This constructor copy a 2 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		Vec2f            ( Vec2f const & v2fV );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameter.
    ///
    /// This constructor defines a 2 dimensional vector of floats with
    /// the same value in all the slots.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec2f   ( GLfloat const & fS );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameters.
    ///
    /// This constructor defines a 2 dimensional vector of floats slot by slot.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec2f   (
			GLfloat const & fS0,
			GLfloat const & fS1
    );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the 2 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
    ~Vec2f           ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Convertion constructor.
    ///
    /// This constructor convert a 3 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec2f              ( Vec3f const & v3fV );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Access operators.
    ///
    /// \return Slot value of the 2 dimensional vector.
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
		Vec2f & operator=           ( Vec2f const & v2fV );
		Vec2f & operator+=          ( GLfloat const & fS );
		Vec2f & operator+=          ( Vec2f const & v2fV );
		Vec2f & operator-=          ( GLfloat const & fS );
		Vec2f & operator-=          ( Vec2f const & v2fV );
		Vec2f & operator*=          ( GLfloat const & fS );
		Vec2f & operator*=          ( Vec2f const & v2fV );
		Vec2f & operator/=          ( GLfloat const & fS );
		Vec2f & operator/=          ( Vec2f const & v2fV );
		Vec2f & operator++          ( void );
		Vec2f & operator--          ( void );
};

////////////////////////////////////////////////////////////
// Binary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Binary operators.
///
////////////////////////////////////////////////////////////
Vec2f operator+             ( Vec2f const & v2fV, GLfloat const & fS );
Vec2f operator+             ( GLfloat const & fS, Vec2f const & v2fV );
Vec2f operator+             ( Vec2f const & v2fV1, Vec2f const & v2fV2 );
Vec2f operator-             ( Vec2f const & v2fV, GLfloat const & fS );
Vec2f operator-             ( GLfloat const & fS, Vec2f const & v2fV );
Vec2f operator-             ( Vec2f const & v2fV1, Vec2f const & v2fV2 );
Vec2f operator*             ( Vec2f const & v2fV, GLfloat const & fS );
Vec2f operator*             ( GLfloat const & fS, Vec2f const & v2fV );
Vec2f operator*             ( Vec2f const & v2fV1, Vec2f const & v2fV2 );
Vec2f operator/             ( Vec2f const & v2fV, GLfloat const & fS );
Vec2f operator/             ( GLfloat const & fS, Vec2f const & v2fV );
Vec2f operator/             ( Vec2f const & v2fV1, Vec2f const & v2fV2 );

////////////////////////////////////////////////////////////
// Constant unary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Constant unary operators.
///
////////////////////////////////////////////////////////////
Vec2f const operator-       ( Vec2f const & v2fV );
Vec2f const operator--      ( Vec2f const & v2fV, int );
Vec2f const operator++      ( Vec2f const & v2fV, int );

////////////////////////////////////////////////////////////
// Boolean operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Boolean operators.
///
////////////////////////////////////////////////////////////
GLboolean operator==        ( Vec2f const & v2fV1, Vec2f const & v2fV2 );
GLboolean operator!=        ( Vec2f const & v2fV1, Vec2f const & v2fV2 );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Vec2f
