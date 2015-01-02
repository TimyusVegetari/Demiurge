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
#include "GameEngine.hpp"

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameEngine::GameEngine ( void ) :
  m_v2uWindowCenter (0, 0),
  m_v2uSize         (0, 0),
  m_szTitle         (""),
  m_szAuthor        (""),
  m_szVersion       (""),
  m_szCopyright     (""),
  m_uiElapsedTime   (0),
  m_bSleep          (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
GameEngine::~GameEngine ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GameEngine::InitWinMain ( void ) {
  // Set the mini icon of the main window
  if (m_sfIcon.getSize ().x != 0)
    m_sfWindow.setIcon (m_sfIcon.getSize ().x, m_sfIcon.getSize ().y, m_sfIcon.getPixelsPtr ());

  // Set the title of the main window
  std::string szTitle (m_szTitle+" "+m_szVersion);
  m_sfWindow.create (sf::VideoMode (m_v2uSize.x, m_v2uSize.y, 32), szTitle);

  // Check if the main window is open
  if (!m_sfWindow.isOpen ()) {
    std::cout << "Error : The main window cannot open !" << std::endl;
    return GL_FALSE;
  }

  // Compute the center of the main screen of the game
  ComputeWindowCenter ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
std::string GameEngine::GetTitle ( void ) {
  return m_szTitle;
}

////////////////////////////////////////////////////////////
std::string GameEngine::GetAuthor ( void ) {
  return m_szAuthor;
}

////////////////////////////////////////////////////////////
std::string GameEngine::GetVersion ( void ) {
  return m_szVersion;
}

////////////////////////////////////////////////////////////
std::string GameEngine::GetCopyright ( void ) {
  return m_szCopyright;
}

////////////////////////////////////////////////////////////
sf::Image& GameEngine::GetIcon ( void ) {
  return m_sfIcon;
}

////////////////////////////////////////////////////////////
GLuint GameEngine::GetWidth ( void ) {
  return m_v2uSize.x;
}

////////////////////////////////////////////////////////////
GLuint GameEngine::GetHeight ( void ) {
  return m_v2uSize.y;
}

////////////////////////////////////////////////////////////
void GameEngine::ElapsedTime ( void ) {
  m_uiElapsedTime = static_cast<GLuint> ((m_sfClock.getElapsedTime ()).asMilliseconds ());
}

////////////////////////////////////////////////////////////
sf::RenderWindow* GameEngine::GetWindow ( void ) {
  return &m_sfWindow;
}

////////////////////////////////////////////////////////////
void GameEngine::ComputeWindowCenter ( void ) {
  m_v2uWindowCenter = sf::Vector2u (m_sfWindow.getSize ().x/2, m_sfWindow.getSize ().y/2);
}

////////////////////////////////////////////////////////////
GLuint GameEngine::GetWindowWidth ( void ) {
  return m_sfWindow.getSize ().x;
}

////////////////////////////////////////////////////////////
GLuint GameEngine::GetWindowHeight ( void ) {
  return m_sfWindow.getSize ().y;
}

////////////////////////////////////////////////////////////
GLuint GameEngine::GetWindowCenterX ( void ) {
  return m_v2uWindowCenter.x;
}

////////////////////////////////////////////////////////////
GLuint GameEngine::GetWindowCenterY ( void ) {
  return m_v2uWindowCenter.y;
}

////////////////////////////////////////////////////////////
GLboolean GameEngine::WindowIsOpen ( void ) {
  return m_sfWindow.isOpen ();
}

////////////////////////////////////////////////////////////
void GameEngine::CloseWindow ( void ) {
  m_sfWindow.close ();
}

////////////////////////////////////////////////////////////
GLboolean GameEngine::GetSleep ( void ) {
  return m_bSleep;
}

////////////////////////////////////////////////////////////
void GameEngine::SetSleep ( GLboolean bSleep ) {
  m_bSleep = bSleep;
}

////////////////////////////////////////////////////////////
GLboolean GameEngine::PollEvent ( sf::Event& sfEvent ) {
  return m_sfWindow.pollEvent (sfEvent);
}

////////////////////////////////////////////////////////////
void GameEngine::CaptureScreen ( void ) {
  m_sfScreenCapture = m_sfWindow.capture ();
}

////////////////////////////////////////////////////////////
sf::Image& GameEngine::GetScreenCapture ( void ) {
  return m_sfScreenCapture;
}

////////////////////////////////////////////////////////////
void GameEngine::SetMouseVisibility ( GLboolean bVisibility ) {
  m_sfWindow.setMouseCursorVisible (bVisibility);
}
