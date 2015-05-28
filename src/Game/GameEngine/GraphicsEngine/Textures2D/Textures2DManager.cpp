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
#include <Game/GameEngine/GraphicsEngine/Textures2D/Textures2DManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Textures2DManager::Textures2DManager ( void ) :
  m_mTextureMap ()
{
  Texture2D::Ptr psfTexture (new sf::Texture ());
  psfTexture->create (16, 16);

	m_mTextureMap.insert (std::make_pair (Textures2D::ID::None, std::move (psfTexture)));
}

////////////////////////////////////////////////////////////
Textures2DManager::~Textures2DManager ( void ) {
	m_mTextureMap.clear ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Textures2DManager::LoadTexture ( Textures2D::ID eTextureID, const std::string& szFileName ) {
	Texture2D::Ptr psfTexture (new sf::Texture ());
	if (psfTexture->loadFromFile (szFileName)) {
    m_mTextureMap.insert (std::make_pair (eTextureID, std::move (psfTexture)));
	} else {
    // Message which has to be delivered to the errors manager.
    //...
  }
}

////////////////////////////////////////////////////////////
void Textures2DManager::DeleteTexture ( Textures2D::ID eTextureID ) {
  auto mFound = m_mTextureMap.find (eTextureID);
  if (mFound == m_mTextureMap.end ()) {
    // Message which has to be delivered to the errors manager.
    //...
  } else
    m_mTextureMap.erase (eTextureID);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
const sf::Texture& Textures2DManager::GetTexture ( Textures2D::ID eTextureID ) {
  auto mFound = m_mTextureMap.find (eTextureID);
  if (mFound == m_mTextureMap.end ()) {
    // Message which has to be delivered to the errors manager.
    //...

    return *m_mTextureMap[Textures2D::ID::None];
  }
  return *mFound->second;
}
