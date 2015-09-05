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
// The code in this file is inspired by the book "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Factories.hpp
 * \brief Class to manage the states creation/destruction.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef FACTORIES_HPP__
#define FACTORIES_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "State.hpp"
#include "GameStates/StateDefinitions.hpp"
#include <Game/GameEngine/ManagerSignals.hpp>

class StateStack;

namespace States {

////////////////////////////////////////////////////////////
/// \brief Class to construct, initialize and destruct the states of the game.
///
////////////////////////////////////////////////////////////
class Factories : private sf::NonCopyable {

  private:
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a state factory.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_Factory {
      std::function<State::Ptr ()>  m_fpConstructor;  ///< Function pointer of state constructor.
      State::Ptr                    m_pInitializer;   ///< Pointer of state to initialize it.
      GLboolean                     m_bLocked,        ///< Variable to lock the factory if the state is already constructed.
                                    m_bInitializing;  ///< Variable to know if the initialization of the state is running.
      std::string                   m_szName;         ///< Name of the state.

      explicit ST_Factory ( void );
      void SetConstructor ( const std::string& szName, std::function<State::Ptr ()> fpConstructor );
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    StateStack&                       m_oStateStack;              ///< An instance of the state stack to pass to the constructor when the registering of the factories.
    GameObject::ST_Context&           m_stContext;                ///< An instance of the game objects manager to initialize internal objects of the states.
    std::map<States::ID, ST_Factory>  m_mFactories;               ///< List of factories to construct and initialize the specific states.
    GLboolean                         m_bReplacement;             ///< Variable to know if the new state will replace the last in the stack.
    GLuint                            m_uiActivatedInitializers;  ///< Count of activated initializers.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a collection of states factories
    /// and get the game objects manager to call initialisation of internal
    /// game objects of the states.
    ///
    /// \param oStateStack  An instance of the state stack.
    ///        stContext    An instance of the game object context.
    ///
    ////////////////////////////////////////////////////////////
    explicit Factories ( StateStack& oStateStack, GameObject::ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the collection of states factories.
    ///
    ////////////////////////////////////////////////////////////
    ~Factories ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Construct a state.
    ///
    /// \param eStateID   ID of the state to construct.
    ///
    ////////////////////////////////////////////////////////////
    void Construct ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Call the initialize of the states in the initializer.
    ///
    /// \return A signal to know if the initialization list is empty,
    ///         if there is an error, or a success of an element.
    ///
    /// \param vStack   Instance of the stack of states.
    ///
    ////////////////////////////////////////////////////////////
    OutSignal InitializeStates ( std::vector<State::Ptr>& vStack );

    ////////////////////////////////////////////////////////////
    /// \brief Register a state in the factories collection.
    ///
    /// \tparam T   Type of the specific state.
    ///
    /// \param eStateID   ID of the state to register.
    ///        szName     Name of the state to register.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    void RegisterState ( States::ID eStateID, const std::string& szName );

    ////////////////////////////////////////////////////////////
    /// \brief Enable the replacement action.
    ///
    ////////////////////////////////////////////////////////////
    void EnableReplacement ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the state is registered.
    ///
    /// \param eStateID   ID of the state to register.
    ///
    /// \return True if the state is registered, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsRegistered ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Get if the state is constructed.
    ///
    /// \param eStateID   ID of the state to register.
    ///
    /// \return True if the state is constructed, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsConstructed ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the count of activated initializers.
    ///
    /// \return Count of activated initializers.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetInitializingCount ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the name of a state.
    ///
    /// \param eStateID   ID of the state to register.
    ///
    /// \return The name of a state.
    ///
    ////////////////////////////////////////////////////////////
    std::string GetName ( States::ID eStateID );

  private:
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    OutSignal GameObjectsInitializer ( GameObjects::Initializer uiInitializer );
};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
void Factories::RegisterState ( States::ID eStateID, const std::string& szName ) {
	m_mFactories.insert (std::pair<States::ID, States::Factories::ST_Factory> (eStateID, States::Factories::ST_Factory ()));
	m_mFactories[eStateID].SetConstructor (szName,
    [this] ( void ) {
      return State::Ptr (new T (m_oStateStack, m_stContext));
    }
  );
}

}

#endif // FACTORIES_HPP__
