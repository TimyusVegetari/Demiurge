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
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/States/GameStates/TitleState.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
TitleState::TitleState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID   (0),
	m_oGOTitleBackground  (stContext),
	m_oGOTitle            (stContext),
	m_oGOMainMenu         (stContext),
  m_oGOLicense          (stContext)
{
}

////////////////////////////////////////////////////////////
TitleState::~TitleState ( void ) {
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean TitleState::Initialize ( void ) {
  std::cout << "TitleState initializing..." << std::endl;
  // Game title background
  m_oGOTitleBackground.Initialize ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();

  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Game title
  m_oGOTitle.SetRenderList2D_ID (m_uiRenderList2D_ID);
	m_oGOTitle.SetPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));
  m_oGOTitle.Initialize ();
  // Game main menu
  m_oGOMainMenu.SetRenderList2D_ID (m_uiRenderList2D_ID);
	m_oGOMainMenu.SetPosition (m_oGOTitle.GetPosition ().x, m_oGOTitle.GetPosition ().y+m_oGOTitle.GetHeight ());
  m_oGOMainMenu.Initialize ();
	// Game licence and version
  m_oGOLicense.SetRenderList2D_ID (m_uiRenderList2D_ID);
  m_oGOLicense.Initialize ();

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void TitleState::ResizeView ( void ) {
  // Game title background
  m_oGOTitleBackground.ResizeView ();
  // Game title
  m_oGOTitle.ResizeView ();
  // Game main menu
  m_oGOMainMenu.ResizeView ();
  // Game license and version
  m_oGOLicense.ResizeView ();
}

////////////////////////////////////////////////////////////
void TitleState::Draw ( void ) {
  // Draw the background
  m_oGOTitleBackground.Draw ();

  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  gmMainWindow.EnableSFML ();
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  // Animated title logo
  m_oGOTitle.UpdateAnimation ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);
  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean TitleState::Update ( void ) {
  // Update the background
	return m_oGOTitleBackground.Update ();
}

////////////////////////////////////////////////////////////
GLboolean TitleState::HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  if (eEventType == Event::Type::Closed) {
    gmMainWindow.Close ();
	} else if (eEventType == Event::Type::Resized) {
    ResizeView ();
	} else if (eEventType == Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      case sf::Keyboard::Key::Escape :
        gmMainWindow.Close ();
        break;
      case sf::Keyboard::Key::Return :
        RequestStackReplace (States::ID::World);
        break;
      default :
        break;
    }
	}
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean TitleState::HandleInput ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& TitleState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
