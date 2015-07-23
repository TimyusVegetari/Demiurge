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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/Tex2DCoordsBufferObject.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Tex2DCoordsBufferObject::Tex2DCoordsBufferObject ( void ) :
  m_oTex2DCoords  ()
{
}

////////////////////////////////////////////////////////////
Tex2DCoordsBufferObject::~Tex2DCoordsBufferObject ( void ) {
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Tex2DCoordsBufferObject::ActiveTex2DCoordsPointer ( void ) {
  if (m_oTex2DCoords.BindBuffer ()) {
    GLint iTexturesStep = m_oTex2DCoords.GetStep ();
    GLsizei iDatasSize = m_oTex2DCoords.GetDatasSize ();

    if (iTexturesStep != 0 && iDatasSize != 0) {
      glTexCoordPointer (iTexturesStep, GL_FLOAT, iDatasSize, 0);
      // Debug : It will be necessary to check OpenGL error, in the future.
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}
