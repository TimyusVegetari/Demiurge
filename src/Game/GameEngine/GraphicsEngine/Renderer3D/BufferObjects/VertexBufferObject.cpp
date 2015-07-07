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
  m_oNormales   (),
  m_oColors     (),
  m_oTextures   (),
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
GLboolean VertexBufferObject::InitializeBuffers ( void ) {
  GLint iNoError = 0;

  // Génération des ids
  iNoError &= m_oVertex.GenBufferID ();
  iNoError &= m_oNormales.GenBufferID ();
  iNoError &= m_oColors.GenBufferID ();
  iNoError &= m_oTextures.GenBufferID ();
  iNoError &= m_oIndex.GenBufferID ();

  if (iNoError == 1) {
    iNoError &= m_oVertex.SendDatas ();
    iNoError &= m_oNormales.SendDatas ();
    iNoError &= m_oColors.SendDatas ();
    iNoError &= m_oTextures.SendDatas ();
    iNoError &= m_oIndex.SendDatas ();
    if (iNoError == 0) {
      std::cout << "Error in VBO : Sending of datas for " << m_szTypeName << " to the graphics card impossible !" << std::endl;
      return GL_FALSE;
    }

    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
  } else {
    std::cout << "Error in VBO : Generation of buffer identifiers for " << m_szTypeName << " impossible !" << std::endl;
    return GL_FALSE;
  }

  return static_cast<GLboolean> (iNoError);
}

////////////////////////////////////////////////////////////
void VertexBufferObject::Render ( GLuint uiMask ) {
  // Enable buffers
  if (m_oVertex.GetStep () != 0) {
    m_oVertex.BindBuffer ();
    if ((uiMask & VBO_NORMALES) == 1)
      m_oNormales.BindBuffer ();
    if ((uiMask & VBO_COLORS) == 2)
      m_oColors.BindBuffer ();
    if ((uiMask & VBO_TEXTURES) == 4)
      m_oTextures.BindBuffer ();

    // Draw with index
    GLsizei iIndexArraySize = BindIndex ();
    if (iIndexArraySize != 0)
      glDrawElements (GL_QUADS, iIndexArraySize, GL_UNSIGNED_INT, 0);

    // Disable buffers
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
  }
}

////////////////////////////////////////////////////////////
void VertexBufferObject::DeleteBuffers ( void ) {
  m_oIndex.DeleteBuffer ();
  m_oTextures.DeleteBuffer ();
  m_oColors.DeleteBuffer ();
  m_oNormales.DeleteBuffer ();
  m_oVertex.DeleteBuffer ();
}

////////////////////////////////////////////////////////////
void VertexBufferObject::DeleteDatas ( void ) {
  m_oVertex.DeleteDatas ();
  m_oNormales.DeleteDatas ();
  m_oColors.DeleteDatas ();
  m_oTextures.DeleteDatas ();
  m_oIndex.DeleteDatas ();
}

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::ActiveVertexPointer ( void ) {
  if (m_oVertex.BindBuffer ()) {
    GLint uiVertexStep = m_oVertex.GetStep ();
    GLsizei iDatasSize = m_oVertex.GetDatasSize ();

    if (uiVertexStep != 0 && iDatasSize != 0) {
      glVertexPointer (uiVertexStep, GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::ActiveNormalesPointer ( void ) {
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

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::ActiveColorsPointer ( void ) {
  if (m_oColors.BindBuffer ()) {
    GLint uiColorsStep = m_oColors.GetStep ();
    GLsizei iDatasSize = m_oColors.GetDatasSize ();

    if (uiColorsStep != 0 && iDatasSize != 0) {
      glColorPointer (uiColorsStep, GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::ActiveTexturesPointer ( void ) {
  if (m_oTextures.BindBuffer ()) {
    GLint uiTexturesStep = m_oTextures.GetStep ();
    GLsizei iDatasSize = m_oTextures.GetDatasSize ();

    if (uiTexturesStep != 0 && iDatasSize != 0) {
      glTexCoordPointer (uiTexturesStep, GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLsizei VertexBufferObject::BindIndex ( void ) {
  if (m_oIndex.BindBuffer ()) {
    return m_oIndex.GetDatasSize ();
  }
  return 0;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
std::string VertexBufferObject::GetTypeName ( void ) {
  return m_szTypeName;
}
