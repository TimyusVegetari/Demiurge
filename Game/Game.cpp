////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2013-2014 Acroute Anthony (ant110283@hotmail.fr)
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
// Headers
////////////////////////////////////////////////////////////
#include "Game.hpp"
#include "GameEngine/GameEngine.cpp"

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Game::Game ( void ) {
  // Initialization of the datas of the game engine
  m_v2uSize       = sf::Vector2u (854, 480);
  m_szTitle       = DEMIURGE_NAME;
  m_szAuthor      = DEMIURGE_AUTHOR;
  m_szVersion     = DEMIURGE_VERSION;
  m_szCopyright   = DEMIURGE_LICENSE;
  m_szDate        = DEMIURGE_DATE;
  m_uiTickTrigger = 0;

  // Load the mini icon of the main window
  if (!m_sfIcon.loadFromFile ("./datas/icon.png")) {
    std::cout << "Error : the game's icon cannot be loaded !" << std::endl;
  }

  // Set the tick rate of the game mecanic
  SetTickRate (20);
}


////////////////////////////////////////////////////////////
Game::~Game ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Game::GameInit ( void ) {
  // Display the main information about the game on the command window
  std::cout << m_szTitle << " v" << m_szVersion << " by " << m_szAuthor << std::endl;
  std::cout << "Game under license " << m_szCopyright << std::endl;
  std::cout << "Created in " << m_szDate << std::endl;
  std::cout << "Program in C++, using OpenGL and SFML" << std::endl << std::endl;

  // Create the OpenGL context with SFML
  sf::Context context (sf::ContextSettings (32), m_v2uSize.x, m_v2uSize.y);

  // Activate the vertical synchronisation of the screen
  m_sfWindow.setVerticalSyncEnabled (GL_TRUE);

  // Restart the universal clock
  m_sfClock.restart ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void Game::GameCycle ( void ) {
  // If it's time to check events and execute game mecanic
  if (TickClock ()) {
    // Elementary events for the main window of the game
    sf::Event sfEvent;
    while (PollEvent (sfEvent)) {
      switch (sfEvent.type) {
        // Close window :
        case sf::Event::Closed :
          CloseWindow ();
          break;
        // Resize window :
        case sf::Event::Resized :
          m_sfWindow.setView (sf::View (sf::FloatRect (0, 0, sfEvent.size.width, sfEvent.size.height)));
          ComputeWindowCenter ();
          break;
        default :
          break;
      }
    }
  }

  // Events and update of the game states, scenes, ... (game mecanic)
}

////////////////////////////////////////////////////////////
void Game::GamePaint ( void ) {

  // Draw of the game states, scenes, ...

  m_sfWindow.display ();
}

////////////////////////////////////////////////////////////
void Game::GameEnd ( void ) {
  CloseWindow ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Game::SetTickRate ( GLuint uiTickRate ) {
  m_uiTickDelay = 1000 / uiTickRate;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Game::TickClock ( void ) {
  if (m_uiElapsedTime > m_uiTickTrigger) {
    m_uiTickTrigger = m_uiElapsedTime + m_uiTickDelay;
    return GL_TRUE;
  }
  return GL_FALSE;
}
