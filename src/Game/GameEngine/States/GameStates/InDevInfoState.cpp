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
#include <Game/GameEngine/States/GameStates/InDevInfoState.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
InDevInfoState::InDevInfoState ( StateStack& oStack, ST_Context stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID (0),
  m_uiTitle_ID        (0),
  m_uiContent_ID      (0),
  m_uiTickTrigger     (500),
  m_uiElapsedTicks    (0)
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

	// In development information title
  m_uiTitle_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oTitle  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTitle_ID);
  oTitle.SetFont        (stContext.m_oBmpFont);
  oTitle.SetString      ("Please note this is a pre-alpha version of Demiurge.");
  oTitle.SetStyle       (sf::Text::Style::Bold);
  oTitle.SetColor       (sf::Color::Yellow);
	oTitle.SetOrigin      (oTitle.GetLocalBounds ().width / 2.f, 0.f);
	oTitle.setPosition    (gmMainWindow.GetView ().getCenter ().x, 100.f);
	// In development information contant
  m_uiContent_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oContent  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiContent_ID);
  oContent.SetFont          (stContext.m_oBmpFont);
  oContent.SetString        (std::string ("It has only a fraction of the planned features\n")
                            +std::string ("and may contain bugs and be missing anims,\n")
                            +std::string ("sounds and other features.\n\n")
                            +std::string ("This does not reflect the quality, wealth or\n")
                            +std::string ("feature set of the imagined project.\n")
                            +std::string ("It is the beginning of a long-term work, intended to\n")
                            +std::string ("evolve during the years.\n\n")
                            +std::string ("Thank you for your understanding and good game !"));
  oContent.SetColor         (sf::Color::Green);
	oContent.SetOrigin        (oContent.GetLocalBounds ().width / 2.f, 0.f);
	oContent.setPosition      (gmMainWindow.GetView ().getCenter ().x, 130.f);
}

////////////////////////////////////////////////////////////
InDevInfoState::~InDevInfoState ( void ) {
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void InDevInfoState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);
}

////////////////////////////////////////////////////////////
GLboolean InDevInfoState::Update ( void ) {
  // After a laps of time the game go to the title state
  if (m_uiElapsedTicks >= m_uiTickTrigger) {
    RequestStackPop ();
    RequestStackPush (States::ID::Title);

    return GL_TRUE;
  } else
    m_uiElapsedTicks++; // Else, time goes by

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean InDevInfoState::HandleEvent ( const sf::Event& sfEvent ) {
	if (sfEvent.type == sf::Event::KeyPressed) {
    if (sfEvent.key.code == sf::Keyboard::Key::Return) {
      RequestStackPop ();
      RequestStackPush (States::ID::Title);
    }
	}
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& InDevInfoState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
