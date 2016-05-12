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
#include <Game/GameEngine/States/GameStates/TitleState.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
TitleState::TitleState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList3D_ID   (0),
  m_uiRenderList2D_ID   (0),
	m_uiSkybox            (0),
	m_uiTitle             (0),
	m_uiMainMenu          (0),
  m_uiLicense           (0),
  m_sfMainView          ()
{
}

////////////////////////////////////////////////////////////
TitleState::~TitleState ( void ) {
  // Delete the render list 3D
//  Renderer3D& oRenderer3D = m_stContext.m_oGraphicsEngine.GetRenderer3D ();
//  oRenderer3D.Erase (m_uiRenderList3D_ID);
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);

  // Delete the game objects
//  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::Skybox, m_uiSkybox);
  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::Title, m_uiTitle);
  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::MainMenu, m_uiMainMenu);
  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::License, m_uiLicense);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean TitleState::Initialize ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Creation of the initializer for this state.
  m_uiInitializer_ID = oGameObjectsManager.CreateInitializer ();

  // Create a render list 3D
//  Renderer3D& oRenderer3D = m_stContext.m_oGraphicsEngine.GetRenderer3D ();
//  m_uiRenderList3D_ID = oRenderer3D.CreateRenderList ();

  // Game title background
//  if (!oGameObjectsManager.AddToInitializer<GO_Skybox> (m_uiInitializer_ID, GameObjects::Type::Skybox, m_uiSkybox)) {
    // Debug : It will be necessary to process the errors, in the future.
//  }

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();

  // Game title
  if (!oGameObjectsManager.AddToInitializer<GOTitle> (m_uiInitializer_ID, GameObjects::Type::Title, m_uiTitle)) {
    // Debug : It will be necessary to process the errors, in the future.
  }
  GOTitle& oGOTitle = oGameObjectsManager.GetGameObject<GOTitle> (GameObjects::Type::Title, m_uiTitle);
  oGOTitle.SetRenderList2D_ID (m_uiRenderList2D_ID);
  oGOTitle.SetPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));
  // Game main menu
  if (!oGameObjectsManager.AddToInitializer<GOMainMenu> (m_uiInitializer_ID, GameObjects::Type::MainMenu, m_uiMainMenu)) {
    // Debug : It will be necessary to process the errors, in the future.
  }
  GOMainMenu& oGOMainMenu = oGameObjectsManager.GetGameObject<GOMainMenu> (GameObjects::Type::MainMenu, m_uiMainMenu);
  oGOMainMenu.SetRenderList2D_ID (m_uiRenderList2D_ID);
	oGOMainMenu.SetPosition (oGOTitle.GetPosition ().x, oGOTitle.GetPosition ().y+96);
	// Game licence and version
  if (!oGameObjectsManager.AddToInitializer<GOLicense> (m_uiInitializer_ID, GameObjects::Type::License, m_uiLicense)) {
    // Debug : It will be necessary to process the errors, in the future.
  }
  GOLicense& oGOLicense = oGameObjectsManager.GetGameObject<GOLicense> (GameObjects::Type::License, m_uiLicense);
  oGOLicense.SetRenderList2D_ID (m_uiRenderList2D_ID);

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, gmMainWindow.GetWidth ()*1.f, gmMainWindow.GetHeight ()*1.f));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void TitleState::ResizeView ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Update the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, gmMainWindow.GetWidth ()*1.f, gmMainWindow.GetHeight ()*1.f));

  // Game title background
//  GO_Skybox& oGOSkybox = oGameObjectsManager.GetGameObject<GO_Skybox> (GameObjects::Type::Skybox, m_uiSkybox);
//  oGOSkybox.ResizeView ();
  // Game title
  GOTitle& oGOTitle = oGameObjectsManager.GetGameObject<GOTitle> (GameObjects::Type::Title, m_uiTitle);
  oGOTitle.SetPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 3.f));
  oGOTitle.ResizeView ();
  // Game main menu
  GOMainMenu& oGOMainMenu = oGameObjectsManager.GetGameObject<GOMainMenu> (GameObjects::Type::MainMenu, m_uiMainMenu);
	oGOMainMenu.SetPosition (oGOTitle.GetPosition ().x, oGOTitle.GetPosition ().y+96);
  oGOMainMenu.ResizeView ();
  // Game license and version
  GOLicense& oGOLicense = oGameObjectsManager.GetGameObject<GOLicense> (GameObjects::Type::License, m_uiLicense);
  oGOLicense.ResizeView ();
}

////////////////////////////////////////////////////////////
void TitleState::Draw ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

//  Renderer3D& oRenderer3D = m_stContext.m_oGraphicsEngine.GetRenderer3D ();
  // Draw the skybox
//  oRenderer3D.Render (m_uiRenderList3D_ID, gmMainWindow);

  gmMainWindow.EnableSFML ();

  // Activating of the main view
  gmMainWindow.setView (m_sfMainView);

  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  // Animated title logo
  GOTitle& oGOTitle = oGameObjectsManager.GetGameObject<GOTitle> (GameObjects::Type::Title, m_uiTitle);
  oGOTitle.UpdateAnimation ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean TitleState::Update ( void ) {
  // Update the background
//  GO_Skybox& oGOSkybox = m_stContext.m_oGameObjectsManager.GetGameObject<GOTitleBackground> (GameObjects::Type::Skybox, m_uiSkybox);
//	return oGOSkybox.Update ();
  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean TitleState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  if (eEventType == drimi::Event::Type::Closed) {
    gmMainWindow.Close ();
	} else if (eEventType == drimi::Event::Type::Resized) {
    ResizeView ();
	} else if (eEventType == drimi::Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      case sf::Keyboard::Key::Escape :
        gmMainWindow.Close ();
        break;
      case sf::Keyboard::Key::Return :
        RequestStackReplace (States::ID::World);
        break;
      default :
        break;
    }
	}
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean TitleState::HandleTextUnicode ( const GLchar cUnicode ) {
  return GL_FALSE;
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
