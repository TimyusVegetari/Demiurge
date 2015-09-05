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
#include <Game/GameEngine/GameObjects/GameObjectsManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObjectsManager::GameObjectsManager ( GameObject::ST_Context stContext ) :
  m_mList         (),
  m_mInitializer  (),
  m_stContext     (stContext),
  m_uiError       (Error::NONE)
{
}

////////////////////////////////////////////////////////////
GameObjectsManager::~GameObjectsManager ( void ) {
  for (std::map<GameObjects::Type, GOInstances*>::iterator it = m_mList.begin (); it != m_mList.end (); ++it)
    delete it->second;
	m_mList.clear ();
	m_mInitializer.clear ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObjectsManager::GOInstances_SizeType GameObjectsManager::DeleteGameObject ( GameObjects::Type eGameObjectType, GameObjects::ID uiGameObjectID ) {
	if (m_mList[eGameObjectType]->erase (uiGameObjectID)) {
    if (m_mList[eGameObjectType]->empty ())
      m_mList.erase (eGameObjectType);
    return GL_TRUE;
	}
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
OutSignal GameObjectsManager::Initializer ( GameObjects::Initializer uiInitializer ) {
  if (!m_mInitializer[uiInitializer].empty ()) {
    auto lBegin = m_mInitializer[uiInitializer].begin ();
    if ((*m_mList[lBegin->m_uiType])[lBegin->m_uiID]->Initialize ()) {
      // If initialisation succeed
      m_mInitializer[uiInitializer].pop_front ();
      return OutSignal::Element_Succeed;
    } else {
      // If initialisation failed
      m_mInitializer.erase (uiInitializer);
      return OutSignal::Element_Failed;
    }
  }
  // If initialisation finished
  m_mInitializer.erase (uiInitializer);
  return OutSignal::List_End;
}

////////////////////////////////////////////////////////////
GameObjects::Initializer GameObjectsManager::CreateInitializer ( void ) {
  GLuint uiInitializerID;
  if (m_mInitializer.empty ()) uiInitializerID = 1;
  else uiInitializerID = m_mInitializer.rend ()->first + 1;
	m_mInitializer.insert (std::pair<GameObjects::Initializer, std::list<ST_InitContainer>> (uiInitializerID, std::list<ST_InitContainer> ()));

	return uiInitializerID;

}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GameObjectsManager::IsExist ( GameObjects::Type eGameObjectType ) {
  auto mFound = m_mList.find (eGameObjectType);
  if (mFound == m_mList.end ()) {
    return GL_FALSE;
  }
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLuint GameObjectsManager::CheckError ( void ) {
	return m_uiError;
}

////////////////////////////////////////////////////////////
GameObject::ST_Context& GameObjectsManager::GetContext ( void ) {
  return m_stContext;
}
