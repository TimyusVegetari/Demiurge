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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/Tex3DCoordsArray.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Tex3DCoordsArray::Tex3DCoordsArray ( void ) :
  CGDatas (3, GL_ARRAY_BUFFER)
{
}

////////////////////////////////////////////////////////////
Tex3DCoordsArray::~Tex3DCoordsArray ( void ) {
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
glm::vec3 Tex3DCoordsArray::GetTex3DCoords ( GLsizei iDataPos ) {
  glm::vec3 v3fTex3DCoords;

  iDataPos *= m_iStep;
  if (iDataPos < m_iDatasArraySize) {
    v3fTex3DCoords.s = m_tDatasArray[iDataPos  ];
    v3fTex3DCoords.t = m_tDatasArray[iDataPos+1];
    v3fTex3DCoords.p = m_tDatasArray[iDataPos+2];
  } else {
    v3fTex3DCoords.s = 0.f;
    v3fTex3DCoords.t = 0.f;
    v3fTex3DCoords.p = 0.f;
  }

  return v3fTex3DCoords;
}
