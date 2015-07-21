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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Textures2DManager.hpp
 * \brief Class to manage the textures 2D.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef TEXTURES2DMANAGER_HPP__
#define TEXTURES2DMANAGER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>

////////////////////////////////////////////////////////////
// Precompilator data
////////////////////////////////////////////////////////////
#define GL_TEXTURE_CUBE_MAP             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z  0x851A

#define NONE_TEXTURE	0

////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////
namespace Texture2D {
  typedef std::unique_ptr<sf::Texture> Ptr;  ///< Unique pointer of texture 2D.
}

////////////////////////////////////////////////////////////
/// \brief Class to manage the textures 2D.
///
////////////////////////////////////////////////////////////
class Textures2DManager : sf::NonCopyable {

  public :
    ////////////////////////////////////////////////////////////
    // Enumeration
    ////////////////////////////////////////////////////////////
    enum TexType {
      NONE,
      SFML_TEXTURE,
      CUBEMAP_TEXTURE
    };

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<GLuint, Texture2D::Ptr>  m_mTextureMap;    ///< List of pointer to store the SFML textures.
    std::map<GLuint, GLuint>          m_mTextureIDMap;  ///< List of OpenGL textures identifiers.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a manager of textures 2D.
    ///
    ////////////////////////////////////////////////////////////
    Textures2DManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the manager of textures 2D.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Textures2DManager ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Load a texture 2D in OpenGL.
    ///
    /// \param eType      Type of the texture
    ///        szFileName Name of the file. An extra can be added
    ///                   if the type of the texture requires it.
    ///        szFileExt  Extension of the file.
    ///
    ////////////////////////////////////////////////////////////
    GLuint LoadTexture ( TexType eType, const std::string& szFileName, const std::string& szFileExt );

    ////////////////////////////////////////////////////////////
    /// \brief Remove a texture 2D in OpenGL.
    ///
    /// \param eType        Type of the texture
    ///        uiTextureID  ID of the identified texture 2D.
    ///
    ////////////////////////////////////////////////////////////
    void DeleteTexture ( TexType eType, GLuint uiTextureID );

    ////////////////////////////////////////////////////////////
    /// \brief Bind the texture for OpenGL.
    ///
    /// \param eType        Type of the texture
    ///        uiTextureID  ID of the identified texture 2D.
    ///
    ////////////////////////////////////////////////////////////
    void BindTexture ( Textures2DManager::TexType eType, GLuint uiTextureID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified SFML texture.
    ///
    /// \param uiTextureID  ID of the texture 2D.
    ///
    /// \return The identified sf::Texture or a default sf::Texture.
    ///
    ////////////////////////////////////////////////////////////
    const sf::Texture& GetSFMLTexture ( GLuint uiTextureID );
};

#endif // TEXTURES2DMANAGER_HPP__
