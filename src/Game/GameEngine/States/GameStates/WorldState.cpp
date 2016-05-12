////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2016 Acroute Anthony (ant110283@hotmail.fr)
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
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
WorldState::WorldState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID     (0),
  m_uiRenderList3D_ID     (0),
	m_uiCamera              (0),
	m_uiSimpleInformations  (0),
	m_uiSkybox              (0),
  m_uiBox                 (0),
  m_sfMainView            ()
{
}

////////////////////////////////////////////////////////////
WorldState::~WorldState ( void ) {
  // Delete the game objects
  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::Camera, m_uiCamera);
  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::SimpleInformations, m_uiSimpleInformations);
//  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::Skybox, m_uiSkybox);
//  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::Box, m_uiBox);

  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);

  // Delete the render list 3D
//  Renderer3D& oRenderer3D = m_stContext.m_oGraphicsEngine.GetRenderer3D ();
//  oRenderer3D.Erase (m_uiRenderList3D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean WorldState::Initialize ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Creation of the initializer for this state.
  m_uiInitializer_ID = oGameObjectsManager.CreateInitializer ();
  // Camera 3D
  if (!oGameObjectsManager.AddToInitializer<GOCamera> (m_uiInitializer_ID, GameObjects::Type::Camera, m_uiCamera)) {
    // Debug : It will be necessary to process the errors, in the future.
  }
  // Skybox
//  if (!oGameObjectsManager.AddToInitializer<GOSkybox> (m_uiInitializer_ID, GameObjects::Type::Skybox, m_uiSkybox)) {
    // Debug : It will be necessary to process the errors, in the future.
//  }
  // Box
//  if (!oGameObjectsManager.AddToInitializer<GOBox> (m_uiInitializer_ID, GameObjects::Type::Box, m_uiBox)) {
    // Debug : It will be necessary to process the errors, in the future.
//  }
	// Simple informations
  if (!oGameObjectsManager.AddToInitializer<GOSimpleInformations> (m_uiInitializer_ID, GameObjects::Type::SimpleInformations, m_uiSimpleInformations)) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  // Create a render list 3D
//  Renderer3D& oRenderer3D = m_stContext.m_oGraphicsEngine.GetRenderer3D ();
//  m_uiRenderList3D_ID = oRenderer3D.CreateRenderList (Shaders::ID::Wired);
//  RenderList3D& oRenderList3D = m_stContext.GetRenderList3D (m_uiRenderList3D_ID);
  // Camera 3D
  GOCamera& oGOCamera = oGameObjectsManager.GetGameObject<GOCamera> (GameObjects::Type::Camera, m_uiCamera);
  // Skybox
//  GOSkybox& oGOSkybox = oGameObjectsManager.GetGameObject<GOSkybox> (GameObjects::Type::Skybox, m_uiSkybox);
//  oRenderList3D.PushBack (GameObjects3D::Type::Skybox, m_uiSkybox);
//  oGOSkybox.SetRenderList3D_ID (m_uiRenderList3D_ID);
  // Box
//  GOBox& oGOBox = oGameObjectsManager.GetGameObject<GOBox> (GameObjects::Type::Box, m_uiBox);
//  oRenderList3D.PushBack (GameObjects3D::Type::WiredObject, m_uiBox);
//  oGOBox.SetRenderList3D_ID (m_uiRenderList3D_ID);

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
	// Simple informations
  GOSimpleInformations& oGOSimpleInformations = oGameObjectsManager.GetGameObject<GOSimpleInformations> (GameObjects::Type::SimpleInformations, m_uiSimpleInformations);
  oGOSimpleInformations.SetRenderList2D_ID (m_uiRenderList2D_ID);

  gmMainWindow.SetMouseVisibility (GL_FALSE);

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, gmMainWindow.GetWidth ()*1.f, gmMainWindow.GetHeight ()*1.f));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void WorldState::ResizeView ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  // Update the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat>(gmMainWindow.GetWidth ()), static_cast<GLfloat>(gmMainWindow.GetHeight ())));

  // Camera 3D
  GOCamera& oGOCamera = oGameObjectsManager.GetGameObject<GOCamera> (GameObjects::Type::Camera, m_uiCamera);
  oGOCamera.ResizeView ();
}

////////////////////////////////////////////////////////////
void WorldState::Draw ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  OGLManager& oOGLManager = GetOGLManager ();

  // Activating of the main view
  gmMainWindow.setView (m_sfMainView);

  Renderer3D& oRenderer3D = m_stContext.m_oGraphicsEngine.GetRenderer3D ();
//  if (oOGLManager.GetVersion () == 2)         ///< OpenGL 2
//    oRenderer3D.PerspectiveOGL2 (gmMainWindow);

  // Camera 3D
  GOCamera& oGOCamera = oGameObjectsManager.GetGameObject<GOCamera> (GameObjects::Type::Camera, m_uiCamera);

	// Skybox test
//  oRenderer3D.Render (m_uiRenderList3D_ID, GameObjects3D::Type::Skybox, oGOCamera.GetCameraID (), oOGLManager, oGameObjectsManager);
  /*GOSkybox& oGOSkybox = oGameObjectsManager.GetGameObject<GOSkybox> (GameObjects::Type::Skybox, m_uiSkybox);
	oGOSkybox.Draw (oGOCamera.GetCameraID ());*/

	// Box test
//  GOBox& oGOBox = oGameObjectsManager.GetGameObject<GOBox> (GameObjects::Type::Box, m_uiBox);
//	oGOBox.Draw (oGOCamera.GetCameraID ());

  gmMainWindow.EnableSFML ();

  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean WorldState::Update ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  // Update the camera 3D
  GOCamera& oGOCamera = oGameObjectsManager.GetGameObject<GOCamera> (GameObjects::Type::Camera, m_uiCamera);
  oGOCamera.Update ();

  // Update simple informations for debug
  GOSimpleInformations& oGOSimpleInformations = oGameObjectsManager.GetGameObject<GOSimpleInformations> (GameObjects::Type::SimpleInformations, m_uiSimpleInformations);
  oGOSimpleInformations.Update (oGOCamera.GetCameraID ());

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean WorldState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  if (eEventType == drimi::Event::Type::MouseMoved) {
    // Rotate the camera 3D
    GOCamera& oGOCamera = oGameObjectsManager.GetGameObject<GOCamera> (GameObjects::Type::Camera, m_uiCamera);
    oGOCamera.Rotate ();
  }

	if (eEventType == drimi::Event::Type::Resized) {
    ResizeView ();
  } else if (eEventType == drimi::Event::Type::KeyPressed) {
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
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  // Rotate the camera 3D
  GOCamera& oGOCamera = oGameObjectsManager.GetGameObject<GOCamera> (GameObjects::Type::Camera, m_uiCamera);
  oGOCamera.HandleInput ();

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& WorldState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
