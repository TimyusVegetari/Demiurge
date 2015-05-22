////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2013-2015 Acroute Anthony (ant110283@hotmail.fr)
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
// Headers
////////////////////////////////////////////////////////////
#include <Game/Game.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Game::Game ( void ) {
  // Initialization of the datas of the game engine
  m_v2uSize         = sf::Vector2u (DEMIURGE_WIDTH, DEMIURGE_HEIGHT);
  m_szTitle         = DEMIURGE_NAME;
  m_szAuthor        = DEMIURGE_AUTHOR;
  m_szVersion       = DEMIURGE_VERSION;
  m_szCopyright     = DEMIURGE_LICENSE;
  m_szDate          = DEMIURGE_DATE;
  m_uiTickTrigger   = 0;

  // Load the mini icon of the main window
  if (!m_sfIcon.loadFromFile ("./datas/icon.png")) {
    std::cout << "Error : the game's icon cannot be loaded !" << std::endl;
  }
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

  // Loading of the fonts of the game
  m_oBmpFont.LoadFromFile ("datas/fonts/font.png", GL_FALSE);
  m_oBmpFont.LoadFromFile ("datas/fonts/font_bold.png", GL_TRUE);
  if (!m_oBmpFont.LoadShaderFromFile ("datas/fonts/shaders/font_vertshader.glsl", "datas/fonts/shaders/font_fragshader.glsl")) {
    std::cout << "Error during the loading of font's shaders !" << std::endl;

    return GL_FALSE;
  }

  // Render targets registration in the list
  RegisterRenderTargets ();

  // States registration in the stack
  RegisterStates ();
  // Prepare the first state of the game
  m_oStateStack.PushState (States::ID::InDevInfo);

  // Game objects registration
  RegisterGameObjects ();

  // Set the tick rate of the game mecanic
  SetTickRate (20);

  // Initialize the 3D graphics engine
  m_oGraphicsEngine.Configurate (m_v2uSize.x, m_v2uSize.y, 32);
  if (!m_oGraphicsEngine.Initialize ())
    return GL_FALSE;
  m_oGraphicsEngine.SetFrameRate (60);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void Game::GameCycle ( void ) {
  // If it's time to check events and execute game mecanic
  if (TickClock ()) {
    // Events and update game states, scenes, ... (game mecanic)
    ProcessInput ();
    m_oStateStack.Update ();

    // If the stack is empty, the crash state is called
    if (m_oStateStack.IsEmpty ())
      m_oStateStack.PushState (States::ID::None);
  }
}

////////////////////////////////////////////////////////////
void Game::GamePaint ( void ) {
  // Test de l'horloge pour déterminer si la durée pour une image est achevée
  if (FrameClock ()) {
    gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);
    gmMainWindow.Clear ();

    // Draw of the game states, scenes, ...
    m_oStateStack.Draw ();

    gmMainWindow.Display ();
  }
}

////////////////////////////////////////////////////////////
void Game::GameEnd ( void ) {
  gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);
  gmMainWindow.Close ();
  m_oRenderTargetsManager.DeleteRenderTarget (RenderTargets::ID::MainWindow);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Game::SetTickRate ( GLuint uiTickRate ) {
  m_uiTickDelay = 1000 / uiTickRate;
  m_uiTickTrigger = m_uiTickDelay;
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

////////////////////////////////////////////////////////////
GLboolean Game::FrameClock ( void ) {
  if (m_uiElapsedTime > m_oGraphicsEngine.GetFrameTrigger ()) {
    m_oGraphicsEngine.SetFrameTrigger (m_uiElapsedTime);
    m_oGraphicsEngine.ComputeFrameRate (m_uiElapsedTime);
    return GL_TRUE;
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void Game::RegisterStates ( void ) {
  m_oStateStack.RegisterState<InDevInfoState> (States::ID::InDevInfo);
  m_oStateStack.RegisterState<TitleState> (States::ID::Title);
}

////////////////////////////////////////////////////////////
void Game::ProcessInput ( void ) {
  gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);

  sf::Event sfEvent;
  while (gmMainWindow.PollEvent (sfEvent)) {
    // Call of the HandleEvent of the states of the game
    m_oStateStack.HandleEvent (sfEvent);

    // Elementary events for the main window of the game
    switch (sfEvent.type) {
      // Close window :
      case sf::Event::Closed :
        gmMainWindow.Close ();
        break;
      // Resize window :
      case sf::Event::Resized :
        gmMainWindow.SetView (sf::View (sf::FloatRect (0.f, 0.f, static_cast<GLfloat>(sfEvent.size.width), static_cast<GLfloat>(sfEvent.size.height))));
        ComputeWindowCenter ();
        break;
      default :
        break;
    }
  }
}

////////////////////////////////////////////////////////////
void Game::RegisterGameObjects ( void ) {
  //m_oGameObjectsManager.RegisterGameObject<...> (GameObjects::ID::...);
}
