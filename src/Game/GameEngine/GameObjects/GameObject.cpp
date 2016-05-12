////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2016 Acroute Anthony (ant110283@hotmail.fr)
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
#include <Game/GameEngine/States/StateStack.hpp>

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::ST_Context::ST_Context ( const GLuint& uiElapsedTime,
                                     RenderTargetsManager& oRenderTargetsManager,
                                     drimi::BmpFont& oBmpFont,
                                     GraphicsEngine& oGraphicsEngine,
                                     StateStack& oStateStack,
                                     GameObjectsManager& oGameObjectsManager ) :
  m_uiElapsedTime           (uiElapsedTime),
  m_oRenderTargetsManager   (oRenderTargetsManager),
  m_oBmpFont                (oBmpFont),
  m_oGraphicsEngine         (oGraphicsEngine),
  m_oStateStack             (oStateStack),
  m_oGameObjectsManager     (oGameObjectsManager)
{
}

////////////////////////////////////////////////////////////
const GLuint& GameObject::ST_Context::GetElapsedTime ( void ) {
  return m_uiElapsedTime;
}

////////////////////////////////////////////////////////////
RenderList2D& GameObject::ST_Context::GetRenderList2D ( GLuint uiRenderList2D_ID ) {
  return m_oGraphicsEngine.GetRenderer2D ().GetRenderList (uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
//RenderList3D& GameObject::ST_Context::GetRenderList3D ( GLuint uiRenderList3D_ID ) {
//  return m_oGraphicsEngine.GetRenderer3D ().GetRenderList (uiRenderList3D_ID);
//}

////////////////////////////////////////////////////////////
StateStack& GameObject::ST_Context::GetStateStack ( void ) {
  return m_oStateStack;
}

////////////////////////////////////////////////////////////
GameObjectsManager& GameObject::ST_Context::GetGameObjectsManager ( void ) {
  return m_oGameObjectsManager;
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::GameObject ( ST_Context& stContext ) :
  m_stContext       (stContext)
{
}

////////////////////////////////////////////////////////////
GameObject::~GameObject ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GameObject::RequestStackPush ( States::ID eStateID ) {
  m_stContext.GetStateStack ().PushState (eStateID);
}

////////////////////////////////////////////////////////////
void GameObject::RequestStackPop ( void ) {
	m_stContext.GetStateStack ().PopState ();
}

////////////////////////////////////////////////////////////
void GameObject::RequestStackReplace ( States::ID eStateID ) {
  m_stContext.GetStateStack ().ReplaceState (eStateID);
}

////////////////////////////////////////////////////////////
void GameObject::RequestStateClear ( void ) {
	m_stContext.GetStateStack ().ClearStates ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::ST_Context& GameObject::GetContext ( void ) const {
	return m_stContext;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
OGLManager& GameObject::GetOGLManager ( void ) {
  return m_stContext.m_oGraphicsEngine.GetOGLManager ();
}
