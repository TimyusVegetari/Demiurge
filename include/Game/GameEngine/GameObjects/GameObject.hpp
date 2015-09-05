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
 * \file GameObject.hpp
 * \brief Class for the game objects.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/RenderTargets/RenderTargetsManager.hpp>
#include <Game/GameEngine/GraphicsEngine/GraphicsEngine.hpp>
#include <Game/EventTypes.hpp>
#include "GameObjectIdentifiers.hpp"

class GameObjectsManager;

////////////////////////////////////////////////////////////
/// \brief Class to create game objects like as players,
/// creatures, equipments, vehicules, etc...
///
////////////////////////////////////////////////////////////
class GameObject {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<GameObject> Ptr;  ///< Unique pointer of game object.

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_Context {
      const GLuint&         m_uiElapsedTime;          ///< Reference of the absolute elapsed time of the game.
			RenderTargetsManager&	m_oRenderTargetsManager;  ///< Reference of the render targets manager of the game.
			drimi::BmpFont&       m_oBmpFont;               ///< Reference of the bitmap font of the game.
      GraphicsEngine&       m_oGraphicsEngine;        ///< Reference of the graphics engine of the game.
			GameObjectsManager&   m_oGameObjectsManager;    ///< Reference of the game objects manager.

			ST_Context  ( const GLuint& uiElapsedTime,
                    RenderTargetsManager&	oRenderTargetsManager,
                    drimi::BmpFont& oBmpFont,
                    GraphicsEngine& oGraphicsEngine,
                    GameObjectsManager& oGameObjectsManager );
      const GLuint& GetElapsedTime ( void );
      RenderList2D& GetRenderList2D ( GLuint uiRenderList2D_ID );
      GameObjectsManager& GetGameObjectsManager ( void );
    };

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ST_Context&       m_stContext;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a game object.
    ///
    ////////////////////////////////////////////////////////////
    GameObject ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GameObject ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the game object.
    ///
    /// \return True if the initialization is not finish, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( void ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the game object.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the game object.
    ///
    /// \return True to permit the inputs of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void ) = 0;

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the unique ressources context of the game
    ///
    /// \return The unique ressources context
    ///
    ////////////////////////////////////////////////////////////
    ST_Context& GetContext ( void ) const;

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the OpenGL manager.
    ///
    /// \return The OpenGL manager.
    ///
    ////////////////////////////////////////////////////////////
    OGLManager& GetOGLManager ( void );
};

#endif // GAMEOBJECT_HPP__
