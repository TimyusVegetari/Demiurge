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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Skybox/Skybox.hpp>

////////////////////////////////////////////////////////////
Skybox::Skybox ( void ) :
  VertexBufferObject  (),
  m_uiCubeMapID       (0)
{
  m_szTypeName  = "VBO::Skybox";
}

////////////////////////////////////////////////////////////
Skybox::~Skybox ( void ) {
}

////////////////////////////////////////////////////////////
void Skybox::SetCubeMapID ( const GLuint uiTextureID ) {
  m_uiCubeMapID = uiTextureID;
}

////////////////////////////////////////////////////////////
void Skybox::InitializeDatas ( void ) {
  GLfloat fWidth = 1.0f;          ///< Width of the cube

  m_oVertex.SetDatas (new GLfloat[24] {
      -fWidth,-fWidth,-fWidth,
      -fWidth, fWidth,-fWidth,
      -fWidth,-fWidth, fWidth,
      -fWidth, fWidth, fWidth,
       fWidth,-fWidth,-fWidth,
       fWidth, fWidth,-fWidth,
       fWidth,-fWidth, fWidth,
       fWidth, fWidth, fWidth
    }, 24, 3, GL_ARRAY_BUFFER);    ///< Coordinnates of the vertex

  m_oTextures.SetDatas (new GLfloat[24] {
      -fWidth,-fWidth,-fWidth,
      -fWidth, fWidth,-fWidth,
      -fWidth,-fWidth, fWidth,
      -fWidth, fWidth, fWidth,
       fWidth,-fWidth,-fWidth,
       fWidth, fWidth,-fWidth,
       fWidth,-fWidth, fWidth,
       fWidth, fWidth, fWidth
    }, 24, 3, GL_ARRAY_BUFFER);  ///< Coordinnates of the textures

  m_oIndex.SetDatas (
    new GLuint[24] {
      0, 1, 2, 3, // X Negative
      4, 6, 5, 7, // X Positive
      0, 2, 4, 6, // Y Negative
      1, 5, 3, 7, // Y Positive
      0, 4, 1, 5, // Z Negative
      2, 3, 6, 7, // Z Positive
    }, 24, 1, GL_ELEMENT_ARRAY_BUFFER);   ///< Index of the vertex and textures
}

////////////////////////////////////////////////////////////
GLboolean Skybox::InitializeCubeVBO ( void ) {
	InitializeDatas ();
	return InitializeBuffers (VBO_TEXTURES);
}

////////////////////////////////////////////////////////////
void Skybox::UpdateMVP ( const glm::vec3& v3fCamLocalFocalisation, const glm::vec3& v3fCamOrientation ) {
  gluLookAt (0, 0, 0, v3fCamLocalFocalisation.x, v3fCamLocalFocalisation.y, v3fCamLocalFocalisation.z, v3fCamOrientation.x, v3fCamOrientation.y, v3fCamOrientation.z);
}

////////////////////////////////////////////////////////////
void Skybox::Draw ( Textures2DManager& oTextures2DManager ) {
  // Binding of the cube map texture
  oTextures2DManager.BindTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, m_uiCubeMapID);
  Render (VBO_TEXTURES, GL_TRIANGLE_STRIP);
}
