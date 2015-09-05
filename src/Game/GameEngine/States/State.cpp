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
// A big part of the code in this file is inspired by the book
// "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/States/State.hpp>
#include <Game/GameEngine/States/StateStack.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
State::State ( StateStack& oStack, GameObject::ST_Context& stContext ) :
  GameObject          (stContext),
  m_oStack            (oStack),
  m_uiInitializer_ID  (0)
  /*m_sfThread        (&State::Initialize, this),
  m_bIsInitialized  (GL_FALSE)*/
{
}

////////////////////////////////////////////////////////////
State::~State ( void ) {
  //m_sfThread.wait ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void State::RequestStackPush ( States::ID eStateID ) {
  m_oStack.PushState (eStateID);
}

////////////////////////////////////////////////////////////
void State::RequestStackPop ( void ) {
	m_oStack.PopState ();
}

////////////////////////////////////////////////////////////
void State::RequestStackReplace ( States::ID eStateID ) {
  m_oStack.ReplaceState (eStateID);
}

////////////////////////////////////////////////////////////
void State::RequestStateClear ( void ) {
	m_oStack.ClearStates ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObjects::Initializer State::GetInitializerID ( void ) {
  return m_uiInitializer_ID;
}
