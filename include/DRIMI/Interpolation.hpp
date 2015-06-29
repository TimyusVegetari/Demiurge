////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2013-2015 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file Interpolation.hpp
 * \brief Functions to interpolate values in 1D, 2D or 3D.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef DRIMI_INTERPOLATION_HPP__
#define DRIMI_INTERPOLATION_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/OpenGL.hpp>

#include <math.h>
#define PI 3.14159265

namespace drimi {
namespace interpolation {
////////////////////////////////////////////////////////////
/// \brief Functions to interpolate values in 1D, 2D or 3D.
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Interpolate 2 values (linear)
///
/// \param dA   Value of the start (ex: Y of a point)
///        dB   Value of the goal (ex: Y of a second point)
///        dX   Value of the factor (ex: X of a intermediate point)
///
/// \return Value from the factor between A and B (ex: Y of the intermediate point)
///
////////////////////////////////////////////////////////////
inline GLdouble Linear1D ( GLdouble dA, GLdouble dB, GLdouble dX );

////////////////////////////////////////////////////////////
/// \brief Interpolate 4 values (linear)
///
/// \param dA   Value of the square
///        dB   Value of the square
///        dC   Value of the square
///        dD   Value of the square
///        dX   Value of the factor (ex: X of a intermediate point)
///        dY   Value of the factor (ex: Y of a intermediate point)
///
/// \return Value from the factor between A, B, C and D
///
////////////////////////////////////////////////////////////
inline GLdouble Linear2D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dX, GLdouble dY );

////////////////////////////////////////////////////////////
/// \brief Interpolate 8 values (linear)
///
/// \param dA   Value of the cube
///        dB   Value of the cube
///        dC   Value of the cube
///        dD   Value of the cube
///        dE   Value of the cube
///        dF   Value of the cube
///        dG   Value of the cube
///        dH   Value of the cube
///        dX   Value of the factor (ex: X of a intermediate point)
///        dY   Value of the factor (ex: Y of a intermediate point)
///        dZ   Value of the factor (ex: Z of a intermediate point)
///
/// \return Value from the factor between A, B, C, D, E, F, G and H
///
////////////////////////////////////////////////////////////
inline GLdouble Linear3D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dE, GLdouble dF, GLdouble dG, GLdouble dH, GLdouble dX, GLdouble dY, GLdouble dZ );

////////////////////////////////////////////////////////////
/// \brief Interpolate 2 values (Cosine)
///
/// \param dA   Value of the start (ex: Y of a point)
///        dB   Value of the goal (ex: Y of a second point)
///        dX   Value of the factor (ex: X of a intermediate point)
///
/// \return Value from the factor between A and B (ex: Y of the intermediate point)
///
////////////////////////////////////////////////////////////
inline GLdouble Cosine1D ( GLdouble dA, GLdouble dB, GLdouble dX );

////////////////////////////////////////////////////////////
/// \brief Interpolate 4 values (Cosine)
///
/// \param dA   Value of the square
///        dB   Value of the square
///        dC   Value of the square
///        dD   Value of the square
///        dX   Value of the factor (ex: X of a intermediate point)
///        dY   Value of the factor (ex: Y of a intermediate point)
///
/// \return Value from the factor between A, B, C and D
///
////////////////////////////////////////////////////////////
inline GLdouble Cosine2D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dX, GLdouble dY );

////////////////////////////////////////////////////////////
/// \brief Interpolate 8 values (Cosine)
///
/// \param dA   Value of the cube
///        dB   Value of the cube
///        dC   Value of the cube
///        dD   Value of the cube
///        dE   Value of the cube
///        dF   Value of the cube
///        dG   Value of the cube
///        dH   Value of the cube
///        dX   Value of the factor (ex: X of a intermediate point)
///        dY   Value of the factor (ex: Y of a intermediate point)
///        dZ   Value of the factor (ex: Z of a intermediate point)
///
/// \return Value from the factor between A, B, C, D, E, F, G and H
///
////////////////////////////////////////////////////////////
inline GLdouble Cosine3D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dE, GLdouble dF, GLdouble dG, GLdouble dH, GLdouble dX, GLdouble dY, GLdouble dZ );

