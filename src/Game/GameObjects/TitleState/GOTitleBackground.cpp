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
#include <Game/GameObjects/TitleState/GOTitleBackground.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOTitleBackground::GOTitleBackground ( ST_Context& stContext ) :
  GameObject              (stContext),
  GameObject3D            (),
  m_uiCamera_ID           (0),
  m_oShaderProgramSkybox  (),
  m_oSkybox               ()
{
}

////////////////////////////////////////////////////////////
GOTitleBackground::~GOTitleBackground ( void ) {
  OGLManager& oOGLManager = GetOGLManager ();
  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    // Delete the shaders
    m_oShaderProgramSkybox.Delete ();
  }
  // Delete the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  oCameraManager.Erase (m_uiCamera_ID);
}

////////////////////////////////////////////////////////////
GLboolean GOTitleBackground::Initialize ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Getting of the OGLManager
  OGLManager& oOGLManager = GetOGLManager ();

  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    // Initialize the shaders
    if (!m_oShaderProgramSkybox.Load ("datas/shaders/vertex_skybox.glsl", "datas/shaders/fragment_skybox.glsl")) {
      // Debug : It will be necessary to process the errors, in the future.
    }
  }

  // Create a camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  m_uiCamera_ID = oCameraManager.CreateCamera ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (69.f, 0.1f, 128.f);

	// Skybox test
  glDisableClientState (GL_COLOR_ARRAY);  ///< If colors are not used, we must disable colors activated by SFML.
  glEnable (GL_TEXTURE_CUBE_MAP);
	m_oSkybox.SetCubeMapID (oTextures2DManager.LoadTexture (Textures2DManager::TexType::CUBEMAP_TEXTURE, "./datas/skybox/skybox", "png"));
  glDisable (GL_TEXTURE_CUBE_MAP);
	if (!m_oSkybox.InitializeVBO ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void GOTitleBackground::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Get the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Initialize the camera 3D
  oCamera.SetViewport (0, 0, gmMainWindow.GetWidth (), gmMainWindow.GetHeight ());
  oCamera.SetPerspective (69.f, 0.1f, 128.f);
}

////////////////////////////////////////////////////////////
void GOTitleBackground::Draw ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  OGLManager& oOGLManager = GetOGLManager ();

  if (oOGLManager.GetVersion () == 2) {         ///< OpenGL 2
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (69.0, static_cast<GLdouble> (gmMainWindow.GetWidth ())/static_cast<GLdouble> (gmMainWindow.GetHeight ()), 0.1, 128.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
  }

  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);

  // Skybox test
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

	if (oOGLManager.GetVersion () == 2) {         ///< OpenGL 2
    glPopMatrix ();
  } else if (oOGLManager.GetVersion () == 3) {  ///< OpenGL 3
    glUseProgram (0);
  }
}

////////////////////////////////////////////////////////////
GLboolean GOTitleBackground::Update ( void ) {
  // Update the camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (m_uiCamera_ID);
  // Rotate the camera 3D
  oCamera.RotationYFirstPerson (drimi::Radians (1.f/4.f));
  oCamera.ApplyMove ();

  OGLManager& oOGLManager = GetOGLManager ();
  if (oOGLManager.GetVersion () == 3) {         ///< OpenGL 3
    oCamera.FocaliseFirstPerson ();
    oCamera.UseMVP ();
  }

	return GL_FALSE;
}
