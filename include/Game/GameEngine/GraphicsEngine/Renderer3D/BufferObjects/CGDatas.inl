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
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
CGDatas<T>::CGDatas ( GLint iStep, GLenum eTarget ) :
  m_uiBufferID        (0),
  m_tDatasArray       (NULL),
  m_iDatasArraySize   (0),
  m_iStep             (iStep),
  m_eTarget           (eTarget)
{
}

////////////////////////////////////////////////////////////
template <typename T>
CGDatas<T>::~CGDatas ( void ) {
  if (m_tDatasArray != NULL) {
    delete[] m_tDatasArray;
  }
  if (m_uiBufferID != 0) {
    glDeleteBuffers (1, &m_uiBufferID);
    // Debug : It will be necessary to check OpenGL error, in the future.
  }
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
GLboolean CGDatas<T>::GenBufferID ( void ) {
  if (m_uiBufferID == 0) {
    glGenBuffers (1, &m_uiBufferID);
    return GL_TRUE;
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
template <typename T>
GLboolean CGDatas<T>::BindBuffer ( void ) {
  if (m_uiBufferID != 0) {
    glBindBuffer (m_eTarget, m_uiBufferID);
    // Debug : It will be necessary to check OpenGL error, in the future.
    if (glGetError () == GL_INVALID_ENUM)
      std::cout << "OpenGL Error during the bind of the buffer in the graphics card !" << std::endl;
    return GL_TRUE;
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
template <typename T>
void CGDatas<T>::SetDatas ( T* tDatasArray, GLsizei iDatasArraySize ) {
  m_iDatasArraySize   = iDatasArraySize;
  m_tDatasArray       = tDatasArray;
}

////////////////////////////////////////////////////////////
template <typename T>
GLboolean CGDatas<T>::SendDatas ( void ) {
  if (m_uiBufferID != 0) {
    glBindBuffer (m_eTarget, m_uiBufferID);
    if (m_iDatasArraySize != 0 && m_tDatasArray != NULL) {
      glBufferData (m_eTarget, m_iDatasArraySize * static_cast<GLsizei> (sizeof (T)), m_tDatasArray, GL_STATIC_DRAW);
      // Debug : It will be necessary to check OpenGL error, in the future.
      if (glGetError () == GL_INVALID_ENUM)
        std::cout << "OpenGL Error during the send of datas in the graphics card !" << std::endl;
    //  delete[] m_tDatasArray;
    //  m_tDatasArray = NULL;

      return GL_TRUE;
    }
  }
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
template <typename T>
void CGDatas<T>::DeleteDatas ( void ) {
  if (m_tDatasArray != NULL) {
    delete[] m_tDatasArray;
    m_tDatasArray = NULL;
  }
  m_iDatasArraySize   = 0;
  m_iStep             = 0;
}

////////////////////////////////////////////////////////////
template <typename T>
void CGDatas<T>::DeleteBuffer ( void ) {
  if (m_uiBufferID != 0) {
    glDeleteBuffers (1, &m_uiBufferID);
    // Debug : It will be necessary to check OpenGL error, in the future.
    m_uiBufferID = 0;
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
GLuint CGDatas<T>::GetBufferID ( void ) {
  return m_uiBufferID;
}

////////////////////////////////////////////////////////////
template <typename T>
GLsizei CGDatas<T>::GetDatasLength ( void ) {
  return m_iDatasArraySize;
}

////////////////////////////////////////////////////////////
template <typename T>
const T* CGDatas<T>::GetDatas ( void ) {
  return m_tDatasArray;
}

////////////////////////////////////////////////////////////
template <typename T>
GLsizei CGDatas<T>::GetDatasSize ( void ) {
  return m_iStep * static_cast<GLint> (sizeof (T));
}

////////////////////////////////////////////////////////////
template <typename T>
GLint CGDatas<T>::GetStep ( void ) {
  return m_iStep;
}

////////////////////////////////////////////////////////////
template <typename T>
GLenum CGDatas<T>::GetTarget ( void ) {
  return m_eTarget;
}
