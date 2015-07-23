////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
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
 * \file Tex2DCoordsArray.hpp
 * \brief Class to define vertex array for VBOs.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef TEX2DCOORDSARRAY_HPP__
#define TEX2DCOORDSARRAY_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CGDatas.hpp"
#include <glm/vec2.hpp> // glm::vec2

////////////////////////////////////////////////////////////
/// \brief Class to store and manipulate the texture 2D coordinates of the VBOs.
///
////////////////////////////////////////////////////////////
class Tex2DCoordsArray : public CGDatas<GLfloat> {

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a texture 2D coordinates array.
    ///
    ////////////////////////////////////////////////////////////
    Tex2DCoordsArray ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the texture 2D coordinates array.
    ///
    ////////////////////////////////////////////////////////////
    ~Tex2DCoordsArray ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the texture 2D coordinates at the data position.
    ///
    /// \param iDataPos   Data position.
    ///
    /// \return Vector of the 2 floats.
    ///
    ////////////////////////////////////////////////////////////
    glm::vec2 GetTex2DCoords ( GLsizei iDataPos );
};

#endif // TEX3DCOORDSARRAY_HPP__
