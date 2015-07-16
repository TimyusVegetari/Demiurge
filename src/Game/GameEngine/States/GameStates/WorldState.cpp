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
#include <Game/GameEngine/States/GameStates/WorldState.hpp>
#include <Game/gamedev_info.hpp>
#include <glm/trigonometric.hpp> // glm::atan

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
WorldState::WorldState ( StateStack& oStack, ST_Context stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID       (0),
  m_uiSimpleInformations_ID (0),
  m_uiCamera_ID             (0),
  m_bMoved                  (GL_FALSE),
  m_oSkybox                 (),
  m_oBox                    ()
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

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
  Textures2DManager& oTextures2DManager = stContext.m_oGraphicsEngine.GetTextures2DManager ();
	m_oSkybox.SetCubeMapID (oTextures2DManager.LoadTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, "./datas/skybox/skybox", "png"));
  glDisable (GL_TEXTURE_CUBE_MAP);
	if (!m_oSkybox.InitializeCubeVBO ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

	m_oBox.SetDimensions (1.f, 1.f, 1.f);
	m_oBox.InitializeDatas ();
	m_oBox.InitializeBuffers (VBO_NORMALES | VBO_COLORS);

  gmMainWindow.EnableSFML ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

  // Simple informations for debug
  m_uiSimpleInformations_ID           = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oSimpleInformations = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiSimpleInformations_ID);
  oSimpleInformations.SetFont         (stContext.m_oBmpFont);
  oSimpleInformations.SetColor        (sf::Color::Green);
	oSimpleInformations.SetOrigin       (0.f, 0.f);
	oSimpleInformations.setPosition     (0.f, 0.f);

  gmMainWindow.DisableSFML ();

  gmMainWindow.SetMouseVisibility (GL_FALSE);
}

////////////////////////////////////////////////////////////
WorldState::~WorldState ( void ) {
  // Delete the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  oCameraManager.Erase (m_uiCamera_ID);
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);

  m_oBox.DeleteBuffers ();
  m_oBox.DeleteDatas ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void WorldState::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Get the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (69.f, 0.1f, 128.f);
}

////////////////////////////////////////////////////////////
void WorldState::Draw ( void ) {
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
	m_oSkybox.UpdateMVP (oCamera.GetLocalFocalisation (), oCamera.GetOrientation ());
  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors at the place of SFML.
  glDepthMask (GL_FALSE);   ///< Disable drawing in the depth buffer
  glEnable (GL_TEXTURE_CUBE_MAP);
	m_oSkybox.Draw (m_stContext.m_oGraphicsEngine.GetTextures2DManager ());
  glDisable (GL_TEXTURE_CUBE_MAP);
  glDepthMask (GL_TRUE);    ///< Enable drawing in the depth buffer
	glPopMatrix ();

  gluLookAt (oCamera.GetPosition ().x, oCamera.GetPosition ().y, oCamera.GetPosition ().z,
             oCamera.GetGlobalFocalisation ().x, oCamera.GetGlobalFocalisation ().y, oCamera.GetGlobalFocalisation ().z,
             oCamera.GetOrientation ().x, oCamera.GetOrientation ().y, oCamera.GetOrientation ().z);
  glEnable (GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  m_oBox.Render (VBO_NORMALES | VBO_COLORS, GL_QUADS);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDisable (GL_DEPTH_TEST);

  gmMainWindow.EnableSFML ();

  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean WorldState::Update ( void ) {
  // Update the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  if (m_bMoved) {
    oCamera.ApplyMove ();
    m_bMoved = GL_FALSE;
  }
  oCamera.FocaliseFirstPerson ();
  oCamera.UseMVP ();

  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  gmMainWindow.EnableSFML ();

  // Update simple informations for debug
  RenderList2D& oRenderList2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ().GetRenderList (m_uiRenderList2D_ID);
  drimi::BmpText& oSimpleInformations = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiSimpleInformations_ID);
  oSimpleInformations.SetString       (std::string ("Fps : ")+m_stContext.m_oGraphicsEngine.GetFrameRate ()
                                      +std::string ("\nPlayer position : ")+oCamera.ToStringPosition ()
                                      +std::string ("\n       orientation : ")+oCamera.ToStringOrientation ()
                                      +std::string ("\n       focalisation : ")+oCamera.ToStringGlobalFocalisation ()
                                      +std::string (" (")+oCamera.ToStringLocalFocalisation ()+std::string (")"));

  gmMainWindow.DisableSFML ();
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean WorldState::HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);

  if (eEventType == Event::Type::MouseMoved) {
    // Get the mouse mouvement
    GLfloat fRelMouseX = static_cast<GLfloat> (sf::Mouse::getPosition (gmMainWindow).x) - gmMainWindow.GetView ().getCenter ().x;
    GLfloat fRelMouseY = static_cast<GLfloat> (sf::Mouse::getPosition (gmMainWindow).y) - gmMainWindow.GetView ().getCenter ().y;
    // Rotate the camera 3D
    oCamera.RotationZXFirstPerson (-glm::radians (fRelMouseY*0.25f)); ///< 0.25f is the mouse sensitivity
    oCamera.RotationYFirstPerson (glm::radians (fRelMouseX*0.25f));
    sf::Mouse::setPosition (sf::Vector2i (static_cast<GLint> (gmMainWindow.GetWidth ()/2), static_cast<GLint> (gmMainWindow.GetHeight ()/2)), gmMainWindow);
  }

	if (eEventType == Event::Type::Resized) {
    ResizeView ();
  } else if (eEventType == Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      case sf::Keyboard::Key::Escape :
        gmMainWindow.Close ();
        break;
      default :
        break;
    }
	}
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean WorldState::HandleInput ( void ) {
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);

  // Move the camera 3D
  if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up)) {
    oCamera.MoveForwardAndBack (0.1f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down)) {
    oCamera.MoveForwardAndBack (-0.1f);
    m_bMoved = GL_TRUE;
  }
  if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right)) {
    oCamera.MoveRightAndLeft (-0.1f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left)) {
    oCamera.MoveRightAndLeft (0.1f);
    m_bMoved = GL_TRUE;
  }
  if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Numpad9)) {
    oCamera.MoveUpAndDown (0.1f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Numpad3)) {
    oCamera.MoveUpAndDown (-0.1f);
    m_bMoved = GL_TRUE;
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& WorldState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
