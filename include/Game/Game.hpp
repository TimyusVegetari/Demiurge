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
// A little part of this code is inspired by the book "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Game.hpp
 * \brief Class for the game engine of Demiurge.
 * \author Anthony Acroute
 * \version 0.5
 * \date 2013-2016
 *
 */

#ifndef GAME_HPP__
#define GAME_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GameEngine/GameEngine.hpp"
#include <DRIMI/Utils/EventTypes.hpp>
#include "gamedev_info.hpp"

////////////////////////////////////////////////////////////
/// \brief Class for initialising and executing the game.
///
////////////////////////////////////////////////////////////
class Game : public GameEngine {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    // Time for the game mecanic
    GLuint            m_uiTickDelay;
    GLuint            m_uiTickTrigger;
    // Events system of the game
    GLboolean         m_bPassMouseMoved;

    // Temporary game objects identifiers before futures upgrades.
    GLuint            m_uiGO_Skybox;
    GLuint            m_uiGO_Box;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a game.
    ///
    ////////////////////////////////////////////////////////////
    Game            ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Game   ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the game.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean GameInit ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Manage the mecanic part of the game.
    ///
    ////////////////////////////////////////////////////////////
    void GameCycle ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Drawn all the composants of the game.
    ///
    ////////////////////////////////////////////////////////////
    void GamePaint ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Manage the closing of the game.
    ///
    ////////////////////////////////////////////////////////////
    void GameEnd ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the tick rate of the time of game mecanic.
    ///
    /// \param uiTickRate   Tick rate of the game mecanic, in ticks.
    ///
    ////////////////////////////////////////////////////////////
    void SetTickRate ( GLuint uiTickRate );

  private :
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the tick delay is elapsed and update the tick trigger.
    ///
    /// \return True if the tick delay is elapsed, False else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean TickClock ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get if the frame delay is elapsed and update the frame trigger.
    ///
    /// \return True if the frame delay is elapsed, False else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean FrameClock ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Process the input for all the components of the game.
    ///
    ////////////////////////////////////////////////////////////
    void ProcessInput ( void );
};

#endif // GAME_HPP__
