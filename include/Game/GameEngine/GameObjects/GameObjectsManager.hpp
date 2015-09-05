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
#include <Game/GameEngine/ManagerSignals.hpp>

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
      UNCONSTRUCTED_OBJECT,
      UNCREATED_INITIALIZER
    };

  private:
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<GameObjects::ID, GameObject::Ptr>  GOInstances;          ///< std::map of created instances of game objects.
    typedef GOInstances::size_type                      GOInstances_SizeType; ///< std::map::size_type of created game object list.
    typedef std::pair<GameObjects::ID, GameObject::Ptr> GOInstances_Pair;     ///< std::pair of created game object.

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a initializer container.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_InitContainer {
			GameObjects::Type   m_uiType;   ///< Type of the game object to initialize.
			GameObjects::ID     m_uiID;     ///< Identifier of the game object to initialize.
    };

    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<GameObjects::Initializer,
                std::list<ST_InitContainer>>            GOInitializers;       ///< std::map of game object initializer.

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<GameObjects::Type, GOInstances*> m_mList;        ///< List of created game object.
                                                              ///  of the specific game objects.
    GOInitializers                            m_mInitializer; ///< Initializer of game objects.
    GameObject::ST_Context                    m_stContext;    ///< Unique ressources context for the game.
    GLuint                                    m_uiError;      ///< Error value if an error arose.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a stack of game objects.
    ///
    /// \param stContext  Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    explicit GameObjectsManager ( GameObject::ST_Context stContext );

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
    /// \brief Add a game object in the list.
    ///
    /// \tparam T   Type of the specific game object.
    ///
    /// \param eGameObjectType  Registered game object identifier.
    ///        uiGameObjectID   Constructed game object identifier.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    void AddGameObject ( GameObjects::Type eGameObjectType, GameObjects::ID& eGameObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Remove a game object in the list.
    ///
    /// \param eGameObjectType  Registered game object identifier.
    ///        uiGameObjectID   Constructed game object identifier.
    ///
    ////////////////////////////////////////////////////////////
    GOInstances_SizeType DeleteGameObject ( GameObjects::Type eGameObjectType, GameObjects::ID uiGameObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the game objects in the initializers.
    ///
    /// \param uiInitializer  Identifier of the game object initializer.
    ///
    /// \return A signal to know if the initialization list is empty,
    ///         if there is an error, or a success of an element.
    ///
    ////////////////////////////////////////////////////////////
    OutSignal Initializer ( GameObjects::Initializer uiInitializer );

    ////////////////////////////////////////////////////////////
    /// \brief Create an initializer.
    ///
    /// \return Identifier of the game object initializer.
    ///
    ////////////////////////////////////////////////////////////
    GameObjects::Initializer CreateInitializer ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize a game object.
    ///
    /// \tparam T   Type of the specific game object.
    ///
    /// \param uiInitializer    Identifier of the game object initializer.
    ///        eGameObjectType  Registered game object identifier.
    ///        uiGameObjectID   Constructed game object identifier.
    ///
    /// \return True if the pre-initialization succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLboolean AddToInitializer ( GameObjects::Initializer uiInitializer, GameObjects::Type eGameObjectType, GameObjects::ID& uiGameObjectID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list is exist.
    ///
    /// \param eGameObjectType  Registered game object identifier.
    ///
    /// \return True if the list is exist, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsExist ( GameObjects::Type eGameObjectType );

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified game object.
    ///
    /// \tparam T   Type of the specific game object.
    ///
    /// \param eGameObjectType  Registered game object identifier.
    ///        uiGameObjectID   Constructed game object identifier.
    ///
    /// \return Game object or error.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetGameObject ( GameObjects::Type eGameObjectType, GameObjects::ID uiGameObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckError ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the ressources context.
    ///
    /// \return Instance of the ressources context.
    ///
    ////////////////////////////////////////////////////////////
    GameObject::ST_Context& GetContext ( void );
};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
void GameObjectsManager::AddGameObject ( GameObjects::Type eGameObjectType, GameObjects::ID& uiGameObjectID ) {
  if (!IsExist (eGameObjectType)) {
    m_mList.insert (std::pair<GameObjects::Type, GameObjectsManager::GOInstances*> (eGameObjectType, new GameObjectsManager::GOInstances ()));
    uiGameObjectID = 1;
  } else {
    uiGameObjectID = m_mList[eGameObjectType]->rend ()->first + 1;
  }
	m_mList[eGameObjectType]->insert (GameObjectsManager::GOInstances_Pair (uiGameObjectID, GameObject::Ptr (new T (m_stContext))));
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
T& GameObjectsManager::GetGameObject ( GameObjects::Type eGameObjectType, GameObjects::ID uiGameObjectID ) {
  auto mFound = m_mList[eGameObjectType]->find (uiGameObjectID);
  if (mFound == m_mList[eGameObjectType]->end ()) {
    m_uiError = Error::UNCONSTRUCTED_OBJECT;

    AddGameObject<T> ( eGameObjectType, uiGameObjectID );
    return static_cast<T&> (*(*m_mList[eGameObjectType])[uiGameObjectID]);
  }
  return static_cast<T&> (*mFound->second);
}

////////////////////////////////////////////////////////////
template <typename T>
GLboolean GameObjectsManager::AddToInitializer ( GameObjects::Initializer uiInitializer, GameObjects::Type eGameObjectType, GameObjects::ID& uiGameObjectID ) {
  auto mFound = m_mInitializer.find (uiInitializer);
  if (mFound == m_mInitializer.end ()) {
    m_uiError = Error::UNCREATED_INITIALIZER;
    return GL_FALSE;
  }
  AddGameObject<T> (eGameObjectType, uiGameObjectID);
  m_mInitializer[uiInitializer].push_back ({eGameObjectType, uiGameObjectID});
  return GL_TRUE;
}

#endif // GAMEOBJECTSMANAGER_HPP__
