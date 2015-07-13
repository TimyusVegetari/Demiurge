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
GLboolean VertexBufferObject::InitializeBuffers ( GLuint uiMask ) {
  GLint iNoError = 1;

  // Génération des ids
  iNoError &= m_oVertex.GenBufferID ();
  if ((uiMask & VBO_NORMALES) == 1)
    iNoError &= m_oNormales.GenBufferID ();
  if ((uiMask & VBO_COLORS) == 2)
    iNoError &= m_oColors.GenBufferID ();
  if ((uiMask & VBO_TEXTURES) == 4)
    iNoError &= m_oTextures.GenBufferID ();
  iNoError &= m_oIndex.GenBufferID ();

  if (iNoError == 1) {
    iNoError &= m_oVertex.SendDatas ();
    if ((uiMask & VBO_NORMALES) == 1)
      iNoError &= m_oNormales.SendDatas ();
    if ((uiMask & VBO_COLORS) == 2)
      iNoError &= m_oColors.SendDatas ();
    if ((uiMask & VBO_TEXTURES) == 4)
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
void VertexBufferObject::Render ( GLuint uiMask, GLenum eMode ) {
  // Enable buffers
  if (m_oVertex.GetStep () != 0) {
    glEnableClientState (GL_VERTEX_ARRAY);          ///< Activate vertex coords array
    ActiveVertexPointer ();
    if ((uiMask & VBO_NORMALES) == 1) {
      glEnableClientState (GL_NORMAL_ARRAY);        ///< Activate normal coords array
      ActiveNormalesPointer ();
    }
    if ((uiMask & VBO_COLORS) == 2) {
      glEnableClientState (GL_COLOR_ARRAY);         ///< Activate color coords array
      ActiveColorsPointer ();
    }
    if ((uiMask & VBO_TEXTURES) == 4) {
      glEnableClientState (GL_TEXTURE_COORD_ARRAY); ///< Activate texture coords array
      ActiveTexturesPointer ();
    }

    // Draw with index
    GLsizei iIndexArraySize = BindIndex ();
    if (iIndexArraySize != 0)
      glDrawElements (eMode, iIndexArraySize, GL_UNSIGNED_INT, 0);

    if ((uiMask & VBO_TEXTURES) == 4)
      glDisableClientState (GL_TEXTURE_COORD_ARRAY);  ///< Deactivate texture coords array
    if ((uiMask & VBO_COLORS) == 2)
      glDisableClientState (GL_COLOR_ARRAY);          ///< Deactivate color coords array
    if ((uiMask & VBO_NORMALES) == 1)
      glDisableClientState (GL_NORMAL_ARRAY);         ///< Deactivate normal coords array
    glDisableClientState (GL_VERTEX_ARRAY);         ///< Deactivate vertex array

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
    GLint iColorsStep = m_oColors.GetStep ();
    GLsizei iDatasSize = m_oColors.GetDatasSize ();

    if (iColorsStep != 0 && iDatasSize != 0) {
      glColorPointer (iColorsStep, GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean VertexBufferObject::ActiveTexturesPointer ( void ) {
  if (m_oTextures.BindBuffer ()) {
    GLint iTexturesStep = m_oTextures.GetStep ();
    GLsizei iDatasSize = m_oTextures.GetDatasSize ();

    if (iTexturesStep != 0 && iDatasSize != 0) {
      glTexCoordPointer (iTexturesStep, GL_FLOAT, iDatasSize, 0);
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
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
std::string VertexBufferObject::GetTypeName ( void ) {
  return m_szTypeName;
}
