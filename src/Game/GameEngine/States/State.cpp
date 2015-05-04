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
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
State::ST_Context::ST_Context ( RenderTargetsManager&	m_oRenderTargetsManager,
                                drimi::BmpFont& oBmpFont,
                                Textures2DManager& oTextures2DManager,
                                GameObjectsManager& oGameObjectsManager ) :
  m_poRenderTargetsManager  (m_oRenderTargetsManager),
  m_poBmpFont               (oBmpFont),
  m_poTextures2DManager     (&oTextures2DManager),
  m_poGameObjectsManager    (oGameObjectsManager)
{
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
State::State ( StateStack& oStack, ST_Context stContext ) :
  m_poStack   (oStack),
  m_stContext (stContext)
{
}

////////////////////////////////////////////////////////////
State::~State ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void State::RequestStackPush ( States::ID eStateID ) {
  m_poStack.PushState (eStateID);
}

////////////////////////////////////////////////////////////
void State::RequestStackPop ( void ) {
	m_poStack.PopState ();
}

////////////////////////////////////////////////////////////
void State::RequestStateClear ( void ) {
	m_poStack.ClearStates ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
State::ST_Context State::GetContext ( void ) const {
	return m_stContext;
}
