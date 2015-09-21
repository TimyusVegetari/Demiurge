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

#include <Game/GameEngine/GraphicsEngine/Renderer2D/Renderer2D.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer2D::Renderer2D ( void ) :
  m_mRenderLists    (),
  m_uiIdAccumulator (0),
  m_uiError         (NONE)
{
}

////////////////////////////////////////////////////////////
Renderer2D::~Renderer2D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer2D::Initialize ( void ) {
  std::cout << "Renderer 2D : Initializing..." << std::endl;
  GLboolean bSuccess = GL_TRUE;

  if (bSuccess)
    std::cout << "Renderer 2D : Initialization succeed" << std::endl;
  else
    std::cout << "Renderer 2D : Initialization failed" << std::endl;
  return bSuccess;
}

////////////////////////////////////////////////////////////
GLuint Renderer2D::CreateRenderList ( void ) {
  m_uiIdAccumulator++;
  m_mRenderLists.insert (Renderer2D::Pair (m_uiIdAccumulator, RenderList2D::Ptr (new RenderList2D ())));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
void Renderer2D::Erase ( GLuint uiRenderListID ) {
  auto mFound = m_mRenderLists.find (uiRenderListID);
  if (mFound == m_mRenderLists.end ()) {
    CheckIDError (uiRenderListID);
  } else {
    m_mRenderLists.erase (mFound);
  }
}

////////////////////////////////////////////////////////////
void Renderer2D::Render ( GLuint uiRenderListID, gm::RenderWindow& gmRenderWindow ) {
  auto mFound = m_mRenderLists.find (uiRenderListID);
  if (mFound == m_mRenderLists.end ()) {
    CheckIDError (uiRenderListID);
  } else {
    if ((*mFound->second).Reset ()) {
      do {
        gmRenderWindow.Draw ((*mFound->second).GetDrawable ());
      } while ((*mFound->second).Advance ());
    }
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer2D::IsEmpty ( void ) {
	return m_mRenderLists.empty ();
}

////////////////////////////////////////////////////////////
GLuint Renderer2D::CheckError ( void ) {
	return m_uiError;
}

////////////////////////////////////////////////////////////
RenderList2D& Renderer2D::GetRenderList ( GLuint uiRenderListID ) {
  auto mFound = m_mRenderLists.find (uiRenderListID);
  if (mFound == m_mRenderLists.end ()) {
    CheckIDError (uiRenderListID);

    m_mRenderLists.insert (Renderer2D::Pair (uiRenderListID, RenderList2D::Ptr (new RenderList2D ())));
    return (*m_mRenderLists[uiRenderListID]);
  }
  return (*mFound->second);
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Renderer2D::CheckIDError ( GLuint uiRenderListID ) {
  if (uiRenderListID > m_uiIdAccumulator) {
    m_uiIdAccumulator = uiRenderListID;
    m_uiError = Error::OVERFLOWED_OBJECT;
  } else
    m_uiError = Error::UNCONSTRUCTED_OBJECT;
}
