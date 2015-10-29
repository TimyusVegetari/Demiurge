////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2015 Acroute Anthony (ant110283@hotmail.fr)
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
#include <Game/GameObjects/GO_Box.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GO_Box::GO_Box ( void ) :
  Box         (),
  m_uiValue   (0)
{
}

////////////////////////////////////////////////////////////
GO_Box::GO_Box ( GLuint uiValue ) :
  Box         (),
  m_uiValue   (uiValue)
{
}

////////////////////////////////////////////////////////////
GO_Box::~GO_Box ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GO_Box::Initialize ( void ) {
  std::cout << " >> GO_Box initializing..." << std::endl;
	// Box test
  SetDimensions (1.f, 1.f, 1.f);
	if (!InitializeVBO ()) {
    // Debug : It will be necessary to process the errors, in the future.
    return GL_FALSE;
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GO_Box::SetValue ( GLuint uiValue ) {
  std::cout << "  The value " << uiValue << " is stored." << std::endl;
  m_uiValue = uiValue;
}
