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
StateStack::StateStack ( GameObject::ST_Context& stContext ) :
  m_vStack        (),
  m_vPendingList  (),
  m_stContext     (stContext),
  m_oFactories    (*this, stContext)
{
  m_oFactories.RegisterState<CrashState> (States::ID::None, "Crash");
}

////////////////////////////////////////////////////////////
StateStack::~StateStack ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void StateStack::RegisterStates ( void ) {
  std::cout << "States registering : ";
  m_oFactories.RegisterState<InDevInfoState> (States::ID::InDevInfo, "InDevInfo");
  m_oFactories.RegisterState<TitleState> (States::ID::Title, "Title");
  m_oFactories.RegisterState<WorldState> (States::ID::World, "World");
  std::cout << "Succeed" << std::endl;
}

////////////////////////////////////////////////////////////
void StateStack::Initialize ( States::ID eStateID ) {
  // Launch the creation of the state.
  std::cout << "Calling of '" << m_oFactories.GetName (eStateID) << "'..." << std::endl;
  PushState ( eStateID );
	ApplyPendingChanges ();
  // Initialize the state.
  OutSignal eOutSignal;
  while ((eOutSignal = m_oFactories.InitializeStates (m_vStack)) == OutSignal::Element_Succeed) {}
  if (eOutSignal == OutSignal::Element_Failed)
    std::cout << "'" << m_oFactories.GetName (eStateID) << "' initialization failed" << std::endl;
  else
    std::cout << "'" << m_oFactories.GetName (eStateID) << "' initialization succeed" << std::endl;
}

////////////////////////////////////////////////////////////
void StateStack::Update ( void ) {
  // Initialize the new states when it's necessary.
  if (m_oFactories.GetInitializingCount () > 0) {
    std::cout << "States initializing..." << std::endl;
    m_oFactories.InitializeStates (m_vStack);
  }

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
void StateStack::Crash ( void ) {
	m_vPendingList.push_back (ST_PendingChange (Push, States::ID::None));

	ApplyPendingChanges ();
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
void StateStack::ApplyPendingChanges ( void ) {
  for (auto it = m_vPendingList.begin () ; it != m_vPendingList.end () ; ++it) {
    // Check if the state identifier is legal.
    if (!m_oFactories.IsRegistered ((*it).m_eStateID)) {
      // Message which has to be delivered to the errors manager.
      //...

      (*it).m_eAction = Push;
      (*it).m_eStateID = States::ID::None;
    }
    // Applying of the pending changes.
		switch ((*it).m_eAction) {
			case Push:
			  if (!m_oFactories.IsConstructed ((*it).m_eStateID)) {
          m_oFactories.Construct ((*it).m_eStateID);
          //m_vStack.push_back (CreateState ((*it).m_eStateID));
          //m_vStack[m_vStack.size ()-1]->m_sfThread.launch ();
			  } else {
          std::cout << "Warning : The state '" << m_oFactories.GetName ((*it).m_eStateID) << "' has been called then it already constructed !" << std::endl;
          std::cout << "          The command was 'State Push'." << std::endl;
        }
				break;
			case Pop:
				m_vStack.pop_back ();
				break;
			case Replace:
			  if (!m_oFactories.IsConstructed ((*it).m_eStateID)) {
          m_oFactories.EnableReplacement ();
          m_oFactories.Construct ((*it).m_eStateID);
			  } else {
          std::cout << "Warning : The state '" << m_oFactories.GetName ((*it).m_eStateID) << "' has been called then it already constructed !" << std::endl;
          std::cout << "          The command was 'State Replace'." << std::endl;
        }
				break;
			case Clear:
				m_vStack.clear ();
				break;
		}
	}

	m_vPendingList.clear ();
}
