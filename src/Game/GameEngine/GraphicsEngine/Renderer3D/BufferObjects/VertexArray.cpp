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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/VertexArray.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
VertexArray::VertexArray ( GLfloat* fDatasArray, GLsizei iDatasArraySize ) :
  CGDatas (3, GL_ARRAY_BUFFER)
{
  SetDatas (fDatasArray, iDatasArraySize);
}

////////////////////////////////////////////////////////////
VertexArray::~VertexArray ( void ) {
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
glm::vec3 VertexArray::GetVertex ( GLsizei iDataPos ) {
  glm::vec3 v3fVertex;

  iDataPos *= m_iStep;
  if (iDataPos < m_iDatasArraySize) {
    v3fVertex.x = m_tDatasArray[iDataPos  ];
    v3fVertex.y = m_tDatasArray[iDataPos+1];
    v3fVertex.z = m_tDatasArray[iDataPos+2];
  } else {
    v3fVertex.x = 0.f;
    v3fVertex.y = 0.f;
    v3fVertex.z = 0.f;
  }

  return v3fVertex;
}
