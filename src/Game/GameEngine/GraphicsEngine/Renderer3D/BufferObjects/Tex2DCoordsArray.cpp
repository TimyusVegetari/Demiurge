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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/Tex2DCoordsArray.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Tex2DCoordsArray::Tex2DCoordsArray ( void ) :
  CGDatas (2, GL_ARRAY_BUFFER)
{
}

////////////////////////////////////////////////////////////
Tex2DCoordsArray::~Tex2DCoordsArray ( void ) {
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
glm::vec2 Tex2DCoordsArray::GetTex2DCoords ( GLsizei iDataPos ) {
  glm::vec2 v2fTex2DCoords;

  iDataPos *= m_iStep;
  if (iDataPos < m_iDatasArraySize) {
    v2fTex2DCoords.s = m_tDatasArray[iDataPos  ];
    v2fTex2DCoords.t = m_tDatasArray[iDataPos+1];
  } else {
    v2fTex2DCoords.s = 0.f;
    v2fTex2DCoords.t = 0.f;
  }

  return v2fTex2DCoords;
}
