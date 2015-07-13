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
  m_uiRenderList2D_ID (0),
  m_uiTitle_ID        (0),
  m_uiTitleLogo_ID    (0),
  m_uiPressEnter_ID   (0),
  m_uiVersion_ID      (0),
  m_uiLicense_ID      (0),
	m_iTitleLogoFrameX  (128*32), ///< Initialization of the title logo animation
	m_iTitleLogoFrameY  (128*16),
  m_uiCamera_ID       (0),
  m_oSkybox           ()
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  Textures2DManager& oTextures2DManager = stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Create a camera 3D
  CameraManager& oCameraManager = stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  m_uiCamera_ID = oCameraManager.CreateCamera ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (69.f, 0.1f, 128.f);

	// Skybox test
  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors activated by SFML.
  glEnable (GL_TEXTURE_CUBE_MAP);
	m_oSkybox.SetCubeMapID (oTextures2DManager.LoadTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, "./datas/skybox/skybox", "png"));
  glDisable (GL_TEXTURE_CUBE_MAP);
	if (!m_oSkybox.InitializeCubeVBO ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  gmMainWindow.EnableSFML ();

  // Loading of the textures 2D
  GLuint  uiTitleTexID      = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gameTitle/title", "png"),
          uiLogoTexID       = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gameTitle/titlelogo", "png");

  // Create a render list 2D
  Renderer2D& oRenderer2D = stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

  // Game Title
  m_uiTitle_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitle_ID);
  sfTitle.setTexture  (oTextures2DManager.GetSFMLTexture (uiTitleTexID));
	sfTitle.setOrigin   (sfTitle.getLocalBounds ().width / 2.f, sfTitle.getLocalBounds ().height / 2.f);
	sfTitle.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));
  // Game Title Logo
  m_uiTitleLogo_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitleLogo = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitleLogo_ID);
  sfTitleLogo.setTexture      (oTextures2DManager.GetSFMLTexture (uiLogoTexID));
  sfTitleLogo.setTextureRect  (sf::IntRect (0, 0, 128, 128));
	sfTitleLogo.setOrigin       (sfTitleLogo.getLocalBounds ().width / 2.f, sfTitleLogo.getLocalBounds ().height / 2.f);
	sfTitleLogo.setPosition     (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f - 3.f));
	// Game Press Enter
  m_uiPressEnter_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oPressEnter = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiPressEnter_ID);
  oPressEnter.SetFont      (stContext.m_oBmpFont);
  oPressEnter.SetString    ("- Press Enter to continue -");
  oPressEnter.SetColor     (sf::Color::Green);
	oPressEnter.SetOrigin    (oPressEnter.GetLocalBounds ().width / 2.f, oPressEnter.GetLocalBounds ().height / 2.f);
	oPressEnter.setPosition  (gmMainWindow.GetView ().getCenter ().x, gmMainWindow.GetView ().getCenter ().y);

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

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
TitleState::~TitleState ( void ) {
  // Delete the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  oCameraManager.Erase (m_uiCamera_ID);
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void TitleState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (69.0, static_cast<GLdouble> (gmMainWindow.GetWidth ())/static_cast<GLdouble> (gmMainWindow.GetHeight ()), 0.1, 128.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
	// Skybox test
	glPushMatrix ();
  glLoadIdentity ();
	m_oSkybox.UpdateMVP (oCamera.GetPosition (), oCamera.GetFocalisation (), oCamera.GetOrientation ());
  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors at the place of SFML.
  glDepthMask (GL_FALSE);   ///< Disable drawing in the depth buffer
  glEnable (GL_TEXTURE_CUBE_MAP);
	m_oSkybox.Draw (m_stContext.m_oGraphicsEngine.GetTextures2DManager ());
  glDisable (GL_TEXTURE_CUBE_MAP);
  glDepthMask (GL_TRUE);    ///< Enable drawing in the depth buffer
	glPopMatrix ();

  gmMainWindow.EnableSFML ();

  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();

  // Animated title logo
  m_iTitleLogoFrameX += 128;
  if (m_iTitleLogoFrameX >= 128*32) {
    m_iTitleLogoFrameX = 0;
    m_iTitleLogoFrameY += 128;
    if (m_iTitleLogoFrameY >= 128*16)
      m_iTitleLogoFrameY = 0;
  }
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);
  sf::Sprite& sfTitleLogo = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitleLogo_ID);
  sfTitleLogo.setTextureRect  (sf::IntRect (m_iTitleLogoFrameX, m_iTitleLogoFrameY, 128, 128));

  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean TitleState::Update ( void ) {
  // Update the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Rotate the camera 3D
  oCamera.RotationYFirstPerson (drimi::Radians (1.f/4.f));
  oCamera.ApplyMove ();
  oCamera.FocaliseFirstPerson ();
  oCamera.UseMVP ();

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean TitleState::HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  if (eEventType == Event::Type::Closed) {
    gmMainWindow.Close ();
	} else if (eEventType == Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      case sf::Keyboard::Key::Escape :
        gmMainWindow.Close ();
        break;
      case sf::Keyboard::Key::Return :
        RequestStackPop ();
        RequestStackPush (States::ID::World);
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
