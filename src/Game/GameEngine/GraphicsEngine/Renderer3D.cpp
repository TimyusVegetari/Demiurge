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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Renderer3D.hpp
 * \brief Class for the renderer 3D of the graphics engine.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#include <Game/GameEngine/GraphicsEngine/Renderer3D.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer3D::Renderer3D ( void )
{
}

////////////////////////////////////////////////////////////
Renderer3D::~Renderer3D ( void ) {
  //DeleteCrossGI ();
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
/*void Renderer3D::LoadCrossGI ( void ) {
  // Buffers d'instances
  glUseProgram (m_gShadersManager.GetBoundingsShaderProgramID ());
  m_gMeshesManager.LoadCrossGI ();
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glUseProgram (0);
}*/

////////////////////////////////////////////////////////////
/*void Renderer3D::DeleteCrossGI ( void ) {
  // Buffers d'instances
  m_gMeshesManager.DeleteCrossGI ();
}*/

////////////////////////////////////////////////////////////
/*void Renderer3D::LoadCrossGI ( drimi::Vec3f v3fCenter, drimi::Vec4f v4fColor ) {
  m_gMeshesManager.LoadCrossGIList ( v3fCenter.x, v3fCenter.y, v3fCenter.z, v4fColor.x, v4fColor.y, v4fColor.z, v4fColor.w );
}*/

////////////////////////////////////////////////////////////
/*void Renderer3D::DrawCross ( drimi::Mat4x4f& m4fMVP ) {
  GLuint shaderProgramID;

  shaderProgramID = m_gShadersManager.GetBoundingsShaderProgramID ();
  glUseProgram (shaderProgramID);

  // Récupération de l'id de l'uniform
  GLint iMatrixID = glGetUniformLocation (shaderProgramID, "mvpMatrix");
  if (iMatrixID == -1)
    std::cout << "Error while getting the uniform 'mvpMatrix'" << std::endl;

  // Passage des centres des champs
  GLint iCrossCenterAttribLoc = m_gShadersManager.GetBoundingsCenterAttribLoc ();
  glBindBuffer (GL_ARRAY_BUFFER, m_gMeshesManager.GetCrossCenterID ());
  glEnableVertexAttribArray (iCrossCenterAttribLoc);
  glVertexAttribPointer (iCrossCenterAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, (const GLvoid*)(0));
  glVertexAttribDivisorARB (iCrossCenterAttribLoc, 1);

  // Passage des couleurs des champs
  GLint iCrossColorAttribLoc = m_gShadersManager.GetBoundingsColorAttribLoc ();
  glBindBuffer (GL_ARRAY_BUFFER, m_gMeshesManager.GetCrossColorID ());
  glEnableVertexAttribArray (iCrossColorAttribLoc);
  glVertexAttribPointer (iCrossColorAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const GLvoid*)(0));
  glVertexAttribDivisorARB (iCrossColorAttribLoc, 1);

  // Passage de la matrice au shader
  glUniformMatrix4fv (iMatrixID, 1, GL_FALSE, drimi::ValuePtr (m4fMVP));

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_COLOR_MATERIAL);

  m_gMeshesManager.DrawCrossMesh ();

  glDisable (GL_COLOR_MATERIAL);
  glDisable (GL_DEPTH_TEST);

  glUseProgram (0);
}*/

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////
