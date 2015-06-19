////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
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
// A big part of the code in this file is inspired by the book
// "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file State.hpp
 * \brief Class for the states of the game.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2014-2015
 *
 */

#ifndef STATE_HPP__
#define STATE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/RenderTargets/RenderTargetsManager.hpp>
#include <Game/GameEngine/GraphicsEngine/GraphicsEngine.hpp>
#include <Game/GameEngine/GameObjects/GameObjectsManager.hpp>
#include <Game/EventTypes.hpp>
#include "GameStates/StateIdentifiers.hpp"

class StateStack;

////////////////////////////////////////////////////////////
/// \brief Class to create states of the game like as the menu,
/// game pause, current game session, cinematic, etc...
///
////////////////////////////////////////////////////////////
class State {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<State>  Ptr; ///< Unique pointer of state.

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_Context {
			RenderTargetsManager&	m_oRenderTargetsManager;  ///< Reference of the render targets manager of the game.
			drimi::BmpFont&       m_oBmpFont;               ///< Reference of the bitmap font of the game.
      GraphicsEngine&       m_oGraphicsEngine;        ///< Reference of the graphics engine of the game.
			GameObjectsManager&   m_oGameObjectsManager;    ///< Reference of the game objects manager.

			ST_Context            ( RenderTargetsManager&	oRenderTargetsManager,
                              drimi::BmpFont& oBmpFont,
                              GraphicsEngine& oGraphicsEngine,
                              GameObjectsManager& oGameObjectsManager );
    };

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    StateStack&       m_oStack;
    ST_Context        m_stContext;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a state.
    ///
    ////////////////////////////////////////////////////////////
    State ( StateStack& oStack, ST_Context stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~State ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Draw ( void ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Call all the update of the components of the state.
    ///
    /// \return True to permit the other states to be updated, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Update ( void ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the state.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the state.
    ///
    /// \return True to permit the inputs of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void ) = 0;

  protected :
    ////////////////////////////////////////////////////////////
    /// \brief Add the state on the top of the stack.
    ///
    /// \param sStateID   Value to identify a specific state.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStackPush ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Remove the state of the stack.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStackPop ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call the method to clean the stack.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStateClear ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the unique ressources context of the game
    ///
    /// \return The unique ressources context
    ///
    ////////////////////////////////////////////////////////////
    ST_Context GetContext ( void ) const;
};

#endif // STATE_HPP__
