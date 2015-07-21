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
  m_mTextureMap   (),
  m_mTextureIDMap ()
{
  Texture2D::Ptr psfTexture (new sf::Texture ());
  psfTexture->create (16, 16);

	m_mTextureMap.insert (std::make_pair (NONE_TEXTURE, std::move (psfTexture)));
	m_mTextureIDMap.insert (std::make_pair (NONE_TEXTURE, NONE_TEXTURE));
}

////////////////////////////////////////////////////////////
Textures2DManager::~Textures2DManager ( void ) {
	m_mTextureMap.clear ();
	m_mTextureIDMap.clear ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint Textures2DManager::LoadTexture ( Textures2DManager::TexType eType, const std::string& szFileName, const std::string& szFileExt ) {
  GLuint uiTextureID;
  if (eType == Textures2DManager::TexType::SFML_TEXTURE) {
    Texture2D::Ptr psfTexture (new sf::Texture ());
    if (psfTexture->loadFromFile (szFileName+"."+szFileExt)) {
      uiTextureID = m_mTextureMap.size ();
      m_mTextureMap.insert (std::make_pair (uiTextureID, std::move (psfTexture)));
    } else {
      // Message which has to be delivered to the errors manager.
      //...
      uiTextureID = NONE_TEXTURE;
    }
  } else if (eType == Textures2DManager::TexType::CUBEMAP_TEXTURE) {
    // List of successive faces to create textures of the cube map
    GLenum eCubeMapTarget[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    // Load the textures
    sf::Image sfTexture[6];
    sfTexture[0].loadFromFile (szFileName+"_right."+szFileExt);
    sfTexture[1].loadFromFile (szFileName+"_left."+szFileExt);
    sfTexture[2].loadFromFile (szFileName+"_top."+szFileExt);
    sfTexture[3].loadFromFile (szFileName+"_bottom."+szFileExt);
    sfTexture[4].loadFromFile (szFileName+"_front."+szFileExt);
    sfTexture[5].loadFromFile (szFileName+"_back."+szFileExt);

    // Generate an identifier of the cube map
    GLuint uiOpenGLTexID;
    glGenTextures (1, &uiOpenGLTexID);
    uiTextureID = m_mTextureMap.size ();
    m_mTextureIDMap.insert (std::make_pair (uiTextureID, uiOpenGLTexID));

    // Configurate cube map
    glBindTexture (GL_TEXTURE_CUBE_MAP, uiOpenGLTexID);

    for (GLuint uiFace = 0 ; uiFace < 6 ; uiFace++) {
      glTexImage2D (eCubeMapTarget[uiFace],
                    0,
                    GL_RGBA,
                    static_cast<GLsizei> (sfTexture[uiFace].getSize ().x),
                    static_cast<GLsizei> (sfTexture[uiFace].getSize ().y),
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    sfTexture[uiFace].getPixelsPtr ());
    }

    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  } else
    uiTextureID = NONE_TEXTURE;

  return uiTextureID;
}

////////////////////////////////////////////////////////////
void Textures2DManager::DeleteTexture ( Textures2DManager::TexType eType, GLuint uiTextureID ) {
  if (eType == Textures2DManager::TexType::SFML_TEXTURE) {
    auto mFound = m_mTextureMap.find (uiTextureID);
    if (mFound == m_mTextureMap.end () || uiTextureID == NONE_TEXTURE) {
      // Message which has to be delivered to the errors manager.
      //...
    } else
      m_mTextureMap.erase (uiTextureID);
  } else if (Textures2DManager::TexType::CUBEMAP_TEXTURE) {
    auto mFound = m_mTextureIDMap.find (uiTextureID);
    if (mFound == m_mTextureIDMap.end () || uiTextureID == NONE_TEXTURE) {
      // Message which has to be delivered to the errors manager.
      //...
    } else {
      glDeleteTextures (1, &(mFound->second));
      m_mTextureIDMap.erase (uiTextureID);
    }
  }
}

////////////////////////////////////////////////////////////
void Textures2DManager::BindTexture ( Textures2DManager::TexType eType, GLuint uiTextureID ) {
  if (eType == Textures2DManager::TexType::SFML_TEXTURE) {
    // For this moment, I don't code this part.
  } else if (Textures2DManager::TexType::CUBEMAP_TEXTURE) {
    auto mFound = m_mTextureIDMap.find (uiTextureID);
    if (mFound == m_mTextureIDMap.end ()) {
      // Message which has to be delivered to the errors manager.
      //...
    }
    glBindTexture (GL_TEXTURE_CUBE_MAP, mFound->second);
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
const sf::Texture& Textures2DManager::GetSFMLTexture ( GLuint uiTextureID ) {
  auto mFound = m_mTextureMap.find (uiTextureID);
  if (mFound == m_mTextureMap.end ()) {
    // Message which has to be delivered to the errors manager.
    //...

    return *m_mTextureMap[NONE_TEXTURE];
  }
  return *mFound->second;
}
