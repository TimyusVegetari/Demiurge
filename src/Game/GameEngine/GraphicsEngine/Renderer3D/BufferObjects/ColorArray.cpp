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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/ColorArray.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
ColorArray::ColorArray ( void ) :
  CGDatas (4, GL_ARRAY_BUFFER)
{
}

////////////////////////////////////////////////////////////
ColorArray::~ColorArray ( void ) {
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
glm::vec4 ColorArray::GetColor ( GLsizei iDataPos ) {
  glm::vec4 v4fColor;

  iDataPos *= m_iStep;
  if (iDataPos < m_iDatasArraySize) {
    v4fColor.r = m_tDatasArray[iDataPos  ];
    v4fColor.g = m_tDatasArray[iDataPos+1];
    v4fColor.b = m_tDatasArray[iDataPos+2];
    v4fColor.a = m_tDatasArray[iDataPos+3];
  } else {
    v4fColor.r = 1.f;
    v4fColor.g = 1.f;
    v4fColor.b = 1.f;
    v4fColor.a = 1.f;
  }

  return v4fColor;
}
