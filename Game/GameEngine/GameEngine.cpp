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
#include "States/StateStack.cpp"
#include "RenderTargetsManager/RenderTargetsManager.cpp"

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameEngine::GameEngine ( void ) :
  m_oRenderTargetsManager (),
  m_v2uWindowCenter       (0, 0),
  m_v2uSize               (0, 0),
  m_szTitle               (""),
  m_szAuthor              (""),
  m_szVersion             (""),
  m_szCopyright           (""),
  m_szDate                (""),
  m_sfIcon                (),
  m_sfClock               (),
  m_uiElapsedTime         (0),
  m_oBmpFont              (),
  m_oStateStack           (State::ST_Context (m_oRenderTargetsManager, m_oBmpFont)),
  m_bSleep                (GL_FALSE)
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
  // Create the main window and set the mini icon and the title
  m_oRenderTargetsManager.AddRenderTarget (RenderTargets::ID::MainWindow);
  gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);

  if (m_sfIcon.getSize ().x != 0)
    gmMainWindow.SetIcon (m_sfIcon.getSize ().x, m_sfIcon.getSize ().y, m_sfIcon.getPixelsPtr ());

  std::string szTitle (m_szTitle+" "+m_szVersion);
  gmMainWindow.Create (sf::VideoMode (m_v2uSize.x, m_v2uSize.y, 32), szTitle);

  // Check if the main window is open
  if (!gmMainWindow.IsOpen ()) {
    std::cout << "Error : The main window cannot open !" << std::endl;
    return GL_FALSE;
  }

  // Compute the center of the main screen of the game
  ComputeWindowCenter ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GameEngine::ElapsedTime ( void ) {
  m_uiElapsedTime = static_cast<GLuint> ((m_sfClock.getElapsedTime ()).asMilliseconds ());
}

////////////////////////////////////////////////////////////
void GameEngine::ComputeWindowCenter ( void ) {
  gm::RenderWindow& gmMainWindow = GetWindow (RenderTargets::ID::MainWindow);
  m_v2uWindowCenter = sf::Vector2u (gmMainWindow.GetWidth ()/2, gmMainWindow.GetHeight ()/2);
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
std::string GameEngine::GetDate ( void ) {
  return m_szDate;
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
gm::RenderWindow& GameEngine::GetWindow ( RenderTargets::ID eRenderTargetID ) {
  return m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (eRenderTargetID);
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
  gm::RenderWindow& sfMainWindow = GetWindow (RenderTargets::ID::MainWindow);
  return sfMainWindow.IsOpen ();
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
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GameEngine::RegisterRenderTargets ( void ) {
  m_oRenderTargetsManager.RegisterRenderTarget<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
