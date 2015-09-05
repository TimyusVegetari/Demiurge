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
#include <Game/GameObjects/TitleState/GOLicense.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOLicense::GOLicense ( ST_Context& stContext ) :
  GameObject          (stContext),
  GameObject2D        (),
  m_uiVersion_ID      (0),
  m_uiLicense_ID      (0)
{
}

////////////////////////////////////////////////////////////
GOLicense::~GOLicense ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOLicense::Initialize ( void ) {
  std::cout << " >> GOLicense initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  gmMainWindow.EnableSFML ();

  GLuint uiElapsedSecond = 0;
  GLuint uiElapsedTime = m_stContext.GetElapsedTime ();

	// Game version
  m_uiVersion_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oVersion = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiVersion_ID);
  oVersion.SetFont      (m_stContext.m_oBmpFont);
  oVersion.SetString    (std::string (DEMIURGE_NAME)+
                         std::string (" ")+
                         std::string (DEMIURGE_VERSION));
  oVersion.SetStyle     (sf::Text::Style::Bold);
  oVersion.SetColor     (sf::Color::Yellow);
	oVersion.SetOrigin    (0.f, oVersion.GetLocalBounds ().height);
	oVersion.setPosition  (5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);

  uiElapsedTime = m_stContext.GetElapsedTime () - uiElapsedTime;
  if (uiElapsedTime >= 1000) {
    uiElapsedSecond = static_cast<GLuint> (uiElapsedTime / 1000.f);
    uiElapsedTime -= uiElapsedSecond * 1000;
  }
  std::cout << uiElapsedSecond << " s " << uiElapsedTime << " ms" << std::endl;

	// Game licence
  m_uiLicense_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oLicense = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiLicense_ID);
  oLicense.SetFont      (m_stContext.m_oBmpFont);
  oLicense.SetString    (DEMIURGE_LICENSE);
  oLicense.SetColor     (sf::Color::Yellow);
	oLicense.SetOrigin    (oLicense.GetLocalBounds ().width, oLicense.GetLocalBounds ().height);
	oLicense.setPosition  (static_cast<GLfloat> (gmMainWindow.GetWidth ()) - 5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);

  uiElapsedTime = m_stContext.GetElapsedTime () - uiElapsedTime;
  if (uiElapsedTime >= 1000) {
    uiElapsedSecond = static_cast<GLuint> (uiElapsedTime / 1000.f);
    uiElapsedTime -= uiElapsedSecond * 1000;
  }
  std::cout << uiElapsedSecond << " s " << uiElapsedTime << " ms" << std::endl;

  gmMainWindow.DisableSFML ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOLicense::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  gmMainWindow.EnableSFML ();
  // Get the render list 2D
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
	// Game version
  drimi::BmpText& oVersion = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiVersion_ID);
	oVersion.setPosition  (5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);
	// Game licence
  drimi::BmpText& oLicense = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiLicense_ID);
	oLicense.setPosition  (static_cast<GLfloat> (gmMainWindow.GetWidth ()) - 5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);
  gmMainWindow.DisableSFML ();
}
