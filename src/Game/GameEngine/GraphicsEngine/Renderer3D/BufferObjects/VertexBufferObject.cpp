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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/VertexBufferObject.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
VertexBufferObject::VertexBufferObject ( GLfloat* fVertexDatasArray, GLsizei iVertexDatasArraySize,
                                         GLuint* uiIndexDatasArray, GLsizei iIndexDatasArraySize ) :
  m_oVertex     (fVertexDatasArray, iVertexDatasArraySize),
  m_oIndex      (uiIndexDatasArray, iIndexDatasArraySize)
{
}

////////////////////////////////////////////////////////////
VertexBufferObject::~VertexBufferObject ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::GenBuffers ( GLboolean bCloseBinding ) {
  GLboolean bNoError = GL_TRUE;

  bNoError &= m_oVertex.GenBufferID ();
  bNoError &= m_oIndex.GenBufferID ();

  if (bCloseBinding) {
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  return bNoError;
}

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::SendDatas ( GLboolean bCloseBinding ) {
  GLboolean bNoError = GL_TRUE;

  bNoError &= m_oVertex.SendDatas ();
  bNoError &= m_oIndex.SendDatas ();

  if (bCloseBinding) {
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  return bNoError;
}

////////////////////////////////////////////////////////////
void VertexBufferObject::DeleteBuffers ( void ) {
  m_oVertex.DeleteBuffer ();
  m_oIndex.DeleteBuffer ();
}

////////////////////////////////////////////////////////////
void VertexBufferObject::DeleteDatas ( void ) {
  m_oVertex.DeleteDatas ();
  m_oIndex.DeleteDatas ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLsizei VertexBufferObject::GetVertexDatasLength ( void ) {
  return m_oVertex.GetDatasLength ();
}

////////////////////////////////////////////////////////////
GLsizei VertexBufferObject::GetVertexDatasSize ( void ) {
  return m_oVertex.GetDatasSize ();
}

////////////////////////////////////////////////////////////
GLint VertexBufferObject::GetVertexStep ( void ) {
  return m_oVertex.GetStep ();
}

////////////////////////////////////////////////////////////
const GLfloat* VertexBufferObject::GetVertexDatas ( void ) {
  return m_oVertex.GetDatas ();
}

////////////////////////////////////////////////////////////
GLsizei VertexBufferObject::GetIndexDatasLength ( void ) {
  return m_oIndex.GetDatasLength ();
}

////////////////////////////////////////////////////////////
GLsizei VertexBufferObject::GetIndexDatasSize ( void ) {
  return m_oIndex.GetDatasSize ();
}

////////////////////////////////////////////////////////////
GLint VertexBufferObject::GetIndexStep ( void ) {
  return m_oIndex.GetStep ();
}

////////////////////////////////////////////////////////////
const GLuint* VertexBufferObject::GetIndexDatas ( void ) {
  return m_oIndex.GetDatas ();
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::ActiveVertexPointer ( void ) {
  if (m_oVertex.BindBuffer ()) {
    GLint iVertexStep = m_oVertex.GetStep ();
    GLsizei iDatasSize = m_oVertex.GetDatasSize ();

    if (iVertexStep != 0 && iDatasSize != 0) {
      glVertexPointer (iVertexStep, GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      if (glGetError () == GL_INVALID_ENUM)
        std::cout << "OpenGL Error during the call of the vertex pointer in the graphics card !" << std::endl;
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLsizei VertexBufferObject::BindIndex ( void ) {
  if (m_oIndex.BindBuffer ()) {
    return m_oIndex.GetDatasLength ();
  }
  return 0;
}

////////////////////////////////////////////////////////////
void VertexBufferObject::Render ( GLenum eMode ) {
  // Enable buffers
  if (m_oVertex.GetStep () != 0) {
    glEnableClientState (GL_VERTEX_ARRAY);          ///< Activate vertex coords array
    ActiveVertexPointer ();

    // Draw with index
    GLsizei iIndexArraySize = BindIndex ();
    if (iIndexArraySize != 0) {
      glDrawElements (eMode, iIndexArraySize, GL_UNSIGNED_INT, 0);
    }

    // Disable buffers
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glDisableClientState (GL_VERTEX_ARRAY);         ///< Deactivate vertex array
  }
}
