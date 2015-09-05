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
#include <Game/GameObjects/WorldState/GOCamera.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOCamera::GOCamera ( ST_Context& stContext ) :
  GameObject              (stContext),
  GameObject3D            (),
  m_uiCamera_ID           (0),
  m_bMoved                (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
GOCamera::~GOCamera ( void ) {
  // Delete the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  oCameraManager.Erase (m_uiCamera_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOCamera::Initialize ( void ) {
  std::cout << " >> GOCamera initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Create a camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  m_uiCamera_ID = oCameraManager.CreateCamera ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (69.f, 0.1f, 128.f);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOCamera::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Get the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (69.f, 0.1f, 128.f);
}

////////////////////////////////////////////////////////////
GLboolean GOCamera::Update ( void ) {
  // Update the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  if (m_bMoved) {
    oCamera.ApplyMove ();
    m_bMoved = GL_FALSE;
  }

  OGLManager& oOGLManager = GetOGLManager ();
  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    oCamera.FocaliseFirstPerson ();
    oCamera.UseMVP ();
  }

	return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOCamera::Rotate ( void ) {
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);

  // Get the mouse mouvement
  GLfloat fRelMouseX = static_cast<GLfloat> (sf::Mouse::getPosition (gmMainWindow).x) - gmMainWindow.GetView ().getCenter ().x;
  GLfloat fRelMouseY = static_cast<GLfloat> (sf::Mouse::getPosition (gmMainWindow).y) - gmMainWindow.GetView ().getCenter ().y;
  // Rotate the camera 3D
  oCamera.RotationZXFirstPerson (-glm::radians (fRelMouseY*0.25f)); ///< 0.25f is the mouse sensitivity
  oCamera.RotationYFirstPerson (glm::radians (fRelMouseX*0.25f));
  sf::Mouse::setPosition (sf::Vector2i (static_cast<GLint> (gmMainWindow.GetWidth ()/2), static_cast<GLint> (gmMainWindow.GetHeight ()/2)), gmMainWindow);
}

////////////////////////////////////////////////////////////
GLboolean GOCamera::HandleInput ( void ) {
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

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint GOCamera::GetCameraID ( void ) {
  return m_uiCamera_ID;
}
