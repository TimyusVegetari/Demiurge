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
 * \file CrashState.hpp
 * \brief Class to define the crash state of the game.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef CRASHSTATE_HPP__
#define CRASHSTATE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../../State.hpp"
#if defined (INCLUDE_SFML__) && defined (INCLUDE_STD__) && defined (INCLUDE_DRIMI__)

////////////////////////////////////////////////////////////
/// \brief Class to create the crash state of the game. This state
/// appears on the screen when the game has a critical error and display
/// informations about this problem.
///
////////////////////////////////////////////////////////////
class CrashState : public State {

  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    drimi::BmpText    m_oError,
                      m_oDetails;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a crash state.
    ///
    ////////////////////////////////////////////////////////////
    CrashState ( StateStack& oStack, ST_Context stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~CrashState ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

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
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const sf::Event& sfEvent );

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

#endif // INCLUDE_SFML__ && INCLUDE_STD__ && INCLUDE_DRIMI__
#endif // CRASHSTATE_HPP__
