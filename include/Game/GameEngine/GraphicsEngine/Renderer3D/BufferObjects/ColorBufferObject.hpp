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
 * \file ColorBufferObject.hpp
 * \brief Class to define a VBO.
 * \author Anthony Acroute
 * \version 0.4
 * \date 2013-2015
 *
 */

#ifndef COLORBUFFEROBJECT_HPP__
#define COLORBUFFEROBJECT_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/ColorArray.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to define the color of the VBOs.
///
////////////////////////////////////////////////////////////
class ColorBufferObject {

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ColorArray        m_oColors;

  public:
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a VBO.
    ///
    ////////////////////////////////////////////////////////////
    ColorBufferObject          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the VBO.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~ColorBufferObject ( void );

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Active the color pointer of OpenGL.
    ///
    /// \return True if activation succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean ActiveColorsPointer ( void );
};

#endif // COLORBUFFEROBJECT_HPP__
