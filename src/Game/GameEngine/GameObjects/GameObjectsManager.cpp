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
GameObjectsManager::GameObjectsManager ( void ) :
  m_mList       (),
  m_mFactories  (),
  m_uiError     (ERROR::NONE)
{
}

////////////////////////////////////////////////////////////
GameObjectsManager::~GameObjectsManager ( void ) {
	m_mList.clear ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GameObjectsManager::AddGameObject ( GameObjects::ID eGameObjectID ) {
	m_mList.insert (CreateGameObject (eGameObjectID));
}

////////////////////////////////////////////////////////////
GameObjectsManager::Size_type GameObjectsManager::DeleteGameObject ( GameObjects::ID eGameObjectID ) {
	return m_mList.erase (eGameObjectID);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GameObjectsManager::IsEmpty ( void ) {
	return m_mList.empty ();
}

////////////////////////////////////////////////////////////
GLuint GameObjectsManager::CheckError ( void ) {
	return m_uiError;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObjectsManager::Pair GameObjectsManager::CreateGameObject ( GameObjects::ID eGameObjectID ) {
  auto mFound = m_mFactories.find (eGameObjectID);
  if (mFound == m_mFactories.end ()) {
    m_uiError = ERROR::UNREGISTERED_OBJECT;

    return GameObjectsManager::Pair (GameObjects::ID::None, nullptr);
  }

  return GameObjectsManager::Pair (eGameObjectID, mFound->second ());
}
