////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2016 Acroute Anthony (ant110283@hotmail.fr)
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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/NormalBufferObject.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
NormalBufferObject::NormalBufferObject ( GLfloat* fNormalDatasArray, GLsizei iNormalDatasArraySize ) :
  m_oNormales (fNormalDatasArray, iNormalDatasArraySize)
{
}

////////////////////////////////////////////////////////////
NormalBufferObject::~NormalBufferObject ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean NormalBufferObject::GenBuffers ( GLboolean bCloseBinding ) {
  GLboolean bError = m_oNormales.GenBufferID ();
  if (bCloseBinding) {
    glBindBuffer (GL_ARRAY_BUFFER, 0);
  }
  return bError;
}

////////////////////////////////////////////////////////////
GLboolean NormalBufferObject::SendDatas ( GLboolean bCloseBinding ) {
  GLboolean bError = m_oNormales.SendDatas ();
  if (bCloseBinding) {
    glBindBuffer (GL_ARRAY_BUFFER, 0);
  }
  return bError;
}

////////////////////////////////////////////////////////////
void NormalBufferObject::DeleteBuffers ( void ) {
  m_oNormales.DeleteBuffer ();
}

////////////////////////////////////////////////////////////
void NormalBufferObject::DeleteDatas ( void ) {
  m_oNormales.DeleteDatas ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLsizei NormalBufferObject::GetNormalDatasLength ( void ) {
  return m_oNormales.GetDatasLength ();
}

////////////////////////////////////////////////////////////
GLsizei NormalBufferObject::GetNormalDatasSize ( void ) {
  return m_oNormales.GetDatasSize ();
}

////////////////////////////////////////////////////////////
GLint NormalBufferObject::GetNormalStep ( void ) {
  return m_oNormales.GetStep ();
}

////////////////////////////////////////////////////////////
const GLfloat* NormalBufferObject::GetNormalDatas ( void ) {
  return m_oNormales.GetDatas ();
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean NormalBufferObject::ActiveNormalesPointer ( void ) {
  if (m_oNormales.BindBuffer ()) {
    GLsizei iDatasSize = m_oNormales.GetDatasSize ();

    if (iDatasSize != 0) {
      glNormalPointer (GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}
