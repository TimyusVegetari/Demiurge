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
 * \file GOTitleBackground.hpp
 * \brief Class for the title of the game.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef GOTITLEBACKGROUND_HPP__
#define GOTITLEBACKGROUND_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObject3D.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Shaders/ShaderProgram.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Skybox/Skybox.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the background for the title of the game.
///
////////////////////////////////////////////////////////////
class GOTitleBackground : public GameObject, public GameObject3D {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint          m_uiCamera_ID;
    ShaderProgram   m_oShaderProgramSkybox;
    Skybox          m_oSkybox;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the game object.
    ///
    ////////////////////////////////////////////////////////////
    GOTitleBackground ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GOTitleBackground ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the game object.
    ///
    /// \return True if the initialization is not finish, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Upgrade all the composants of the game object when
    /// the render target view is resized.
    ///
    ////////////////////////////////////////////////////////////
    void ResizeView ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the game object.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the update of the components of the game object.
    ///
    /// \return True to permit the other game objects to be updated, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Update ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the state.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) { return GL_FALSE; }

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the game object.
    ///
    /// \return True to permit the inputs of the other game objects to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void ) { return GL_FALSE; }
};

#endif // GOTITLEBACKGROUND_HPP__
