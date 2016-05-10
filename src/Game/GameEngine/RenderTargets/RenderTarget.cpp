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
#include <Game/GameEngine/RenderTargets/RenderTarget.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderTarget::RenderTarget ( void ) :
	m_v2uMinimalSize (0, 0)
{
}

////////////////////////////////////////////////////////////
gm::RenderTarget::~RenderTarget ( void ) {
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void gm::RenderTarget::SetMinimalSize ( GLuint uiWidth, GLuint uiHeight ) {
  m_v2uMinimalSize.x = uiWidth;
  m_v2uMinimalSize.y = uiHeight;
}

////////////////////////////////////////////////////////////
sf::Vector2u gm::RenderTarget::GetLegalSize ( GLuint uiWidth, GLuint uiHeight ) {
  if (uiWidth < m_v2uMinimalSize.x) uiWidth = m_v2uMinimalSize.x;
  if (uiHeight < m_v2uMinimalSize.y) uiHeight = m_v2uMinimalSize.y;
  return sf::Vector2u (uiWidth, uiHeight);
}