////////////////////////////////////////////////////////////
/// \brief Interpolate 4 values (Cubic)
///
/// \param dYxx Value of the points and around it
///        dX   Value of the factor (ex: X of a intermediate point)
///
/// \return Value from the factor between A and B (ex: Y of the intermediate point)
///
////////////////////////////////////////////////////////////
inline GLdouble Cubic1D ( GLdouble dY0, GLdouble dY1, GLdouble dY2, GLdouble dY3, GLdouble dX );

////////////////////////////////////////////////////////////
/// \brief Interpolate 16 values (Cubic)
///
/// \param dAxx Values of the points and around it
///        dBxx Values of the points and around it
///        dCxx Values of the points and around it
///        dDxx Values of the points and around it
///        dX   Value of the factor (ex: X of a intermediate point)
///        dY   Value of the factor (ex: Y of a intermediate point)
///
/// \return Value from the factor between A, B, C and D
///
////////////////////////////////////////////////////////////
inline GLdouble Cubic2D ( GLdouble dA00, GLdouble dA01, GLdouble dA02, GLdouble dA03,
                   GLdouble dB10, GLdouble dB11, GLdouble dB12, GLdouble dB13,
                   GLdouble dC20, GLdouble dC21, GLdouble dC22, GLdouble dC23,
                   GLdouble dD30, GLdouble dD31, GLdouble dD32, GLdouble dD33,
                   GLdouble dX, GLdouble dY );

////////////////////////////////////////////////////////////
/// \brief Interpolate 64 values (Cubic)
///
/// \param dAxx Values of the first square of points which compose the square
///        dBxx Values of the second square of points which compose the square
///        dCxx Values of the third square of points which compose the square
///        dDxx Values of the forth square of points which compose the square
///        dX   Value of the factor (ex: X of a intermediate point)
///        dY   Value of the factor (ex: Y of a intermediate point)
///        dZ   Value of the factor (ex: Z of a intermediate point)
///
/// \return Value from the factor between A, B, C and D
///
////////////////////////////////////////////////////////////
inline GLdouble Cubic3D ( GLdouble dA000, GLdouble dA001, GLdouble dA002, GLdouble dA003,
                   GLdouble dA010, GLdouble dA011, GLdouble dA012, GLdouble dA013,
                   GLdouble dA020, GLdouble dA021, GLdouble dA022, GLdouble dA023,
                   GLdouble dA030, GLdouble dA031, GLdouble dA032, GLdouble dA033,
                   GLdouble dB100, GLdouble dB101, GLdouble dB102, GLdouble dB103,
                   GLdouble dB110, GLdouble dB111, GLdouble dB112, GLdouble dB113,
                   GLdouble dB120, GLdouble dB121, GLdouble dB122, GLdouble dB123,
                   GLdouble dB130, GLdouble dB131, GLdouble dB132, GLdouble dB133,
                   GLdouble dC200, GLdouble dC201, GLdouble dC202, GLdouble dC203,
                   GLdouble dC210, GLdouble dC211, GLdouble dC212, GLdouble dC213,
                   GLdouble dC220, GLdouble dC221, GLdouble dC222, GLdouble dC223,
                   GLdouble dC230, GLdouble dC231, GLdouble dC232, GLdouble dC233,
                   GLdouble dD300, GLdouble dD301, GLdouble dD302, GLdouble dD303,
                   GLdouble dD310, GLdouble dD311, GLdouble dD312, GLdouble dD313,
                   GLdouble dD320, GLdouble dD321, GLdouble dD322, GLdouble dD323,
                   GLdouble dD330, GLdouble dD331, GLdouble dD332, GLdouble dD333,
                   GLdouble dX, GLdouble dY, GLdouble dZ );

}
}

#include <DRIMI/Interpolation.inl>

#endif // DRIMI_INTERPOLATION_HPP__
