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
  // Error message
  m_oError.SetFont            (*stContext.m_poBmpFont);
  m_oError.SetString          ("A critical error of unknown origin arose and caused the stop of the game.");
  m_oError.SetStyle           (sf::Text::Style::Bold);
  m_oError.SetColor           (sf::Color::Red);
	m_oError.setOrigin          (m_oError.getLocalBounds ().width / 2.f, 0.f);
	m_oError.setPosition        (stContext.m_psfMainWindow->getSize ().x / 2.f, 100.f);
	//Error details
  m_oDetails.SetFont            (*stContext.m_poBmpFont);
  m_oDetails.SetString          ("There is no detail available.");
  m_oDetails.SetColor           (sf::Color::Yellow);
	m_oDetails.setOrigin          (m_oDetails.getLocalBounds ().width / 2.f, 0.f);
	m_oDetails.setPosition        (stContext.m_psfMainWindow->getSize ().x / 2.f, 120.f);
}

////////////////////////////////////////////////////////////
CrashState::~CrashState ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void CrashState::Draw ( void ) {
  sf::RenderWindow& sfWindow = *GetContext ().m_psfMainWindow;
	sfWindow.draw (m_oError);
	sfWindow.draw (m_oDetails);
}

////////////////////////////////////////////////////////////
GLboolean CrashState::Update ( void ) {
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean CrashState::HandleEvent ( const sf::Event& sfEvent ) {
	if (sfEvent.type == sf::Event::KeyPressed) {
    if (sfEvent.key.code == sf::Keyboard::Key::Escape) {
      GetContext ().m_psfMainWindow->close ();
    }
	}
	return GL_FALSE;
}
