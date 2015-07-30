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
// The code in this file is inspired by the book "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/States/StateStack.hpp>

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
StateStack::ST_PendingChange::ST_PendingChange (StateStack::Action eAction, States::ID eStateID)
: m_eAction (eAction), m_eStateID (eStateID) {
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
StateStack::StateStack ( GameObject::ST_Context stContext ) :
  m_vStack        (),
  m_vPendingList  (),
  m_stContext     (stContext),
  m_mFactories    (),
  m_pInitializer  (nullptr),
  m_bReplacement  (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
StateStack::~StateStack ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void StateStack::Initialize ( States::ID eStateID ) {
  PushState ( eStateID );
	ApplyPendingChanges ();
}

////////////////////////////////////////////////////////////
void StateStack::Update ( void ) {
  // Initialize the new states when it's necessary.
  InitializeState ();

	// Iterate from top to bottom, stop as soon as Update () returns false
	for (auto rit = m_vStack.rbegin () ; rit != m_vStack.rend () ; ++rit) {
		if (!(*rit)->Update ())
			break;
	}

	ApplyPendingChanges ();
}

////////////////////////////////////////////////////////////
void StateStack::Draw ( void ) {
	// Draw all active states from bottom to top
  for (auto it = m_vStack.begin () ; it != m_vStack.end () ; ++it) {
    (*it)->Draw ();
  }
}

////////////////////////////////////////////////////////////
void StateStack::HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
	// Iterate from top to bottom, stop as soon as HandleEvent () returns false
	for (auto rit = m_vStack.rbegin () ; rit != m_vStack.rend () ; ++rit) {
		if (!(*rit)->HandleEvent (eEventType, sfKeyCode))
			break;
	}

	ApplyPendingChanges ();
}

////////////////////////////////////////////////////////////
void StateStack::HandleInput ( void ) {
	// Iterate from top to bottom, stop as soon as HandleInput () returns false
	for (auto rit = m_vStack.rbegin () ; rit != m_vStack.rend () ; ++rit) {
		if (!(*rit)->HandleInput ())
			break;
	}
}

////////////////////////////////////////////////////////////
void StateStack::PushState ( States::ID eStateID ) {
	m_vPendingList.push_back (ST_PendingChange (Push, eStateID));
}

////////////////////////////////////////////////////////////
void StateStack::PopState ( void ) {
	m_vPendingList.push_back (ST_PendingChange (Pop));
}

////////////////////////////////////////////////////////////
void StateStack::ReplaceState ( States::ID eStateID ) {
	m_vPendingList.push_back (ST_PendingChange (Replace, eStateID));
}

////////////////////////////////////////////////////////////
void StateStack::ClearStates ( void ) {
	m_vPendingList.push_back (ST_PendingChange (Clear));
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean StateStack::IsEmpty ( void ) {
	return m_vStack.empty ();
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
State::Ptr StateStack::CreateState ( States::ID eStateID ) {
  auto mFound = m_mFactories.find (eStateID);
  if (mFound == m_mFactories.end ()) {
    // Message which has to be delivered to the errors manager.
    //...

    return State::Ptr (new CrashState (*this, m_stContext));
  }

	return mFound->second ();
}

////////////////////////////////////////////////////////////
void StateStack::ApplyPendingChanges ( void ) {
  for (auto it = m_vPendingList.begin () ; it != m_vPendingList.end () ; ++it) {
		switch ((*it).m_eAction) {
			case Push:
				m_pInitializer = CreateState ((*it).m_eStateID);
				//m_vStack.push_back (CreateState ((*it).m_eStateID));
				//m_vStack[m_vStack.size ()-1]->m_sfThread.launch ();
				break;
			case Pop:
				m_vStack.pop_back ();
				break;
			case Replace:
			  m_bReplacement = GL_TRUE;
				m_pInitializer = CreateState ((*it).m_eStateID);
				break;
			case Clear:
				m_vStack.clear ();
				break;
		}
	}

	m_vPendingList.clear ();
}

////////////////////////////////////////////////////////////
void StateStack::InitializeState ( void ) {
	if (m_pInitializer != nullptr) {
    if (!m_pInitializer->Initialize ()) {
      if (m_bReplacement) {
				m_vStack.pop_back ();
        m_bReplacement = GL_FALSE;
      }
      m_vStack.push_back (std::move(m_pInitializer));
    }
	}
}
