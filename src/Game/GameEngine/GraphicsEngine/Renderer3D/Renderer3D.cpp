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

#include <Game/GameEngine/GraphicsEngine/Renderer3D/Renderer3D.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer3D::Renderer3D ( void ) :
  m_oCameraManager  ()
{
}

////////////////////////////////////////////////////////////
Renderer3D::~Renderer3D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer3D::Initialize ( void ) {
  std::cout << "Renderer 3D : Initializing..." << std::endl;
  GLboolean bSuccess = GL_TRUE;

  // Initialisation des programmes de shader
  //bSuccess = m_gShadersManager.Initialize ();

  // Initialisation des textures des blocs
  //bSuccess = m_gTexturesManager.InitializeBlockTextures ("data/materials/textures/blocks/blocktextures.xml");

  // Initialisation des maillages
  //bSuccess = m_gMeshesManager.Initialize ();

  if (bSuccess)
    std::cout << "Renderer 3D : Initialization succeed" << std::endl;
  else
    std::cout << "Renderer 3D : Initialization failed" << std::endl;
  return bSuccess;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
CameraManager& Renderer3D::GetCameraManager ( void ) {
  return m_oCameraManager;
}
