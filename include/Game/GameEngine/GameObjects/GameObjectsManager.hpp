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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file GameObjectsManager.hpp
 * \brief Class to manage the game objects.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef GAMEOBJECTSMANAGER_HPP__
#define GAMEOBJECTSMANAGER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GameObject.hpp"
#include "GameObjectDefinitions.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to store and manage the game objects.
///
////////////////////////////////////////////////////////////
class GameObjectsManager : private sf::NonCopyable {

  public :
    ////////////////////////////////////////////////////////////
    // Enumeration
    ////////////////////////////////////////////////////////////
    enum Error {
      NONE,
      UNREGISTERED_OBJECT,
      UNCONSTRUCTED_OBJECT
    };

  private:
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<GameObjects::ID, GameObject::Ptr>::size_type Size_type;  ///< std::map::size_type of created game object list.
    typedef std::pair<GameObjects::ID, GameObject::Ptr>           Pair;       ///< std::pair of created game object.

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<GLuint, GameObject::Ptr>       m_mList;      ///< List of created game object.
    std::map<GameObjects::ID,
        std::function<GameObject::Ptr ()>>  m_mFactories; ///< List of functions to call constructor
                                                          ///  of the specific game objects.
    GLuint                                  m_uiError;    ///< Error value if an error arose.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a stack of game objects.
    ///
    ////////////////////////////////////////////////////////////
    explicit GameObjectsManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game objects.
    ///
    ////////////////////////////////////////////////////////////
    ~GameObjectsManager ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Register a game object in the stack.
    ///
    /// \tparam T   Type of the specific game object.
    ///
    /// \param eGameObjectID  ID of the game object to register.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    void RegisterGameObject ( GameObjects::ID eGameObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a game object in the list.
    ///
    /// \param eGameObjectID  ID of the registered game object.
    ///
    ////////////////////////////////////////////////////////////
    void AddGameObject ( GameObjects::ID eGameObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Remove a game object in the list.
    ///
    /// \param eGameObjectID  ID of the registered game object.
    ///
    ////////////////////////////////////////////////////////////
    Size_type DeleteGameObject ( GameObjects::ID eGameObjectID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list is empty.
    ///
    /// \return True if the list is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmpty ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified game object.
    ///
    /// \tparam T   Type of the specific game object.
    ///
    /// \param eGameObjectID  ID of the registered game object.
    ///
    /// \return Game object or error.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetGameObject ( GameObjects::ID eGameObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckError ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Create a type of specific game object.
    ///
    /// \param eGameObjectID   ID of the registered game object.
    ///
    /// \return Pointer of constructed game object.
    ///
    ////////////////////////////////////////////////////////////
    Pair CreateGameObject ( GameObjects::ID eGameObjectID );
};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
void GameObjectsManager::RegisterGameObject ( GameObjects::ID eGameObjectID ) {
	m_mFactories[eGameObjectID] = [this] () {
		return GameObject::Ptr (new T (*this));
	};
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
T& GameObjectsManager::GetGameObject ( GameObjects::ID eGameObjectID ) {
  auto mFound = m_mList.find (eGameObjectID);
  if (mFound == m_mList.end ()) {
    m_uiError = Error::UNCONSTRUCTED_OBJECT;

    AddGameObject ( eGameObjectID );
    return static_cast<T&>(*m_mList[eGameObjectID]);
  }
  return static_cast<T&>(*mFound->second);
}

#endif // GAMEOBJECTSMANAGER_HPP__
