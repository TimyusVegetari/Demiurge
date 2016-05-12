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
#include <Game/GameEngine/States/GameStates/CrashState.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
CrashState::CrashState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID (0),
  m_uiBackground_ID   (0),
  m_uiError_ID        (0),
  m_uiDetails_ID      (0),
  m_sfMainView        ()
{
  std::cout << "CrashState construction..." << std::endl;
}

////////////////////////////////////////////////////////////
CrashState::~CrashState ( void ) {
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean CrashState::Initialize ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

  // Error background
  m_uiBackground_ID         = oRenderList2D.PushBack<sf::RectangleShape> ();
  sf::RectangleShape& sfBackground = oRenderList2D.GetDrawable<sf::RectangleShape> (m_uiBackground_ID);
  sfBackground.setSize      (sf::Vector2f (static_cast<GLfloat> (gmMainWindow.GetWidth ())-64.f, static_cast<GLfloat> (gmMainWindow.GetHeight ())-64.f));
  sfBackground.setFillColor (sf::Color (0, 0, 20, 220));
	sfBackground.setOrigin    (sfBackground.getLocalBounds ().width / 2.f, sfBackground.getLocalBounds ().height / 2.f);
	sfBackground.setPosition  (gmMainWindow.GetView ().getCenter ().x, gmMainWindow.GetView ().getCenter ().y);
  // Error message
  m_uiError_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oError  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiError_ID);
  oError.SetFont          (m_stContext.m_oBmpFont);
  oError.SetString        ("A critical error of unknown origin arose and caused the stop of the game.");
  oError.SetStyle         (sf::Text::Style::Bold);
  oError.SetColor         (sf::Color::Red);
	oError.SetOrigin        (oError.GetLocalBounds ().width / 2.f, 0.f);
	oError.setPosition      (gmMainWindow.GetView ().getCenter ().x, 100.f);
	//Error details
  m_uiDetails_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oDetails  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiDetails_ID);
  oDetails.SetFont          (m_stContext.m_oBmpFont);
  oDetails.SetString        ("There is no detail available.");
  oDetails.SetColor         (sf::Color::Yellow);
	oDetails.SetOrigin        (oDetails.GetLocalBounds ().width / 2.f, 0.f);
	oDetails.setPosition      (gmMainWindow.GetView ().getCenter ().x, 130.f);

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void CrashState::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Update the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));

  // Get the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

  // Error background
  sf::RectangleShape& sfBackground = oRenderList2D.GetDrawable<sf::RectangleShape> (m_uiBackground_ID);
  sfBackground.setSize      (sf::Vector2f (static_cast<GLfloat> (gmMainWindow.GetWidth ())-64.f, static_cast<GLfloat> (gmMainWindow.GetHeight ())-64.f));
	sfBackground.setOrigin    (sfBackground.getLocalBounds ().width / 2.f, sfBackground.getLocalBounds ().height / 2.f);
	sfBackground.setPosition  (gmMainWindow.GetView ().getCenter ().x, gmMainWindow.GetView ().getCenter ().y);
  // Error message
  drimi::BmpText& oError  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiError_ID);
	oError.setPosition      (gmMainWindow.GetView ().getCenter ().x, 100.f);
	//Error details
  drimi::BmpText& oDetails  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiDetails_ID);
	oDetails.setPosition      (gmMainWindow.GetView ().getCenter ().x, 130.f);
}

////////////////////////////////////////////////////////////
void CrashState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  gmMainWindow.EnableSFML ();

  // Activating of the main view
  gmMainWindow.setView (m_sfMainView);

  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean CrashState::Update ( void ) {
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean CrashState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
	if (eEventType == drimi::Event::Type::KeyPressed) {
    if (sfKeyCode == sf::Keyboard::Key::Escape) {
      gm::RenderWindow& gmMainWindow = GetMainWindow ();
      gmMainWindow.Close ();
    }
	}
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean CrashState::HandleInput ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& CrashState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
