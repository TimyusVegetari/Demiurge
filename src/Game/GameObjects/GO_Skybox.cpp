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
#include <Game/GameObjects/GO_Skybox.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GO_Skybox::GO_Skybox ( void ) :
  Skybox          (),
  m_uiValue       (0)
{
}

////////////////////////////////////////////////////////////
GO_Skybox::GO_Skybox ( GLuint uiValue ) :
  Skybox          (),
  m_uiValue       (uiValue)
{
}

////////////////////////////////////////////////////////////
GO_Skybox::~GO_Skybox ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GO_Skybox::Initialize ( Textures2DManager& oTextures2DManager ) {
  std::cout << " >> GO_Skybox initializing..." << std::endl;
	// Skybox test
  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors activated by SFML.
  glEnable (GL_TEXTURE_CUBE_MAP);
	m_uiCubeMapID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, "./datas/skybox/skybox", "png");
  glDisable (GL_TEXTURE_CUBE_MAP);
	if (!InitializeVBO ()) {
    // Debug : It will be necessary to process the errors, in the future.
    return GL_FALSE;
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GO_Skybox::SetValue ( GLuint uiValue ) {
  std::cout << "  The value " << uiValue << " is stored." << std::endl;
  m_uiValue = uiValue;
}
