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
#include <Game/GameObjects/WorldState/GOSkybox.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOSkybox::GOSkybox ( ST_Context& stContext ) :
  GameObject              (stContext),
  GameObject3D            (),
  m_oShaderProgramSkybox  (),
  m_oSkybox               ()
{
}

////////////////////////////////////////////////////////////
GOSkybox::~GOSkybox ( void ) {
  OGLManager& oOGLManager = GetOGLManager ();
  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    // Delete the shaders
    m_oShaderProgramSkybox.Delete ();
  }
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOSkybox::Initialize ( void ) {
  std::cout << " >> GOSkybox initializing..." << std::endl;
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Getting of the OGLManager
  OGLManager& oOGLManager = GetOGLManager ();

  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    // Initialize the shaders
    if (!m_oShaderProgramSkybox.Load ("datas/shaders/vertex_skybox.glsl", "datas/shaders/fragment_skybox.glsl")) {
      // Debug : It will be necessary to process the errors, in the future.
    }
  }

	// Skybox test
  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors activated by SFML.
  glEnable (GL_TEXTURE_CUBE_MAP);
	m_oSkybox.SetCubeMapID (oTextures2DManager.LoadTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, "./datas/skybox/skybox", "png"));
  glDisable (GL_TEXTURE_CUBE_MAP);
	if (!m_oSkybox.InitializeVBO ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOSkybox::Draw ( const GLuint uiCameraID ) {
  // Getting of the needed systems
  OGLManager& oOGLManager = GetOGLManager ();

  // Camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (uiCameraID);

  if (oOGLManager.GetVersion () == 2) {         ///< OpenGL 2
    glPushMatrix ();
    glLoadIdentity ();
    m_oSkybox.UpdateMVP (oCamera.GetLocalFocalisation (), oCamera.GetOrientation ());
  } else if (oOGLManager.GetVersion () == 3) {  ///< OpenGL 3
    glUseProgram (m_oShaderProgramSkybox.GetID ());
    GLint iUnitTextureLoc = glGetUniformLocation (m_oShaderProgramSkybox.GetID (), "cubemap");
    if (iUnitTextureLoc == -1)
      std::cout << "Error while getting the uniform '" << "cubemap" << "'" << std::endl;
    glUniform1i (iUnitTextureLoc, 0);

    GLint iMatrixLoc = glGetUniformLocation (m_oShaderProgramSkybox.GetID (), "mvpMatrix");
    if (iMatrixLoc == -1)
      std::cout << "Error while getting the uniform '" << "mvpMatrix" << "'" << std::endl;
    glUniformMatrix4fv (iMatrixLoc, 1, GL_FALSE, glm::value_ptr (oCamera.GetLocalMVP ()));
  }

  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors at the place of SFML.
  glDepthMask (GL_FALSE);   ///< Disable drawing in the depth buffer
  glEnable (GL_TEXTURE_CUBE_MAP);

	m_oSkybox.Draw (m_stContext.m_oGraphicsEngine.GetTextures2DManager ());

  glDisable (GL_TEXTURE_CUBE_MAP);
  glDepthMask (GL_TRUE);    ///< Enable drawing in the depth buffer
}
