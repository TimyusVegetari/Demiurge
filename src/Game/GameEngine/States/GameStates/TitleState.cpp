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
TitleState::TitleState ( StateStack& oStack, ST_Context stContext ) :
  State ( oStack, stContext ),
  /*m_sfTitle       (),
  m_sfBackground  (),
  m_oVersion      (),
  m_oLicense      (),*/
  m_uiRenderList2D_ID  (0),
  m_uiBackground_ID   (0),
  m_uiTitle_ID        (0),
  m_uiVersion_ID      (0),
  m_uiLicense_ID      (0)
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Loading of the textures 2D
  Textures2DManager& oTextures2DManager = stContext.m_oGraphicsEngine.GetTextures2DManager ();
  oTextures2DManager.LoadTexture (Textures2D::ID::GameTitle, "datas/gameTitle/title.png");
  oTextures2DManager.LoadTexture (Textures2D::ID::GameTitleBackground, "datas/gameTitle/background.png");

  // Create a render list 2D
  Renderer2D& oRenderer2D = stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

  // Game Title Background
  m_uiBackground_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfBackground = oRenderList2D.GetDrawable<sf::Sprite> (m_uiBackground_ID);
  sfBackground.setTexture (oTextures2DManager.GetTexture (Textures2D::ID::GameTitleBackground));
  // Game Title
  m_uiTitle_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitle_ID);
  sfTitle.setTexture  (oTextures2DManager.GetTexture (Textures2D::ID::GameTitle));
	sfTitle.setOrigin   (sfTitle.getLocalBounds ().width / 2.f, sfTitle.getLocalBounds ().height / 2.f);
	sfTitle.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));

	// Game version
  m_uiVersion_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oVersion = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiVersion_ID);
  oVersion.SetFont      (stContext.m_oBmpFont);
  oVersion.SetString    (std::string (DEMIURGE_NAME)+
                         std::string (" ")+
                         std::string (DEMIURGE_VERSION));
  oVersion.SetStyle     (sf::Text::Style::Bold);
  oVersion.SetColor     (sf::Color::Yellow);
	oVersion.SetOrigin    (0.f, oVersion.GetLocalBounds ().height);
	oVersion.setPosition  (5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);
	// Game licence
  m_uiLicense_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oLicense = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiLicense_ID);
  oLicense.SetFont      (stContext.m_oBmpFont);
  oLicense.SetString    (DEMIURGE_LICENSE);
  oLicense.SetColor     (sf::Color::Yellow);
	oLicense.SetOrigin    (oLicense.GetLocalBounds ().width, oLicense.GetLocalBounds ().height);
	oLicense.setPosition  (static_cast<GLfloat> (gmMainWindow.GetWidth ()) - 5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);

  /*// Game Title Background
  m_sfBackground.setTexture (oTextures2DManager.GetTexture (Textures2D::ID::GameTitleBackground));
  // Game Title
  m_sfTitle.setTexture  (oTextures2DManager.GetTexture (Textures2D::ID::GameTitle));
	m_sfTitle.setOrigin   (m_sfTitle.getLocalBounds ().width / 2.f, m_sfTitle.getLocalBounds ().height / 2.f);
	m_sfTitle.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));

	// Game version
  m_oVersion.SetFont      (stContext.m_oBmpFont);
  m_oVersion.SetString    (std::string (DEMIURGE_NAME)+
                           std::string (" ")+
                           std::string (DEMIURGE_VERSION));
  m_oVersion.SetStyle     (sf::Text::Style::Bold);
  m_oVersion.SetColor     (sf::Color::Yellow);
	m_oVersion.SetOrigin    (0.f, m_oVersion.GetLocalBounds ().height);
	m_oVersion.setPosition  (5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);
	// Game licence
  m_oLicense.SetFont      (stContext.m_oBmpFont);
  m_oLicense.SetString    (DEMIURGE_LICENSE);
  m_oLicense.SetColor     (sf::Color::Yellow);
	m_oLicense.SetOrigin    (m_oLicense.GetLocalBounds ().width, m_oLicense.GetLocalBounds ().height);
	m_oLicense.setPosition  (static_cast<GLfloat> (gmMainWindow.GetWidth ()) - 5.f, static_cast<GLfloat> (gmMainWindow.GetHeight ()) - 5.f);*/
}

////////////////////////////////////////////////////////////
TitleState::~TitleState ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void TitleState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);
	/*gmMainWindow.Draw (m_sfBackground);
	gmMainWindow.Draw (m_sfTitle);
	gmMainWindow.Draw (m_oVersion);
	gmMainWindow.Draw (m_oLicense);*/
}

////////////////////////////////////////////////////////////
GLboolean TitleState::Update ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean TitleState::HandleEvent ( const sf::Event& sfEvent ) {
  if (sfEvent.type == sf::Event::KeyPressed) {
    // Soon...
	}
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& TitleState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
