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
#include <Game/GameObjects/TitleState/GOTitle.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOTitle::GOTitle ( ST_Context& stContext ) :
  GameObject          (stContext),
  GameObject2D        (),
  m_sfPosition        (),
  m_uiTitle_ID        (0),
  m_uiTitleLogo_ID    (0),
	m_iTitleLogoFrameX  (128*32), ///< Initialization of the title logo animation
	m_iTitleLogoFrameY  (128*16)
{
}

////////////////////////////////////////////////////////////
GOTitle::~GOTitle ( void ) {
}

////////////////////////////////////////////////////////////
GLboolean GOTitle::Initialize ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  gmMainWindow.EnableSFML ();

  // Loading of the textures 2D
  GLuint  uiTitleTexID      = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gameTitle/title", "png"),
          uiLogoTexID       = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gameTitle/titlelogo", "png");

  // Game Title
  m_uiTitle_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitle_ID);
  sfTitle.setTexture  (oTextures2DManager.GetSFMLTexture (uiTitleTexID));
	sfTitle.setOrigin   (sfTitle.getLocalBounds ().width / 2.f, sfTitle.getLocalBounds ().height / 2.f);
	sfTitle.setPosition (m_sfPosition.x, m_sfPosition.y);
  // Game Title Logo
  m_uiTitleLogo_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitleLogo = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitleLogo_ID);
  sfTitleLogo.setTexture      (oTextures2DManager.GetSFMLTexture (uiLogoTexID));
  sfTitleLogo.setTextureRect  (sf::IntRect (0, 0, 128, 128));
	sfTitleLogo.setOrigin       (sfTitleLogo.getLocalBounds ().width / 2.f, sfTitleLogo.getLocalBounds ().height / 2.f);
	sfTitleLogo.setPosition     (m_sfPosition.x, m_sfPosition.y - 3.f);

  gmMainWindow.DisableSFML ();

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void GOTitle::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  gmMainWindow.EnableSFML ();
  // Get the render list 2D
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  // Game Title
  sf::Sprite& sfTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitle_ID);
	sfTitle.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));
  // Game Title Logo
  sf::Sprite& sfTitleLogo = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitleLogo_ID);
	sfTitleLogo.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f - 3.f));
  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
void GOTitle::UpdateAnimation ( void ) {
  // Animated title logo
  m_iTitleLogoFrameX += 128;
  if (m_iTitleLogoFrameX >= 128*32) {
    m_iTitleLogoFrameX = 0;
    m_iTitleLogoFrameY += 128;
    if (m_iTitleLogoFrameY >= 128*16)
      m_iTitleLogoFrameY = 0;
  }
  m_stContext.GetRenderList2D (m_uiRenderList2D_ID).GetDrawable<sf::Sprite> (m_uiTitleLogo_ID).setTextureRect (sf::IntRect (m_iTitleLogoFrameX, m_iTitleLogoFrameY, 128, 128));
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOTitle::SetPosition ( GLfloat fX, GLfloat fY ) {
  m_sfPosition = sf::Vector2f (fX, fY);
}

////////////////////////////////////////////////////////////
const sf::Vector2f& GOTitle::GetPosition ( void ) {
  return m_sfPosition;
}

////////////////////////////////////////////////////////////
GLfloat GOTitle::GetHeight ( void ) {
  return m_stContext.GetRenderList2D (m_uiRenderList2D_ID).GetDrawable<sf::Sprite> (m_uiTitle_ID).getLocalBounds ().height;
}
