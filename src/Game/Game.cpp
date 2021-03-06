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
  m_uiTickDelay     = 0;
  m_uiTickTrigger   = 0;
  m_bPassMouseMoved = GL_FALSE;

  // Temporary game objects identifiers before futures upgrades.
  m_uiGO_Skybox = 0;
  m_uiGO_Box    = 0;

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

  // Set the tick rate of the game mecanic
  SetTickRate (20);

  // Initialize the 3D graphics engine
  m_oGraphicsEngine.Configurate (m_v2uSize.x, m_v2uSize.y, 32);
  if (!m_oGraphicsEngine.Initialize ())
    return GL_FALSE;
  m_oGraphicsEngine.SetFrameRate (30);

  std::cout << "" << std::endl;
  std::cout << "==== Initialization of some game objects ==========" << std::endl;
  // Some game objects initializations
//  m_oGameObjectsManager.AddGameObject (GameObjects::Type::Skybox, m_uiGO_Skybox);
  // Render targets registration in the list
  RegisterRenderTargets ();
  std::cout << "" << std::endl;
  std::cout << "==== Registration of the game states ==========" << std::endl;
  // States registration in the stack
  m_oStateStack.RegisterStates ();
  std::cout << "" << std::endl;
  // Initialize the main window
  if (!InitWinMain ())
    return GL_FALSE;
  std::cout << "==== Initialization of the first state ========" << std::endl;
  // Prepare the first state of the game
  m_oStateStack.Initialize (States::ID::InDevInfo);
  std::cout << "" << std::endl;

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
      m_oStateStack.Crash ();
  }
}

////////////////////////////////////////////////////////////
void Game::GamePaint ( void ) {
  // Test of the clock to determine if the frame delay is passed
  if (FrameClock ()) {
    gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);
    //gmMainWindow.Clear ();

    glClearDepth (1.f);
    glClearColor (0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
void Game::ProcessInput ( void ) {
  gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);

  drimi::Event::Type eEventType = drimi::Event::Type::None;
  sf::Keyboard::Key sfKeyCode = sf::Keyboard::Key::Unknown;
  GLchar cUnicode = '\0';
  GLboolean bHasFocus         = GL_TRUE;

  sf::Event sfEvent;
  while (gmMainWindow.PollEvent (sfEvent)) {
    // Elementary events for the main window of the game
    switch (sfEvent.type) {
      // Has focus :
      case sf::Event::EventType::GainedFocus :
        bHasFocus = GL_TRUE;
        break;
      // Hasn't focus :
      case sf::Event::EventType::LostFocus :
        bHasFocus = GL_FALSE;
        break;
      // Close window :
      case sf::Event::Closed :
        eEventType = drimi::Event::Type::Closed;
        break;
      // Resize window :
      case sf::Event::Resized :
        if (!m_oRenderTargetsManager.IsFullScreen ()) {
          gmMainWindow.SetView (sf::View (sf::FloatRect (0.f, 0.f, static_cast<GLfloat> (sfEvent.size.width), static_cast<GLfloat> (sfEvent.size.height))));
          gmMainWindow.SetSize (sf::Vector2u (sfEvent.size.width, sfEvent.size.height));
          ComputeWindowCenter ();
  //        eEventType = Event::Type::Resized;
          // Resize view for all the activated states of the game
          m_oStateStack.ResizeView ();
        }
        break;
      // Events of the keyboard
      case sf::Event::KeyPressed :
        if (bHasFocus) {
          eEventType = drimi::Event::Type::KeyPressed;
          sfKeyCode = sfEvent.key.code;
        } else
          eEventType = drimi::Event::Type::None;
        break;
      // Events of the text entered
      case sf::Event::TextEntered :
        if (sfEvent.text.unicode < 128)
          cUnicode = static_cast<char> (sfEvent.text.unicode);
        break;
      // Events of the mouse
      case sf::Event::MouseMoved :
        if (bHasFocus && !m_bPassMouseMoved) {
          eEventType = drimi::Event::Type::MouseMoved;
          // For the loop pass the redondant MouseMoved generated by
          // the changement of the position (probably a bug in the function
          // SetCursorPos for Microsoft Windows. I haven't checked for other OS).
          m_bPassMouseMoved = GL_TRUE;
        } else
          eEventType = drimi::Event::Type::None;
        break;
      case sf::Event::MouseWheelMoved :
        if (bHasFocus) {
          if (sfEvent.mouseWheel.delta > 0)
            eEventType = drimi::Event::Type::MouseWheelUp;
          else
            eEventType = drimi::Event::Type::MouseWheelDown;
        } else
          eEventType = drimi::Event::Type::None;
        break;
      default :
        eEventType = drimi::Event::Type::None;
        break;
    }

    // Call of the HandleTextUnicode or the HandleEvent of the states of the game
    if (eEventType != drimi::Event::Type::None) {
      if (cUnicode != '\0')
        m_oStateStack.HandleTextUnicode (cUnicode);
      else
        m_oStateStack.HandleEvent (eEventType, sfKeyCode);
    }
  }
  // Unlock the MouseMoved for the next tick.
  if (m_bPassMouseMoved)
    m_bPassMouseMoved = GL_FALSE;

  // Call of the HandleInput of the states of the game
  m_oStateStack.HandleInput ();
}
