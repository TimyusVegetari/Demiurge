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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "RenderTargetsManager.hpp"

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
RenderTargetsManager::RenderTargetsManager ( void ) :
  m_mList       (),
  m_mFactories  (),
  m_uiError     (ERROR::NONE)
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
template <typename T>
void RenderTargetsManager::RegisterRenderTarget ( RenderTargets::ID eRenderTargetID ) {
	m_mFactories[eRenderTargetID] = [this] () {
		return RenderTarget::Ptr (new T ());
	};
}

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
template <typename T>
T& RenderTargetsManager::GetRenderTargetObject ( RenderTargets::ID eRenderTargetID ) {
  auto mFound = m_mList.find (eRenderTargetID);
  if (mFound == m_mList.end ()) {
    m_uiError = ERROR::UNCONSTRUCTED_OBJECT;

    AddRenderTarget ( eRenderTargetID );
    return static_cast<T&>(*m_mList[eRenderTargetID]);
  }
  return static_cast<T&>(*mFound->second);
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
    m_uiError = ERROR::UNREGISTERED_OBJECT;

    return RenderTargetsManager::Pair (RenderTargets::ID::None, nullptr);
  }

  return RenderTargetsManager::Pair (eRenderTargetID, mFound->second ());
}
