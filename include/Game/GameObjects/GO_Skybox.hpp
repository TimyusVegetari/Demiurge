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
 * \file GO_Skybox.hpp
 * \brief Class for the skybox of the game.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef GO_SKYBOX_HPP__
#define GO_SKYBOX_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Objects3D/Skybox.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the skybox.
///
////////////////////////////////////////////////////////////
class GO_Skybox : public Skybox {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint              m_uiValue;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the object.
    ///
    ////////////////////////////////////////////////////////////
    GO_Skybox ( void );

    ////////////////////////////////////////////////////////////
    GO_Skybox  ( GLuint uiValue );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GO_Skybox ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the object.
    ///
    /// \param oTextures2DManager   The manager to get the texture of the skybox.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( Textures2DManager& oTextures2DManager );

    ////////////////////////////////////////////////////////////
    void SetValue ( GLuint uiValue );
};

#endif // GO_SKYBOX_HPP__