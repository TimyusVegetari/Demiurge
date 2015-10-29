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

#include <Game/GameEngine/GraphicsEngine/Renderer3D/RenderList3D.hpp>

////////////////////////////////////////////////////////////
// Structure
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderList3D::ST_Identifiers::ST_Identifiers ( void ) :
  m_lList           (),
  m_lListIter       (m_lList.begin ())
{
}

////////////////////////////////////////////////////////////
RenderList3D::ST_Identifiers::~ST_Identifiers ( void ) {
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
RenderList3D::Iter RenderList3D::PushBack ( Objects3D::Type eTypeID, GLuint uiObjectID ) {
  m_stIdentifiers[eTypeID].m_lList.push_back (uiObjectID);
  RenderList3D::Iter lListLast = --m_stIdentifiers[eTypeID].m_lList.end ();

  return lListLast;
}

////////////////////////////////////////////////////////////
RenderList3D::Iter RenderList3D::PushFront ( Objects3D::Type eTypeID, GLuint uiObjectID ) {
  m_stIdentifiers[eTypeID].m_lList.push_front (uiObjectID);

  return m_stIdentifiers[eTypeID].m_lList.begin ();
}

////////////////////////////////////////////////////////////
RenderList3D::Iter RenderList3D::Insert ( Objects3D::Type eTypeID, GLuint uiObjectID, const GLuint uiListedObjectID ) {
  for (RenderList3D::Iter lIter = m_stIdentifiers[eTypeID].m_lList.begin () ; lIter != m_stIdentifiers[eTypeID].m_lList.end () ; lIter++)
    if ((*lIter) == uiListedObjectID)
      return m_stIdentifiers[eTypeID].m_lList.insert (lIter, uiObjectID);

  return m_stIdentifiers[eTypeID].m_lList.end ();
}

////////////////////////////////////////////////////////////
RenderList3D::Size_type RenderList3D::Erase ( Objects3D::Type eTypeID, const GLuint uiListedObjectID ) {
  for (RenderList3D::Iter lIter = m_stIdentifiers[eTypeID].m_lList.begin () ; lIter != m_stIdentifiers[eTypeID].m_lList.end () ; lIter++)
    if ((*lIter) == uiListedObjectID) {
      m_stIdentifiers[eTypeID].m_lList.erase (lIter);
      break;
    }

  return m_stIdentifiers[eTypeID].m_lList.size ();
}

////////////////////////////////////////////////////////////
GLboolean RenderList3D::Reset ( Objects3D::Type eTypeID ) {
  m_stIdentifiers[eTypeID].m_lListIter = m_stIdentifiers[eTypeID].m_lList.begin ();
  if (m_stIdentifiers[eTypeID].m_lListIter != m_stIdentifiers[eTypeID].m_lList.end ())
    return GL_TRUE;

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean RenderList3D::Advance ( Objects3D::Type eTypeID ) {
  m_stIdentifiers[eTypeID].m_lListIter++;
  if (m_stIdentifiers[eTypeID].m_lListIter != m_stIdentifiers[eTypeID].m_lList.end ())
    return GL_TRUE;

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean RenderList3D::IsEmpty ( Objects3D::Type eTypeID ) {
	return m_stIdentifiers[eTypeID].m_lList.empty ();
}

////////////////////////////////////////////////////////////
GLuint RenderList3D::GetObjectID ( Objects3D::Type eTypeID ) {
  return *m_stIdentifiers[eTypeID].m_lListIter;
}
