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
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Skybox::Skybox ( void ) :
  VertexBufferObject      (),
  Tex3DCoordsBufferObject (),
  m_uiCubeMapID           (0)
{
  m_szTypeName  = "VBO::Skybox";
}

////////////////////////////////////////////////////////////
Skybox::~Skybox ( void ) {
  DeleteBuffers ();
  m_oTex3DCoords.DeleteBuffer ();
  DeleteDatas ();
  m_oTex3DCoords.DeleteDatas ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

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
    }, 24);   ///< Coordinnates of the vertex

  m_oTex3DCoords.SetDatas (new GLfloat[24] {
      -fWidth,-fWidth,-fWidth,
      -fWidth, fWidth,-fWidth,
      -fWidth,-fWidth, fWidth,
      -fWidth, fWidth, fWidth,
       fWidth,-fWidth,-fWidth,
       fWidth, fWidth,-fWidth,
       fWidth,-fWidth, fWidth,
       fWidth, fWidth, fWidth
    }, 24);   ///< Coordinnates of the textures

  m_oIndex.SetDatas (
    new GLuint[24] {
      0, 1, 2, 3, // X Negative
      4, 6, 5, 7, // X Positive
      0, 2, 4, 6, // Y Negative
      1, 5, 3, 7, // Y Positive
      0, 4, 1, 5, // Z Negative
      2, 3, 6, 7, // Z Positive
    }, 24);   ///< Index of the vertex and textures
}

////////////////////////////////////////////////////////////
GLboolean Skybox::InitializeVBO ( void ) {
  GLint iNoError = 1;

	InitializeDatas ();
  // Generating of the buffers
  iNoError &= m_oTex3DCoords.GenBufferID ();
  GenBuffers (iNoError);
  // Sending of the datas
  if (iNoError == 1) {
    iNoError &= m_oTex3DCoords.SendDatas ();
    SendDatas (iNoError);
  }

  return static_cast<GLboolean> (iNoError);
}

////////////////////////////////////////////////////////////
void Skybox::UpdateMVP ( const glm::vec3& v3fCamLocalFocalisation, const glm::vec3& v3fCamOrientation ) {
  gluLookAt (0, 0, 0, v3fCamLocalFocalisation.x, v3fCamLocalFocalisation.y, v3fCamLocalFocalisation.z, v3fCamOrientation.x, v3fCamOrientation.y, v3fCamOrientation.z);
}

////////////////////////////////////////////////////////////
void Skybox::Draw ( Textures2DManager& oTextures2DManager ) {
  // Binding of the cube map texture
  oTextures2DManager.BindTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, m_uiCubeMapID);
  glEnableClientState (GL_TEXTURE_COORD_ARRAY); ///< Activate texture coords array
  ActiveTex3DCoordsPointer ();

  Render (GL_TRIANGLE_STRIP);

  glDisableClientState (GL_TEXTURE_COORD_ARRAY);  ///< Deactivate texture coords array
}
