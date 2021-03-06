////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2016 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file TitleState.hpp
 * \brief Class to define the title state of the game.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2015-2016
 *
 */

#ifndef TITLESTATE_HPP__
#define TITLESTATE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../State.hpp"
#include <Game/includes.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the title state of the game.
/// This state contain the title of the game and the menu to play, or
/// for the options, etc...
///
////////////////////////////////////////////////////////////
class TitleState : public State {

  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint                    m_uiRenderList3D_ID,
                              m_uiRenderList2D_ID;
    GameObjects::ID           m_uiSkybox,
                              m_uiTitle,
                              m_uiMainMenu,
                              m_uiLicense;
    sf::View                  m_sfMainView;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a title state.
    ///
    ////////////////////////////////////////////////////////////
    TitleState ( StateStack& oStack, ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~TitleState ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the state.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Upgrade all the composants of the state when
    /// the render target view is resized.
    ///
    ////////////////////////////////////////////////////////////
    virtual void ResizeView ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Draw ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the update of the components of the state.
    ///
    /// \return True to permit the other states to be updated, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Update ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the state.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode );

    ////////////////////////////////////////////////////////////
    /// \brief Transmit a unicode text to the state.
    ///
    /// \param cUnicode   The current text unicode.
    ///
    /// \return True to permit the text unicode transmission of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleTextUnicode ( const GLchar cUnicode );

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the state.
    ///
    /// \return True to permit the inputs of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void );

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the main render window of the game.
    ///
    /// \return The main render window of the game
    ///
    ////////////////////////////////////////////////////////////
    gm::RenderWindow& GetMainWindow ( void );
};

#endif // TITLESTATE_HPP__
