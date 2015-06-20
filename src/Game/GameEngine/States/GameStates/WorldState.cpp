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

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
WorldState::WorldState ( StateStack& oStack, ST_Context stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID       (0),
  m_uiSimpleInformations_ID (0),
  m_uiCamera_ID             (0),
  m_bMoved                  (GL_FALSE)
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Create a camera 3D
  CameraManager& oCameraManager = stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  m_uiCamera_ID = oCameraManager.CreateCamera ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (60.f, 1.f, 100.f);

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
}

////////////////////////////////////////////////////////////
WorldState::~WorldState ( void ) {
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
void WorldState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);
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

  // Update simple informations for debug
  RenderList2D& oRenderList2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ().GetRenderList (m_uiRenderList2D_ID);
  drimi::BmpText& oSimpleInformations = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiSimpleInformations_ID);
  oSimpleInformations.SetString       (std::string ("Fps : ")+m_stContext.m_oGraphicsEngine.GetFrameRate ()
                                      +std::string ("\nPlayer position : ")+oCamera.ToStringPosition ()
                                      +std::string ("\n       orientation : ")+oCamera.ToStringOrientation ()
                                      +std::string ("\n       focalisation : ")+oCamera.ToStringFocalisation ());

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
    oCamera.RotationZXFirstPerson (-fRelMouseY/8.f);
    oCamera.RotationYFirstPerson (fRelMouseX/8.f);
    sf::Mouse::setPosition (sf::Vector2i (static_cast<GLint> (gmMainWindow.GetWidth ()/2), static_cast<GLint> (gmMainWindow.GetHeight ()/2)), gmMainWindow);
  }

  if (eEventType == Event::Type::KeyPressed) {
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
    oCamera.MoveForwardAndBack (1.f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down)) {
    oCamera.MoveForwardAndBack (-1.f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right)) {
    oCamera.MoveRightAndLeft (1.f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left)) {
    oCamera.MoveRightAndLeft (-1.f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Numpad9)) {
    oCamera.MoveUpAndDown (1.f);
    m_bMoved = GL_TRUE;
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Numpad3)) {
    oCamera.MoveUpAndDown (-1.f);
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
