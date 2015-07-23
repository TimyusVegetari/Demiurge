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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/VertexBufferObject.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
VertexBufferObject::VertexBufferObject ( void ) :
  m_szTypeName  (""),
  m_oVertex     (),
  m_oIndex      ()
{
}

////////////////////////////////////////////////////////////
VertexBufferObject::~VertexBufferObject ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void VertexBufferObject::GenBuffers ( GLint &iNoError ) {
  iNoError &= m_oVertex.GenBufferID ();
  iNoError &= m_oIndex.GenBufferID ();

  if (iNoError == 0)
    std::cout << "Error in VBO : Sending of datas for " << m_szTypeName << " to the graphics card impossible !" << std::endl;
}

////////////////////////////////////////////////////////////
void VertexBufferObject::SendDatas ( GLint &iNoError ) {
  iNoError &= m_oVertex.SendDatas ();
  iNoError &= m_oIndex.SendDatas ();

  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

  if (iNoError == 0)
    std::cout << "Error in VBO : Sending of datas for " << m_szTypeName << " to the graphics card impossible !" << std::endl;
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
std::string VertexBufferObject::GetTypeName ( void ) {
  return m_szTypeName;
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
    if (iIndexArraySize != 0)
      glDrawElements (eMode, iIndexArraySize, GL_UNSIGNED_INT, 0);

    // Disable buffers
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glDisableClientState (GL_VERTEX_ARRAY);         ///< Deactivate vertex array
  }
}
