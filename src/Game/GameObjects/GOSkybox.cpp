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
#include <Game/GameObjects/GOSkybox.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOSkybox::GOSkybox ( ST_Context& stContext ) :
  GameObject              (stContext),
  GameObject3D            (),
  VertexBufferObject      (),
  Tex3DCoordsBufferObject (),
  m_uiCubeMapID           (0)
{
  m_szTypeName  = "GOSkybox";
}

////////////////////////////////////////////////////////////
GOSkybox::~GOSkybox ( void ) {
  DeleteBuffers ();
  m_oTex3DCoords.DeleteBuffer ();
  DeleteDatas ();
  m_oTex3DCoords.DeleteDatas ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOSkybox::Initialize ( void ) {
  std::cout << " >> GOSkybox initializing..." << std::endl;
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

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
void GOSkybox::UpdateMVP ( const glm::vec3& v3fCamLocalFocalisation, const glm::vec3& v3fCamOrientation ) {
  gluLookAt (0, 0, 0, v3fCamLocalFocalisation.x, v3fCamLocalFocalisation.y, v3fCamLocalFocalisation.z, v3fCamOrientation.x, v3fCamOrientation.y, v3fCamOrientation.z);
}

////////////////////////////////////////////////////////////
void GOSkybox::Draw ( void ) {
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Binding of the cube map texture
  oTextures2DManager.BindTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, m_uiCubeMapID);
  glEnableClientState (GL_TEXTURE_COORD_ARRAY); ///< Activate texture coords array
  ActiveTex3DCoordsPointer ();

  Render (GL_TRIANGLE_STRIP);

  glDisableClientState (GL_TEXTURE_COORD_ARRAY);  ///< Deactivate texture coords array
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOSkybox::InitializeDatas ( void ) {
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
GLboolean GOSkybox::InitializeVBO ( void ) {
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
