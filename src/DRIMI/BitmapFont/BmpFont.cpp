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
// Headers
////////////////////////////////////////////////////////////
#include <DRIMI/BitmapFont/BmpFont.hpp>

namespace drimi {

////////////////////////////////////////////////////////////
BmpFont::ST_Page::ST_Page ( void ) {
  m_uiNextRow = 0;
  // Remplissage standard de la table de glyphs
  for (sf::Uint32 uiChar = 0 ; uiChar < 255 ; uiChar++) {
    m_mapGlyphs.insert (std::pair<sf::Uint32, sf::Glyph> (uiChar, sf::Glyph ()));
  }
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
BmpFont::BmpFont ( void ) :
  m_iAdvance  (-1),
  m_psfShader (NULL)
{
}

////////////////////////////////////////////////////////////
BmpFont::BmpFont ( const BmpFont& oCopy ) :
  m_iAdvance  (oCopy.m_iAdvance),
  m_psfShader (oCopy.m_psfShader)
{
  m_oPages[0] = oCopy.m_oPages[0];
  m_oPages[1] = oCopy.m_oPages[1];
}

////////////////////////////////////////////////////////////
BmpFont::~BmpFont ( void ) {
  Cleanup ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean BmpFont::LoadFromFile ( const std::string& szFileName, GLboolean bBold ) {
  // Cleaning of the font image
  //Cleanup ();

  GLuint uiBold = static_cast<GLuint> (bBold);

  // Loading of the format of the font image
  FREE_IMAGE_FORMAT fiFormat = FreeImage_GetFileType (szFileName.c_str (), 0);
  if (fiFormat == FIF_UNKNOWN) {
    std::cout << "  Error : Format is unknown..." << std::endl;
    return GL_FALSE;
  }

  // Loading of the font image
	FIBITMAP* pfiImage = FreeImage_Load (fiFormat, szFileName.c_str ());
	if (pfiImage == NULL) {
    std::cout << "  Error : File is corrupted !" << std::endl;
		return GL_FALSE;
	}

  // Loading of the image pixels
	BYTE* puiPixelData = NULL;
  puiPixelData = FreeImage_GetBits (pfiImage);
  if (puiPixelData == NULL) {
    std::cout << "  Error : Image pixels are unavailable..." << std::endl;
    return GL_FALSE;
  }

  // Getting of the image size
  GLuint uiWidth = FreeImage_GetWidth (pfiImage);
  GLuint uiHeight = FreeImage_GetHeight (pfiImage);
  GLuint uiPixSize = uiWidth*uiHeight*4;

  // Convert BGRA colors to RGBA and inverse the Y
  // FreeImage load the image with a inverted Y and the BGRA format
  sf::Uint8* sfBits = new sf::Uint8[uiPixSize];
  GLuint uiPixDataR, uiPixDataG, uiPixDataB, uiPixDataA;
  GLuint uiBitsR, uiBitsG, uiBitsB, uiBitsA;
  GLuint uiLength, uiInvLength;
  GLuint uiInvY = uiHeight-1;
  for (GLuint uiY = 0 ; uiY < uiHeight ; uiY++) {
    uiLength = uiY*uiWidth;
    uiInvLength = uiInvY*uiWidth;
    for (GLuint uiX = 0 ; uiX < uiWidth ; uiX++) {
      uiPixDataR = (uiX+uiLength)*4;
      uiPixDataG = uiPixDataR+1;
      uiPixDataB = uiPixDataR+2;
      uiPixDataA = uiPixDataR+3;
      uiBitsR = (uiX+uiInvLength)*4;
      uiBitsG = uiBitsR+1;
      uiBitsB = uiBitsR+2;
      uiBitsA = uiBitsR+3;

      sfBits[uiBitsR] = static_cast<sf::Uint8> (puiPixelData[uiPixDataB]);
      sfBits[uiBitsG] = static_cast<sf::Uint8> (puiPixelData[uiPixDataG]);
      sfBits[uiBitsB] = static_cast<sf::Uint8> (puiPixelData[uiPixDataR]);
      if (static_cast<GLuint> (sfBits[uiBitsR]) == 0 && static_cast<GLuint> (sfBits[uiBitsG]) == 0 && static_cast<GLuint> (sfBits[uiBitsB]) == 0)
        sfBits[uiBitsA] = 0;
      else
        sfBits[uiBitsA] = static_cast<sf::Uint8> (puiPixelData[uiPixDataA]);
    }
    uiInvY--;
  }

  // Storage of the image pixels in texture
  m_oPages[uiBold].m_sfTexture.create (uiWidth, uiHeight);
  m_oPages[uiBold].m_sfTexture.update (sfBits);

  // Compute positions of the lines
  GLint iY = 1;
  m_oPages[uiBold].m_vRows.push_back (iY);
  uiWidth *= 4;
  for (GLuint uiPix = uiWidth+4 ; uiPix < uiPixSize ; uiPix += uiWidth ) {
    iY++;
    // Colors are in BGR Format, not in RGB !
    if (static_cast<GLuint> (sfBits[uiPix  ]) == 0 && static_cast<GLuint> (sfBits[uiPix+1]) == 255 && static_cast<GLuint> (sfBits[uiPix+2]) == 0) {
      m_oPages[uiBold].m_vRows.push_back (iY);
    }
  }

  // Compute fields of the glyphs
  GLint iGlyphWidth = 0;
  GLint iGlyphX = 1;
  GLuint uiRow = 0;
  for (GLuint uiChar = 0 ; uiChar < 256 ; uiChar++)
    m_oPages[uiBold].m_mapGlyphs[static_cast<sf::Uint32> (uiChar)] = sf::Glyph ();
  GlyphTable::iterator
    mIt (m_oPages[uiBold].m_mapGlyphs.begin ()),
    mEnd (m_oPages[uiBold].m_mapGlyphs.end ());

  mIt->second.textureRect.left  = 1;
  mIt->second.textureRect.top   = 1;
  mIt->second.bounds.left   = 0;
  mIt->second.bounds.top    = 0;
  for (GLuint uiPix = uiWidth+4 ; uiPix < uiPixSize ; uiPix+=4 ) {
    if (static_cast<GLuint> (sfBits[uiPix  ]) == 0 && static_cast<GLuint> (sfBits[uiPix+1]) == 255 && static_cast<GLuint> (sfBits[uiPix+2]) == 0) {
      mIt->second.textureRect.width   = iGlyphWidth;
      mIt->second.textureRect.height  = m_oPages[uiBold].m_vRows[uiRow+1]-m_oPages[uiBold].m_vRows[uiRow]-1;
      mIt->second.bounds.width    = static_cast<GLfloat>(mIt->second.textureRect.width);
      mIt->second.bounds.height   = static_cast<GLfloat>(mIt->second.textureRect.height);
      iGlyphWidth = 0;
      if (static_cast<GLuint> (sfBits[uiPix+4]) == 255 && static_cast<GLuint> (sfBits[uiPix+5]) == 0 && static_cast<GLuint> (sfBits[uiPix+6]) == 0) {
        uiRow++;
        uiPix = uiWidth*static_cast<GLuint> (m_oPages[uiBold].m_vRows[uiRow]);
        iGlyphX = 1;
      } else {
        iGlyphX++;
      }
      ++mIt;
      if (mIt != mEnd) {
        mIt->second.textureRect.left = iGlyphX;
        mIt->second.textureRect.top = m_oPages[uiBold].m_vRows[uiRow];
        mIt->second.bounds.left = 0;
        mIt->second.bounds.top = 0;
      }
    } else {
      iGlyphWidth++;
      iGlyphX++;
    }
  }

	// Delete the image of the file
	FreeImage_Unload (pfiImage);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean BmpFont::LoadShaderFromFile ( const std::string& szVertFileName, const std::string& szFragFileName ) {
  if (m_psfShader != NULL)
    delete m_psfShader;
  m_psfShader = new sf::Shader ();

  return m_psfShader->loadFromFile (szVertFileName, szFragFileName);
}

////////////////////////////////////////////////////////////
BmpFont& BmpFont::operator = ( const BmpFont& oRight ) {
  m_oPages[0] = oRight.m_oPages[0];
  m_oPages[1] = oRight.m_oPages[1];
  m_iAdvance  = oRight.m_iAdvance;

  return *this;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
const sf::Glyph& BmpFont::GetGlyph ( sf::Uint32 uiCodePoint, GLboolean bBold ) const {
  // Get the page corresponding to the character style
  const GlyphTable& mapGlyphs = m_oPages[static_cast<GLuint> (bBold)].m_mapGlyphs;

  // Search the glyph into the cache
  GlyphTable::const_iterator iter = mapGlyphs.find (uiCodePoint);
  if (iter != mapGlyphs.end ()) {
    // Found: just return it
    return iter->second;
  } else {
    // Not found: we have to load it
    return mapGlyphs.begin ()->second;
  }
}

////////////////////////////////////////////////////////////
GLint BmpFont::GetKerning ( sf::Uint32 uiCodePoint, GLboolean bBold ) const {
  // Special case where uiCodePoint is 0 (null character) or \n (return) or \t (tabulation)
  if (uiCodePoint == 0 || uiCodePoint == '\n' || uiCodePoint == '\t')
    return 0;

  // Return the X advance
  return static_cast<GLint>(GetGlyph (uiCodePoint, bBold).bounds.width) + m_iAdvance;
}

////////////////////////////////////////////////////////////
GLint BmpFont::GetLineSpacing ( void ) const {
  return static_cast<GLint>(GetGlyph (1, GL_FALSE).bounds.height) + 1;
}

////////////////////////////////////////////////////////////
const sf::Texture& BmpFont::GetTexture ( GLboolean bBold ) const {
  return m_oPages[static_cast<GLuint> (bBold)].m_sfTexture;
}

////////////////////////////////////////////////////////////
const sf::Shader* BmpFont::GetShader ( void ) const {
  return m_psfShader;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void BmpFont::Cleanup ( void ) {
  m_oPages[0].m_mapGlyphs.clear ();
  m_oPages[0].m_vRows.clear ();
  m_oPages[1].m_mapGlyphs.clear ();
  m_oPages[1].m_vRows.clear ();
  if (m_psfShader != NULL)
    delete m_psfShader;
}

}
