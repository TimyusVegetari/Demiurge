////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2013-2015 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file BmpFont.hpp
 * \brief Class to define a bitmap font.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2013-2015
 *
 */

#ifndef DRIMI_BITMAPFONT_FONT_HPP__
#define DRIMI_BITMAPFONT_FONT_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

// Includes for Windows
#if defined(_WIN32) || defined(WIN32)
  #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
  #endif

  #include <windows.h>
  #include <winsock2.h> // FreeImage is static and thus I have to add winsock2
#endif

#define FREEIMAGE_LIB
#include <FreeImage.h>

#include <iostream>

namespace drimi {
////////////////////////////////////////////////////////////
/// \brief Class for loading and manipulating character bitmap fonts
///
////////////////////////////////////////////////////////////
class BmpFont {

  private:
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<sf::Uint32, sf::Glyph> GlyphTable; ///< Table mapping a codepoint to its glyph

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a page of glyphs
    ///
    ////////////////////////////////////////////////////////////
    struct ST_Page {
      GlyphTable          m_mapGlyphs;  ///< Table mapping code points to their corresponding glyph
      sf::Texture         m_sfTexture;  ///< Texture containing the pixels of the glyphs
      GLuint              m_uiNextRow;  ///< Y position of the next new row in the texture
      std::vector<GLint>  m_vRows;      ///< List containing the position of all the existing rows

      ST_Page             ( void );
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ST_Page             m_oPages[2];
    GLint               m_iAdvance;
    sf::Shader*         m_psfShader;
  public:

    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor defines an empty font
    ///
    ////////////////////////////////////////////////////////////
    BmpFont ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param oCopy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    BmpFont ( const BmpFont& oCopy );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Cleans up all the internal resources used by the font
    ///
    ////////////////////////////////////////////////////////////
    ~BmpFont ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Load the bitmap font from a file
    ///
    /// The supported font format is: PNG.
    ///
    /// \param szFileName Path of the font file to load
    /// \param bBold      Retrieve the bold version or the regular one?
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    ////////////////////////////////////////////////////////////
    GLboolean LoadFromFile ( const std::string& szFileName, GLboolean bBold );

    ////////////////////////////////////////////////////////////
    /// \brief Load the shader of the bitmap font from a file
    ///
    /// \param szVertFileName Path of the vertex shader file to load
    /// \param szFragFileName Path of the fragment shader file to load
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    ////////////////////////////////////////////////////////////
    GLboolean LoadShaderFromFile ( const std::string& szVertFileName, const std::string& szFragFileName );

    ////////////////////////////////////////////////////////////
    /// \brief Overload of assignment operator
    ///
    /// \param oRight Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    BmpFont& operator = ( const BmpFont& oRight );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve a glyph of the font
    ///
    /// \param uiCodePoint   Unicode code point of the character to get
    /// \param bBold         Retrieve the bold version or the regular one?
    ///
    /// \return The glyph corresponding to \a uiCodePoint and \a bBold
    ///
    ////////////////////////////////////////////////////////////
    const sf::Glyph& GetGlyph ( sf::Uint32 uiCodePoint, GLboolean bBold ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the kerning offset of a glyph
    ///
    /// The kerning is an extra offset (negative) to apply between two
    /// glyphs when rendering them, to make the pair look more "natural".
    /// For example, the pair "AV" have a special kerning to make them
    /// closer than other characters. Most of the glyphs pairs have a
    /// kerning offset of zero, though.
    ///
    /// \param uiCodePoint   Unicode code point of the character
    /// \param bBold         Retrieve the bold version or the regular one?
    ///
    /// \return Kerning value for \a uiCodePoint, in pixels
    ///
    ////////////////////////////////////////////////////////////
    GLint GetKerning ( sf::Uint32 uiCodePoint, GLboolean bBold ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the line spacing
    ///
    /// Line spacing is the vertical offset to apply between two
    /// consecutive lines of text.
    ///
    /// \return Line spacing, in pixels
    ///
    ////////////////////////////////////////////////////////////
    GLint GetLineSpacing ( void ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve the texture containing the loaded glyphs for bold or regular
    ///
    /// The contents of the returned texture changes as more glyphs
    /// are requested, thus it is not very relevant. It is mainly
    /// used internally by drimi::BmpText.
    ///
    /// \param bBold Retrieve the bold version or the regular one?
    ///
    /// \return Texture containing the glyphs for bold or regular
    ///
    ////////////////////////////////////////////////////////////
    const sf::Texture& GetTexture ( GLboolean bBold ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the shader of the bitmap font
    ///
    /// \return Shader if it's exist, NULL else
    ///
    ////////////////////////////////////////////////////////////
    const sf::Shader* GetShader ( void ) const;
  private:

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Free all the internal resources
    ///
    ////////////////////////////////////////////////////////////
    void Cleanup ( void );
};

}

#endif // BITMAPFONT_FONT
