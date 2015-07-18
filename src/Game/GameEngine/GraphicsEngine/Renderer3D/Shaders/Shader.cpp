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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Shaders/Shader.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Shader::Shader ( void ) :
  m_uiID    (0),
  m_eType   (0)
{
}

////////////////////////////////////////////////////////////
Shader::~Shader ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Shader::Load ( const GLenum eType, const std::string szFileName ) {
  File fFile;

  m_eType = eType;
  if (fFile.Open (szFileName)) {
    fFile.Read ();
    fFile.Close ();

    const GLchar* cShaderSource = fFile.GetBuffer ().c_str ();
    GLint iShaderSize = static_cast<GLint> (fFile.GetBufferSize ())+1; // +1 for the end string character '\0'

    m_uiID = glCreateShader (eType);
    glShaderSource (m_uiID, 1, &cShaderSource, &iShaderSize);
    glCompileShader (m_uiID);

    return CheckCompilation ();
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void Shader::Delete ( void ) {
  if (m_uiID != 0) {
    glDeleteShader (m_uiID);
    m_uiID = 0;
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint Shader::GetID ( void ) {
  return m_uiID;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Shader::CheckCompilation ( void ) {
  GLint iCompilationStatus = 0;

  glGetShaderiv (m_uiID, GL_COMPILE_STATUS, &iCompilationStatus);
  if (iCompilationStatus != GL_TRUE) {
    std::cout << "Error : Compilation of ";
    if (m_eType == GL_VERTEX_SHADER)
      std::cout << "the vertex shader :" << std::endl;
    else if (m_eType == GL_FRAGMENT_SHADER)
      std::cout << "the fragment shader :" << std::endl;
    // What is the cause of the failure ?
    GLint iLogLength = 0;
    GLchar* cLog = NULL;

    glGetShaderiv (m_uiID, GL_INFO_LOG_LENGTH, &iLogLength);
    cLog = new GLchar[iLogLength];
    if (cLog == NULL) {
      std::cout << "Allocation memory error for the log of the shader compilation !" << std::endl;
      return GL_FALSE;
    }
    // Getting and display of the log
    glGetShaderInfoLog (m_uiID, iLogLength, &iLogLength, cLog);
    std::cout << cLog << std::endl;
    delete[] cLog;

    return GL_FALSE;
  }

  return GL_TRUE;
}
