////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2015 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file ShadersManager.hpp
 * \brief Class to define the shaders manager.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2013-2015
 *
 */

#ifndef SHADERSMANAGER_HPP__
#define SHADERSMANAGER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Shaders/ShaderProgram.hpp>
#include <tinyxml2.h>

////////////////////////////////////////////////////////////
/// \brief Class to create a shader program.
///
////////////////////////////////////////////////////////////
class ShadersManager {

  private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ShaderProgram   m_oShaderPrograms[Shaders::ID::Count];

  public:
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a shaders manager.
    ///
    ////////////////////////////////////////////////////////////
    ShadersManager  ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the shaders manager.
    ///
    ////////////////////////////////////////////////////////////
    ~ShadersManager ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the shaders manager.
    ///
    /// \return True if the initialization succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get a type of a shader program.
    ///
    /// \param eType  Type of the shader program.
    ///
    /// \return An instance of the shader program.
    ///
    ////////////////////////////////////////////////////////////
    ShaderProgram& GetShaderProgram ( Shaders::ID eType );
};

#endif // SHADERSMANAGER_HPP__
