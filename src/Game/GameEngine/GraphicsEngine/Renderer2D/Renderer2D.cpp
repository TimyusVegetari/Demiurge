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

#include <Game/GameEngine/GraphicsEngine/Renderer2D/Renderer2D.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer2D::Renderer2D ( void )
{
}

////////////////////////////////////////////////////////////
Renderer2D::~Renderer2D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer2D::Initialize ( void ) {
  std::cout << "Renderer 2D : Initializing..." << std::endl;
  GLboolean bSuccess = GL_TRUE;

  if (bSuccess)
    std::cout << "Renderer 2D : Initialization succeed" << std::endl;
  else
    std::cout << "Renderer 2D : Initialization failed" << std::endl;
  return bSuccess;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////
