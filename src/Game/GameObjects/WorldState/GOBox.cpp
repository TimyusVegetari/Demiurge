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
#include <Game/GameObjects/WorldState/GOBox.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOBox::GOBox ( ST_Context& stContext ) :
  GameObject              (stContext),
//  GameObject3D            (),
  m_oShaderProgramClassic (),
  m_oBox                  ()
{
}

////////////////////////////////////////////////////////////
GOBox::~GOBox ( void ) {
  OGLManager& oOGLManager = GetOGLManager ();
  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    // Delete the shaders
    m_oShaderProgramClassic.Delete ();
  }
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOBox::Initialize ( void ) {
  std::cout << " >> GOBox initializing..." << std::endl;
  // Getting of the OGLManager
  OGLManager& oOGLManager = GetOGLManager ();

  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    // Initialize the shaders
    if (!m_oShaderProgramClassic.Load ("datas/shaders/vertex_wired.glsl", "datas/shaders/fragment_wired.glsl")) {
      // Debug : It will be necessary to process the errors, in the future.
    }
  }

	// Box test
	m_oBox.SetDimensions (1.f, 1.f, 1.f);
	m_oBox.InitializeVBO ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOBox::Draw ( const GLuint uiCameraID ) {
  // Getting of the needed systems
  OGLManager& oOGLManager = GetOGLManager ();

  // Camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (uiCameraID);

	if (oOGLManager.GetVersion () == 2) {         ///< OpenGL 2
    glPopMatrix ();

    gluLookAt (oCamera.GetPosition ().x, oCamera.GetPosition ().y, oCamera.GetPosition ().z,
               oCamera.GetGlobalFocalisation ().x, oCamera.GetGlobalFocalisation ().y, oCamera.GetGlobalFocalisation ().z,
               oCamera.GetOrientation ().x, oCamera.GetOrientation ().y, oCamera.GetOrientation ().z);
  } else if (oOGLManager.GetVersion () == 3) {  ///< OpenGL 3
    glUseProgram (m_oShaderProgramClassic.GetID ());
    GLint iMatrixLoc = glGetUniformLocation (m_oShaderProgramClassic.GetID (), "mvpMatrix");
    if (iMatrixLoc == -1)
      std::cout << "Error while getting the uniform '" << "mvpMatrix" << "'" << std::endl;
    glUniformMatrix4fv (iMatrixLoc, 1, GL_FALSE, glm::value_ptr (oCamera.GetGlobalMVP ()));
  }

  glEnable (GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  m_oBox.Draw (GL_QUADS);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDisable (GL_DEPTH_TEST);

  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    glUseProgram (0);
  }
}
