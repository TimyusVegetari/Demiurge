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
#include "CrashState.hpp"

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
CrashState::CrashState ( StateStack& oStack, ST_Context stContext ) :
  State ( oStack, stContext ),
  m_oError (),
  m_oDetails ()
{
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Error message
  m_oError.SetFont        (*stContext.m_poBmpFont);
  m_oError.SetString      ("A critical error of unknown origin arose and caused the stop of the game.");
  m_oError.SetStyle       (sf::Text::Style::Bold);
  m_oError.SetColor       (sf::Color::Red);
	m_oError.setOrigin      (m_oError.GetLocalBounds ().width / 2.f, 0.f);
	m_oError.setPosition    (gmMainWindow.GetView ().getCenter ().x, 100.f);
	//Error details
  m_oDetails.SetFont      (*stContext.m_poBmpFont);
  m_oDetails.SetString    ("There is no detail available.");
  m_oDetails.SetColor     (sf::Color::Yellow);
	m_oDetails.setOrigin    (m_oDetails.GetLocalBounds ().width / 2.f, 0.f);
	m_oDetails.setPosition  (gmMainWindow.GetView ().getCenter ().x, 130.f);
}

////////////////////////////////////////////////////////////
CrashState::~CrashState ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void CrashState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
	gmMainWindow.Draw (m_oError);
	gmMainWindow.Draw (m_oDetails);
}

////////////////////////////////////////////////////////////
GLboolean CrashState::Update ( void ) {
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean CrashState::HandleEvent ( const sf::Event& sfEvent ) {
	if (sfEvent.type == sf::Event::KeyPressed) {
    if (sfEvent.key.code == sf::Keyboard::Key::Escape) {
      gm::RenderWindow& gmMainWindow = GetMainWindow ();
      gmMainWindow.Close ();
    }
	}
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& CrashState::GetMainWindow ( void ) {
  return GetContext ().m_poRenderTargetsManager->GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
