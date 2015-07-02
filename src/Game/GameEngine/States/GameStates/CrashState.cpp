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
#include <Game/GameEngine/States/GameStates/CrashState.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
CrashState::CrashState ( StateStack& oStack, ST_Context stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID (0),
  m_uiError_ID        (0),
  m_uiDetails_ID      (0)
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  gmMainWindow.EnableSFML ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

  // Error message
  m_uiError_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oError  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiError_ID);
  oError.SetFont          (stContext.m_oBmpFont);
  oError.SetString        ("A critical error of unknown origin arose and caused the stop of the game.");
  oError.SetStyle         (sf::Text::Style::Bold);
  oError.SetColor         (sf::Color::Red);
	oError.SetOrigin        (oError.GetLocalBounds ().width / 2.f, 0.f);
	oError.setPosition      (gmMainWindow.GetView ().getCenter ().x, 100.f);
	//Error details
  m_uiDetails_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oDetails  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiDetails_ID);
  oDetails.SetFont          (stContext.m_oBmpFont);
  oDetails.SetString        ("There is no detail available.");
  oDetails.SetColor         (sf::Color::Yellow);
	oDetails.SetOrigin        (oDetails.GetLocalBounds ().width / 2.f, 0.f);
	oDetails.setPosition      (gmMainWindow.GetView ().getCenter ().x, 130.f);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
CrashState::~CrashState ( void ) {
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void CrashState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  gmMainWindow.EnableSFML ();
	
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);
	
  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean CrashState::Update ( void ) {
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean CrashState::HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
	if (eEventType == Event::Type::KeyPressed) {
    if (sfKeyCode == sf::Keyboard::Key::Escape) {
      gm::RenderWindow& gmMainWindow = GetMainWindow ();
      gmMainWindow.Close ();
    }
	}
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean CrashState::HandleInput ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& CrashState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
