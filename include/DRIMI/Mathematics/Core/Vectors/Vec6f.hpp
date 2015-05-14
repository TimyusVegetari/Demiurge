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
 * \file Vec6f.hpp
 * \brief Class of 6 dimensional vector of floats.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef DRIMI_MATHEMATICS_Vec6f
#define DRIMI_MATHEMATICS_Vec6f

////////////////////////////////////////////////////////////
/// \brief Class of 6 dimensional vector of floats
///
////////////////////////////////////////////////////////////
namespace drimi {

class Vec6f {
  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
		GLfloat     x1, y1, z1, x2, y2, z2; // No coding style to permit free external access

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a 6 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		Vec6f                       ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor.
    ///
    /// This constructor copy a 6 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
		Vec6f                       ( Vec6f const & v6fV );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameter.
    ///
    /// This constructor defines a 6 dimensional vector of floats with
    /// the same value in all the slots.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec6f              ( GLfloat const & fS );

    ////////////////////////////////////////////////////////////
    /// \brief constructor with parameters.
    ///
    /// This constructor defines a 6 dimensional vector of floats slot by slot.
    ///
    ////////////////////////////////////////////////////////////
		explicit Vec6f              (
			GLfloat const & fS0,
			GLfloat const & fS1,
			GLfloat const & fS2,
			GLfloat const & fS3,
			GLfloat const & fS4,
			GLfloat const & fS5
    );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the 6 dimensional vector of floats.
    ///
    ////////////////////////////////////////////////////////////
    ~Vec6f                      ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Access operators.
    ///
    /// \return Slot value of the 6 dimensional vector.
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
		Vec6f & operator=           ( Vec6f const & v6fV );
		Vec6f & operator+=          ( GLfloat const & fS );
		Vec6f & operator+=          ( Vec6f const & v6fV );
		Vec6f & operator-=          ( GLfloat const & fS );
		Vec6f & operator-=          ( Vec6f const & v6fV );
		Vec6f & operator*=          ( GLfloat const & fS );
		Vec6f & operator*=          ( Vec6f const & v6fV );
		Vec6f & operator/=          ( GLfloat const & fS );
		Vec6f & operator/=          ( Vec6f const & v6fV );
		Vec6f & operator++          ( void );
		Vec6f & operator--          ( void );
};

////////////////////////////////////////////////////////////
// Binary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Binary operators.
///
////////////////////////////////////////////////////////////
Vec6f operator+             ( Vec6f const & v6fV, GLfloat const & fS );
Vec6f operator+             ( GLfloat const & fS, Vec6f const & v6fV );
Vec6f operator+             ( Vec6f const & v6fV1, Vec6f const & v6fV2 );
Vec6f operator-             ( Vec6f const & v6fV, GLfloat const & fS );
Vec6f operator-             ( GLfloat const & fS, Vec6f const & v6fV );
Vec6f operator-             ( Vec6f const & v6fV1, Vec6f const & v6fV2 );
Vec6f operator*             ( Vec6f const & v6fV, GLfloat const & fS );
Vec6f operator*             ( GLfloat const & fS, Vec6f const & v6fV );
Vec6f operator*             ( Vec6f const & v6fV1, Vec6f const & v6fV2 );
Vec6f operator/             ( Vec6f const & v6fV, GLfloat const & fS );
Vec6f operator/             ( GLfloat const & fS, Vec6f const & v6fV );
Vec6f operator/             ( Vec6f const & v6fV1, Vec6f const & v6fV2 );

////////////////////////////////////////////////////////////
// Constant unary operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Constant unary operators.
///
////////////////////////////////////////////////////////////
Vec6f const operator-       ( Vec6f const & v6fV );
Vec6f const operator--      ( Vec6f const & v6fV, int );
Vec6f const operator++      ( Vec6f const & v6fV, int );

////////////////////////////////////////////////////////////
// Boolean operators
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Boolean operators.
///
////////////////////////////////////////////////////////////
GLboolean operator==        ( Vec6f const & v6fV1, Vec6f const & v6fV2 );
GLboolean operator!=        ( Vec6f const & v6fV1, Vec6f const & v6fV2 );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Vec6f
