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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Shaders/ShaderProgram.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram ( void ) :
  m_gVertexShader   (),
  m_gFragmentShader (),
  m_uiID            (0)
{
}

////////////////////////////////////////////////////////////
ShaderProgram::~ShaderProgram ( void ) {
  Delete ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean ShaderProgram::Load ( const std::string szVertexName, const std::string szFragmentName ) {
  // Loading of vertex and fragment shaders
  if (m_gVertexShader.Load (GL_VERTEX_SHADER, szVertexName) && m_gFragmentShader.Load (GL_FRAGMENT_SHADER, szFragmentName)) {
    m_uiID = glCreateProgram ();

    glAttachShader (m_uiID, m_gVertexShader.GetID ());
    glAttachShader (m_uiID, m_gFragmentShader.GetID ());

    glLinkProgram (m_uiID);

    return CheckCompilation ();
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void ShaderProgram::EnableShaderProgram ( void ) {
  glUseProgram (m_uiID);
}

////////////////////////////////////////////////////////////
void ShaderProgram::DisableShaderProgram ( void ) {
  glUseProgram (0);
}

////////////////////////////////////////////////////////////
void ShaderProgram::SendCurrentColor ( const GLchar* szName, const GLfloat* fColor ) {
  GLint iColorLoc = glGetUniformLocation (m_uiID, szName);
  if (iColorLoc == -1)
    std::cout << "Error while getting the uniform '" << szName << "'" << std::endl;
  glUniform4fv (iColorLoc, 1, fColor);
}

////////////////////////////////////////////////////////////
void ShaderProgram::SendUnitTexture ( const GLchar* szName, GLint iV0 ) {
  GLint iUnitTextureLoc = glGetUniformLocation (m_uiID, szName);
  if (iUnitTextureLoc == -1)
    std::cout << "Error while getting the uniform '" << szName << "'" << std::endl;
  glUniform1i (iUnitTextureLoc, iV0);
}

////////////////////////////////////////////////////////////
void ShaderProgram::SendCurrentMatrix ( const GLchar* szName, glm::mat4& m4fMVP ) {
  GLint iMatrixLoc = glGetUniformLocation (m_uiID, szName);
  if (iMatrixLoc == -1)
    std::cout << "Error while getting the uniform '" << szName << "'" << std::endl;
  glUniformMatrix4fv (iMatrixLoc, 1, GL_FALSE, glm::value_ptr (m4fMVP));
}

////////////////////////////////////////////////////////////
void ShaderProgram::Delete ( void ) {
  if (m_uiID != 0) {
    glDetachShader (m_uiID, m_gFragmentShader.GetID ());
    glDetachShader (m_uiID, m_gVertexShader.GetID ());
    glDeleteProgram (m_uiID);
    m_uiID = 0;
  }

  // Deleting of the shaders
  m_gFragmentShader.Delete ();
  m_gVertexShader.Delete ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint ShaderProgram::GetID ( void ) {
  return m_uiID;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean ShaderProgram::CheckCompilation ( void ) {
  GLint iCompilationStatus = 0;

  glGetProgramiv (m_uiID, GL_LINK_STATUS, &iCompilationStatus);
  if (iCompilationStatus != GL_TRUE) {
    std::cout << "Error : Compilation of a shader program !" << std::endl;
    // What is the cause of the failure ?
    GLint iLogLength = 0;
    GLchar* cLog = NULL;

    glGetProgramiv (m_uiID, GL_INFO_LOG_LENGTH, &iLogLength);
    cLog = new GLchar[iLogLength];
    if (cLog == NULL) {
      std::cout << "Allocation memory error for the log of the shader program compilation !" << std::endl;
      return GL_FALSE;
    }
    // Getting and display of the log
    glGetProgramInfoLog (m_uiID, iLogLength, &iLogLength, cLog);
    std::cout << cLog << std::endl;
    delete[] cLog;

    return GL_FALSE;
  }

  return GL_TRUE;
}
