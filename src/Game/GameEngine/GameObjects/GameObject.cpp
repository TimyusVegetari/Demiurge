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
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObjectsManager.hpp>

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::ST_Context::ST_Context ( const GLuint& uiElapsedTime,
                                     RenderTargetsManager& oRenderTargetsManager,
                                     drimi::BmpFont& oBmpFont,
                                     GraphicsEngine& oGraphicsEngine,
                                     GameObjectsManager& oGameObjectsManager ) :
  m_uiElapsedTime           (uiElapsedTime),
  m_oRenderTargetsManager   (oRenderTargetsManager),
  m_oBmpFont                (oBmpFont),
  m_oGraphicsEngine         (oGraphicsEngine),
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
