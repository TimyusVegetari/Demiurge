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
#include <Game/GameObjects/TitleState/GOMainMenu.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOMainMenu::GOMainMenu ( ST_Context& stContext ) :
  GameObject          (stContext),
  GameObject2D        (),
  m_uiPressEnter_ID   (0)
{
}

////////////////////////////////////////////////////////////
GOMainMenu::~GOMainMenu ( void ) {
}

////////////////////////////////////////////////////////////
GLboolean GOMainMenu::Initialize ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  gmMainWindow.EnableSFML ();

	// Game Press Enter
  m_uiPressEnter_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oPressEnter = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiPressEnter_ID);
  oPressEnter.SetFont      (m_stContext.m_oBmpFont);
  oPressEnter.SetString    ("- Press Enter to continue -");
  oPressEnter.SetColor     (sf::Color::Green);
	oPressEnter.SetOrigin    (oPressEnter.GetLocalBounds ().width / 2.f, oPressEnter.GetLocalBounds ().height / 2.f);
	oPressEnter.setPosition  (m_sfPosition.x, m_sfPosition.y);

  gmMainWindow.DisableSFML ();

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void GOMainMenu::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  gmMainWindow.EnableSFML ();
  // Get the render list 2D
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  // Game Press Enter
  drimi::BmpText& oPressEnter = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiPressEnter_ID);
	oPressEnter.setPosition  (m_sfPosition.x, m_sfPosition.y);
  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOMainMenu::SetPosition ( GLfloat fX, GLfloat fY ) {
  m_sfPosition = sf::Vector2f (fX, fY);
}
