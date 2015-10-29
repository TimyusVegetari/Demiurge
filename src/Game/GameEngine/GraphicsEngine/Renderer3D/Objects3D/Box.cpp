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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Objects3D/Box.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Box::Box ( void ) :
  Object3D            (),
  VertexBufferObject  (),
  NormalBufferObject  (),
  ColorBufferObject   (),
  m_fWidth            (0),
  m_fHeight           (0),
  m_fDepth            (0)
{
}

////////////////////////////////////////////////////////////
Box::~Box ( void ) {
  DeleteBuffers ();
  m_oNormales.DeleteBuffer ();
  m_oColors.DeleteBuffer ();
  DeleteDatas ();
  m_oNormales.DeleteDatas ();
  m_oColors.DeleteDatas ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Box::InitializeDatas ( void ) {
  GLfloat fMidWidth   = m_fWidth/2.f,
          fMidHeight  = m_fHeight/2.f,
          fMidDepth   = m_fDepth/2.f;

  m_oVertex.SetDatas (
    new GLfloat[72] {
      // Face 0 : Bottom face
      -fMidWidth, -fMidHeight,  fMidDepth,
      -fMidWidth, -fMidHeight, -fMidDepth,
       fMidWidth, -fMidHeight, -fMidDepth,
       fMidWidth, -fMidHeight,  fMidDepth,
      // Face 1 : Back face
       fMidWidth,  fMidHeight, -fMidDepth,
       fMidWidth, -fMidHeight, -fMidDepth,
      -fMidWidth, -fMidHeight, -fMidDepth,
      -fMidWidth,  fMidHeight, -fMidDepth,
      // Face 2 : Right face
      -fMidWidth,  fMidHeight, -fMidDepth,
      -fMidWidth, -fMidHeight, -fMidDepth,
      -fMidWidth, -fMidHeight,  fMidDepth,
      -fMidWidth,  fMidHeight,  fMidDepth,
      // Face 3 : Front face
      -fMidWidth,  fMidHeight,  fMidDepth,
      -fMidWidth, -fMidHeight,  fMidDepth,
       fMidWidth, -fMidHeight,  fMidDepth,
       fMidWidth,  fMidHeight,  fMidDepth,
      // Face 4 : Left face
       fMidWidth,  fMidHeight,  fMidDepth,
       fMidWidth, -fMidHeight,  fMidDepth,
       fMidWidth, -fMidHeight, -fMidDepth,
       fMidWidth,  fMidHeight, -fMidDepth,
      // Face 5 : Top face
       fMidWidth,  fMidHeight,  fMidDepth,
       fMidWidth,  fMidHeight, -fMidDepth,
      -fMidWidth,  fMidHeight, -fMidDepth,
      -fMidWidth,  fMidHeight,  fMidDepth
    }, 72);

  m_oNormales.SetDatas (
    new GLfloat[72] {
      // Face 0 : Bottom face
       0.f, -1.f,  0.f,
       0.f, -1.f,  0.f,
       0.f, -1.f,  0.f,
       0.f, -1.f,  0.f,
      // Face 1 : Back face
       0.f,  0.f, -1.f,
       0.f,  0.f, -1.f,
       0.f,  0.f, -1.f,
       0.f,  0.f, -1.f,
      // Face 2 : Right face
      -1.f,  0.f,  0.f,
      -1.f,  0.f,  0.f,
      -1.f,  0.f,  0.f,
      -1.f,  0.f,  0.f,
      // Face 3 : Front face
       0.f,  0.f,  1.f,
       0.f,  0.f,  1.f,
       0.f,  0.f,  1.f,
       0.f,  0.f,  1.f,
      // Face 4 : Left face
       1.f,  0.f,  0.f,
       1.f,  0.f,  0.f,
       1.f,  0.f,  0.f,
       1.f,  0.f,  0.f,
      // Face 5 : Top face
       0.f,  1.f,  0.f,
       0.f,  1.f,  0.f,
       0.f,  1.f,  0.f,
       0.f,  1.f,  0.f
    }, 72);

  m_oColors.SetDatas (
    new GLfloat[72] {
      // Face 0 : Bottom face
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      // Face 1 : Back face
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      // Face 2 : Right face
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      // Face 3 : Front face
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      // Face 4 : Left face
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      // Face 5 : Top face
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f,
      1.f, 1.f, 1.f
    }, 72);

  m_oIndex.SetDatas (
    new GLuint[24] {
       0, 1, 2, 3,
       4, 5, 6, 7,
       8, 9,10,11,
      12,13,14,15,
      16,17,18,19,
      20,21,22,23
    }, 24);
}

////////////////////////////////////////////////////////////
GLboolean Box::InitializeVBO ( void ) {
  GLint iNoError = 1;

	InitializeDatas ();
  // Generating of the buffers
  iNoError &= m_oNormales.GenBufferID ();
  iNoError &= m_oColors.GenBufferID ();
  GenBuffers (iNoError);
  // Sending of the datas
  if (iNoError == 1) {
    iNoError &= m_oNormales.SendDatas ();
    iNoError &= m_oColors.SendDatas ();
    SendDatas (iNoError);
  }

  return static_cast<GLboolean> (iNoError);
}

////////////////////////////////////////////////////////////
void Box::Draw ( GLenum eMode ) {
  // Binding of the cube map texture
  glEnableClientState (GL_NORMAL_ARRAY);  ///< Activate normal coords array
  ActiveNormalesPointer ();
  glEnableClientState (GL_COLOR_ARRAY);   ///< Activate color coords array
  ActiveColorsPointer ();

  Render (eMode);

  glDisableClientState (GL_COLOR_ARRAY);  ///< Deactivate color coords array
  glDisableClientState (GL_NORMAL_ARRAY); ///< Deactivate normal coords array
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Box::SetDimensions ( GLfloat fWidth, GLfloat fHeight, GLfloat fDepth ) {
  m_fWidth  = fWidth;
  m_fHeight = fHeight;
  m_fDepth  = fDepth;
}

////////////////////////////////////////////////////////////
void Box::SetWidth ( GLfloat fWidth ) {
  m_fWidth  = fWidth;
}

////////////////////////////////////////////////////////////
void Box::SetHeight ( GLfloat fHeight ) {
  m_fHeight = fHeight;
}

////////////////////////////////////////////////////////////
void Box::SetDepth ( GLfloat fDepth ) {
  m_fDepth  = fDepth;
}

////////////////////////////////////////////////////////////
GLfloat Box::GetWidth ( void ) {
  return m_fWidth;
}

////////////////////////////////////////////////////////////
GLfloat Box::GetHeight ( void ) {
  return m_fHeight;
}

////////////////////////////////////////////////////////////
GLfloat Box::GetDepth ( void ) {
  return m_fDepth;
}
