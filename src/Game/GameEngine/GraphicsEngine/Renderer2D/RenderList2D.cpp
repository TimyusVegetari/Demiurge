////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2015 Acroute Anthony (ant110283@hotmail.fr)
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

#include <Game/GameEngine/GraphicsEngine/Renderer2D/RenderList2D.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderList2D::RenderList2D ( void ) :
  m_lList           (),
  m_mIndex          (),
  m_uiIdAccumulator (0),
  m_uiError         (Error::NONE)
{
}

////////////////////////////////////////////////////////////
RenderList2D::~RenderList2D ( void ) {
	m_lList.clear ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderList2D::Size_type RenderList2D::Erase ( const GLuint uiDrawableID ) {
  m_lList.erase (m_mIndex[uiDrawableID]);
  m_mIndex.erase (uiDrawableID);

  return m_lList.size ();
}

////////////////////////////////////////////////////////////
GLboolean RenderList2D::Reset ( void ) {
  m_lListIter = m_lList.begin ();
  if (m_lListIter != m_lList.end ())
    return GL_TRUE;
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean RenderList2D::Advance ( void ) {
  m_lListIter++;
  if (m_lListIter != m_lList.end ())
    return GL_TRUE;
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean RenderList2D::IsEmpty ( void ) {
	return m_lList.empty ();
}

////////////////////////////////////////////////////////////
sf::Drawable& RenderList2D::GetDrawable ( void ) {
  return (**m_lListIter);
}

////////////////////////////////////////////////////////////
GLuint RenderList2D::CheckError ( void ) {
	return m_uiError;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void RenderList2D::CheckIDError ( GLuint uiDrawableID ) {
  if (uiDrawableID > m_uiIdAccumulator) {
    m_uiIdAccumulator = uiDrawableID;
    m_uiError = Error::OVERFLOWED_OBJECT;
  } else
    m_uiError = Error::UNCONSTRUCTED_OBJECT;
}
