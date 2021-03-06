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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/IndexArray.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
IndexArray::IndexArray ( GLuint* uiDatasArray, GLsizei iDatasArraySize ) :
  CGDatas (1, GL_ELEMENT_ARRAY_BUFFER)
{
  SetDatas (uiDatasArray, iDatasArraySize);
}

////////////////////////////////////////////////////////////
IndexArray::~IndexArray ( void ) {
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint IndexArray::GetIndex ( GLsizei iDataPos ) {
  GLuint uiIndex;

  if (iDataPos < m_iDatasArraySize) {
    uiIndex = m_tDatasArray[iDataPos  ];
  } else {
    uiIndex = 0;
  }

  return uiIndex;
}
