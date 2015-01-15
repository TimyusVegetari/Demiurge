////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2014-2015 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file StateStack.hpp
 * \brief Class for the stack of the states.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014-2015
 *
 */

#ifndef STATESTACK_HPP__
#define STATESTACK_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "State.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to store and manage the states of the game
/// with a stack.
///
////////////////////////////////////////////////////////////
class StateStack : private sf::NonCopyable {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    enum Action {
      Push,
      Pop,
      Clear
    }; ///< List of possible actions in the stack.

  private:
    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a change to do in the stack.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_PendingChange {
      Action              m_eAction;  ///< Action to execute in the stack.
      States::ID          m_eStateID; ///< ID of the state want to do this change.

      explicit            ST_PendingChange ( Action eAction, States::ID eStateID = States::None );
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<State::Ptr>           m_vStack;       ///< Stack of states.
    std::vector<ST_PendingChange>     m_vPendingList; ///< List of changes ready to be executed for the stack.
    State::ST_Context                 m_stContext;    ///< Unique ressources context for the game.
    std::map<States::ID,
        std::function<State::Ptr ()>> m_mFactories;   ///< List of functions to call constructor of the specific states.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a stack of states.
    ///
    /// \param stContext  Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    explicit StateStack ( State::ST_Context stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the stack of states.
    ///
    ////////////////////////////////////////////////////////////
    ~StateStack ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Register a state in the stack.
    ///
    /// \tparam T   Type of the specific state.
    ///
    /// \param eStateID   ID of the state to register.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    void RegisterState ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the update of the states in the stack.
    ///
    ////////////////////////////////////////////////////////////
    void Update ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the draw of the states in the stack.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the events of the states in the stack and
    /// execute the changes in the stack.
    ///
    /// \param sfEvent  The events got back by the game.
    ///
    ////////////////////////////////////////////////////////////
    void HandleEvent ( const sf::Event& sfEvent );

    ////////////////////////////////////////////////////////////
    /// \brief Add a state on the top of the stack.
    ///
    /// \param eStateID   ID of the registered state.
    ///
    ////////////////////////////////////////////////////////////
    void PushState ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Remove a state from the top of the stack.
    ///
    ////////////////////////////////////////////////////////////
    void PopState ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Clear the totality of the stack.
    ///
    ////////////////////////////////////////////////////////////
    void ClearStates ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the stack is empty.
    ///
    /// \return True if the stack is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmpty ( void );

  private:
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Create a type of specific state.
    ///
    /// \param eStateID   ID of the registered state.
    ///
    /// \return Pointer of constructed state.
    ///
    ////////////////////////////////////////////////////////////
    State::Ptr CreateState ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Apply changes in the stack.
    ///
    ////////////////////////////////////////////////////////////
    void  ApplyPendingChanges ( void );
};

#endif // STATESTACK_HPP__
