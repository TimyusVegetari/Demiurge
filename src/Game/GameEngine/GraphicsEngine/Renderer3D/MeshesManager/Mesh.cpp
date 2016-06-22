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
// A big part of the code in this file is inspired by the book
// "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/Renderer3D/MeshesManager/Mesh.hpp>
#include <DRIMI/Mathematics/Methods/ToString.hpp>

////////////////////////////////////////////////////////////
Mesh::Mesh ( void ) :
  m_szTypeName          ("no mesh"),
  m_oVertexBufferObject (NULL, 0,
                         NULL, 0),
  m_oNormalBufferObject (NULL, 0)
{
}

////////////////////////////////////////////////////////////
Mesh::Mesh ( std::string szTypeName,
             GLfloat* fVertexDatasArray, GLsizei iVertexDatasArraySize,
             GLuint* uiIndexDatasArray, GLsizei iIndexDatasArraySize,
             GLfloat* fNormalDatasArray, GLsizei iNormalDatasArraySize ) :
  m_szTypeName          (szTypeName),
  m_oVertexBufferObject (fVertexDatasArray, iVertexDatasArraySize,
                         uiIndexDatasArray, iIndexDatasArraySize),
  m_oNormalBufferObject (fNormalDatasArray, iNormalDatasArraySize)
{
}

////////////////////////////////////////////////////////////
Mesh::~Mesh ( void ) {
  m_oVertexBufferObject.DeleteDatas ();
  m_oVertexBufferObject.DeleteBuffers ();
  m_oNormalBufferObject.DeleteDatas ();
  m_oNormalBufferObject.DeleteBuffers ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Mesh::Initialize ( void ) {
  GLboolean bNoError = GL_TRUE;

  // Generating of the buffers
  bNoError &= m_oVertexBufferObject.GenBuffers (GL_FALSE);
  bNoError &= m_oNormalBufferObject.GenBuffers (GL_FALSE);

  // Sending of the datas
  if (bNoError) {
    bNoError &= m_oVertexBufferObject.SendDatas (GL_FALSE);
    bNoError &= m_oNormalBufferObject.SendDatas (GL_FALSE);
    if (!bNoError)
      std::cout << "Error in VBO : Sending of datas for " << m_szTypeName << " to the graphics card impossible !" << std::endl;
  } else
    std::cout << "Error in VBO : Generating identifier of datas for " << m_szTypeName << " to the graphics card impossible !" << std::endl;

  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

  return bNoError;
}

////////////////////////////////////////////////////////////
void Mesh::Draw ( GLenum eMode ) {
  // Binding of the cube map texture
  glEnableClientState (GL_NORMAL_ARRAY);  ///< Activate normal coords array
  m_oNormalBufferObject.ActiveNormalesPointer ();

  m_oVertexBufferObject.Render (eMode);

  glDisableClientState (GL_NORMAL_ARRAY); ///< Deactivate normal coords array
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
std::string Mesh::GetTypeName ( void ) {
	return m_szTypeName;
}

////////////////////////////////////////////////////////////
GLsizei Mesh::GetVertexDatasLength ( void ) {
  return m_oVertexBufferObject.GetVertexDatasLength ();
}

////////////////////////////////////////////////////////////
GLsizei Mesh::GetVertexDatasSize ( void ) {
  return m_oVertexBufferObject.GetVertexDatasSize ();
}

////////////////////////////////////////////////////////////
GLint Mesh::GetVertexStep ( void ) {
  return m_oVertexBufferObject.GetVertexStep ();
}

////////////////////////////////////////////////////////////
const GLfloat* Mesh::GetVertexDatas ( void ) {
  return m_oVertexBufferObject.GetVertexDatas ();
}

////////////////////////////////////////////////////////////
GLsizei Mesh::GetIndexDatasLength ( void ) {
  return m_oVertexBufferObject.GetIndexDatasLength ();
}

////////////////////////////////////////////////////////////
GLsizei Mesh::GetIndexDatasSize ( void ) {
  return m_oVertexBufferObject.GetIndexDatasSize ();
}

////////////////////////////////////////////////////////////
GLint Mesh::GetIndexStep ( void ) {
  return m_oVertexBufferObject.GetIndexStep ();
}

////////////////////////////////////////////////////////////
const GLuint* Mesh::GetIndexDatas ( void ) {
  return m_oVertexBufferObject.GetIndexDatas ();
}

////////////////////////////////////////////////////////////
GLsizei Mesh::GetNormalDatasLength ( void ) {
  return m_oNormalBufferObject.GetNormalDatasLength ();
}

////////////////////////////////////////////////////////////
GLsizei Mesh::GetNormalDatasSize ( void ) {
  return m_oNormalBufferObject.GetNormalDatasSize ();
}

////////////////////////////////////////////////////////////
GLint Mesh::GetNormalStep ( void ) {
  return m_oNormalBufferObject.GetNormalStep ();
}

////////////////////////////////////////////////////////////
const GLfloat* Mesh::GetNormalDatas ( void ) {
  return m_oNormalBufferObject.GetNormalDatas ();
}

////////////////////////////////////////////////////////////
std::string Mesh::ToStringVertex ( GLuint uiPosition ) {
	const GLfloat* fVertexDatas = m_oVertexBufferObject.GetVertexDatas ();
	if (fVertexDatas != NULL)
    return drimi::ToString (fVertexDatas[uiPosition  ])+std::string (" ")+drimi::ToString (fVertexDatas[uiPosition+1])+std::string (" ")+drimi::ToString (fVertexDatas[uiPosition+2]);
  else
    return std::string ("none");
}

////////////////////////////////////////////////////////////
std::string Mesh::ToStringNormal ( GLuint uiPosition ) {
	const GLfloat* fNormalDatas = m_oNormalBufferObject.GetNormalDatas ();
	if (fNormalDatas != NULL)
    return drimi::ToString (fNormalDatas[uiPosition  ])+std::string (" ")+drimi::ToString (fNormalDatas[uiPosition+1])+std::string (" ")+drimi::ToString (fNormalDatas[uiPosition+2]);
  else
    return std::string ("none");
}
