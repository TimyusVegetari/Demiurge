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

#include <Game/GameEngine/GraphicsEngine/Renderer3D/RenderList3D.hpp>

////////////////////////////////////////////////////////////
// Structure
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderList3D::ST_Datas::ST_Datas ( void ) :
  m_lList           (),
  m_mIndex          (),
  m_uiIdAccumulator (0),
  m_uiError         (Error::NONE)
{
}

////////////////////////////////////////////////////////////
RenderList3D::ST_Datas::~ST_Datas ( void ) {
	m_lList.clear ();
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderList3D::RenderList3D ( void ) {
}

////////////////////////////////////////////////////////////
RenderList3D::~RenderList3D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderList3D::Size_type RenderList3D::Erase ( GameObjects3D::Type uiTypeID, const GLuint uiObjectID ) {
  m_stDatas[uiTypeID].m_lList.erase (m_stDatas[uiTypeID].m_mIndex[uiObjectID]);
  m_stDatas[uiTypeID].m_mIndex.erase (uiObjectID);

  return m_stDatas[uiTypeID].m_lList.size ();
}

////////////////////////////////////////////////////////////
GLboolean RenderList3D::Reset ( GameObjects3D::Type uiTypeID ) {
  m_stDatas[uiTypeID].m_lListIter = m_stDatas[uiTypeID].m_lList.begin ();
  if (m_stDatas[uiTypeID].m_lListIter != m_stDatas[uiTypeID].m_lList.end ())
    return GL_TRUE;
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean RenderList3D::Advance ( GameObjects3D::Type uiTypeID ) {
  m_stDatas[uiTypeID].m_lListIter++;
  if (m_stDatas[uiTypeID].m_lListIter != m_stDatas[uiTypeID].m_lList.end ())
    return GL_TRUE;
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean RenderList3D::IsEmpty ( GameObjects3D::Type uiTypeID ) {
	return m_stDatas[uiTypeID].m_lList.empty ();
}

////////////////////////////////////////////////////////////
GameObject3D& RenderList3D::GetObject ( GameObjects3D::Type uiTypeID ) {
  return (**m_stDatas[uiTypeID].m_lListIter);
}

////////////////////////////////////////////////////////////
GLuint RenderList3D::CheckError ( GameObjects3D::Type uiTypeID ) {
	return m_stDatas[uiTypeID].m_uiError;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void RenderList3D::CheckIDError ( GameObjects3D::Type uiTypeID, const GLuint uiObjectID ) {
  if (uiObjectID > m_stDatas[uiTypeID].m_uiIdAccumulator) {
    m_stDatas[uiTypeID].m_uiIdAccumulator = uiObjectID;
    m_stDatas[uiTypeID].m_uiError = Error::OVERFLOWED_OBJECT;
  } else
    m_stDatas[uiTypeID].m_uiError = Error::UNCONSTRUCTED_OBJECT;
}
