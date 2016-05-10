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
#include <Game/GameEngine/RenderTargets/RenderTargetsManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderTargetsManager::RenderTargetsManager ( void ) :
  m_mList       (),
  m_mFactories  (),
  m_bFullScreen (GL_FALSE),
  m_uiError     (Error::NONE)
{
}

////////////////////////////////////////////////////////////
RenderTargetsManager::~RenderTargetsManager ( void ) {
	m_mList.clear ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void RenderTargetsManager::AddRenderTarget ( RenderTargets::ID eRenderTargetID ) {
	m_mList.insert (CreateRenderTarget (eRenderTargetID));
}

////////////////////////////////////////////////////////////
RenderTargetsManager::Size_type RenderTargetsManager::DeleteRenderTarget ( RenderTargets::ID eRenderTargetID ) {
	return m_mList.erase (eRenderTargetID);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean RenderTargetsManager::IsEmpty ( void ) {
	return m_mList.empty ();
}

////////////////////////////////////////////////////////////
void RenderTargetsManager::SetFullScreen ( GLboolean bFullScreen ) {
	m_bFullScreen = bFullScreen;
}

////////////////////////////////////////////////////////////
GLboolean RenderTargetsManager::IsFullScreen ( void ) {
	return m_bFullScreen;
}

////////////////////////////////////////////////////////////
GLuint RenderTargetsManager::CheckError ( void ) {
	return m_uiError;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderTargetsManager::Pair RenderTargetsManager::CreateRenderTarget ( RenderTargets::ID eRenderTargetID ) {
  auto mFound = m_mFactories.find (eRenderTargetID);
  if (mFound == m_mFactories.end ()) {
    m_uiError = Error::UNREGISTERED_OBJECT;

    return RenderTargetsManager::Pair (RenderTargets::ID::None, nullptr);
  }

  return RenderTargetsManager::Pair (eRenderTargetID, mFound->second ());
}
