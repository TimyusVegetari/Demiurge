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
#include <DRIMI/BitmapFont/BmpText.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace drimi {

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
BmpText::BmpText ( void ) :
  m_sfString            (""),
  m_pBmpFont            (NULL),
  m_uiGlyphAdvance      (1),
  m_fCharacterScale     (1.f),
  m_uiStyle             (sf::Text::Regular),
  m_sfColor             (sf::Color (255, 255, 255)),
  m_sfVertices          (sf::Quads),
  m_sfBounds            (),
  m_bGeometryNeedUpdate (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
BmpText::BmpText ( const sf::String& sfString, const BmpFont& oBmpFont, GLfloat fCharacterScale ) :
  m_sfString            (sfString),
  m_pBmpFont            (&oBmpFont),
  m_uiGlyphAdvance      (1),
  m_fCharacterScale     (fCharacterScale),
  m_uiStyle             (sf::Text::Regular),
  m_sfColor             (sf::Color (255, 255, 255)),
  m_sfVertices          (sf::Quads),
  m_sfBounds            (),
  m_bGeometryNeedUpdate (GL_TRUE)
{
}

////////////////////////////////////////////////////////////
BmpText::~BmpText ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
sf::Vector2f BmpText::FindCharacterPos ( std::size_t index ) const {
  // Make sure that we have a valid font
  if (!m_pBmpFont)
    return sf::Vector2f ();

  // Adjust the index if it's out of range
  if (index > m_sfString.getSize ())
    index = m_sfString.getSize ();

  // Precompute the variables needed by the algorithm
  GLboolean bBold = (m_uiStyle & sf::Text::Style::Bold) != 0;
  GLfloat fHSpace = static_cast<GLfloat> (m_uiGlyphAdvance);
  GLfloat fVSpace = static_cast<GLfloat> (m_pBmpFont->GetLineSpacing ());

  // Compute the position
  sf::Vector2f sfPosition;
  sf::Uint32 uiPrevChar = 0;
  for (std::size_t i=0 ; i<index ; ++i) {
    sf::Uint32 uiCurChar = m_sfString[i];

    // Apply the kerning offset
    sfPosition.x += static_cast<GLfloat> (m_pBmpFont->GetKerning (uiPrevChar, bBold));
    uiPrevChar = uiCurChar;

    // Handle special characters
    switch (uiCurChar) {
      case L' '   : sfPosition.x += fHSpace;
      case L'\t'  : sfPosition.x += fHSpace * 2.f;
      case L'\n'  : sfPosition.y += fVSpace; sfPosition.x = 0.f;
      case L'\v'  : sfPosition.y += fVSpace * 2.f;
      // For regular characters, add the advance offset of the glyph
      default     : sfPosition.x += static_cast<GLfloat> (m_uiGlyphAdvance);
    }
  }

  // Apply scale to the position
  sfPosition *= m_fCharacterScale;

  // Transform the position to global coordinates
  sfPosition = getTransform ().transformPoint (sfPosition);

  return sfPosition;
}

////////////////////////////////////////////////////////////
sf::FloatRect BmpText::GetLocalBounds ( void ) const {
  UpdateGeometry ();

  return m_sfBounds;
}

////////////////////////////////////////////////////////////
sf::FloatRect BmpText::GetGlobalBounds ( void ) const {
  return getTransform ().transformRect (GetLocalBounds ());
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void BmpText::SetString ( const sf::String& sfString ) {
  if (m_sfString != sfString) {
    m_sfString = sfString;
    m_bGeometryNeedUpdate = GL_TRUE;
  }
}

////////////////////////////////////////////////////////////
void BmpText::SetFont ( const BmpFont& oBmpFont ) {
  if (m_pBmpFont != &oBmpFont) {
    m_pBmpFont = &oBmpFont;
    m_bGeometryNeedUpdate = GL_TRUE;
  }
}

////////////////////////////////////////////////////////////
void BmpText::SetStyle ( sf::Uint32 uiStyle ) {
  if (m_uiStyle != uiStyle) {
    m_uiStyle = uiStyle;
    m_bGeometryNeedUpdate = GL_TRUE;
  }
}

////////////////////////////////////////////////////////////
void BmpText::SetCharacterScale ( GLfloat fCharacterScale ) {
  if (m_fCharacterScale != fCharacterScale) {
    m_fCharacterScale = fCharacterScale;
    m_bGeometryNeedUpdate = GL_TRUE;
  }
}

////////////////////////////////////////////////////////////
void BmpText::SetColor ( const sf::Color& sfColor ) {
  if (sfColor != m_sfColor) {
    m_sfColor = sfColor;

    // Change vertex colors directly, no need to update whole geometry
    // (if geometry is updated anyway, we can skip this step)
    if (!m_bGeometryNeedUpdate) {
      for (GLuint uiIter=0 ; uiIter<m_sfVertices.getVertexCount () ; ++uiIter)
        m_sfVertices[uiIter].color = m_sfColor;
    }
  }
}

////////////////////////////////////////////////////////////
const sf::String& BmpText::GetString ( void ) const {
  return m_sfString;
}

////////////////////////////////////////////////////////////
const BmpFont* BmpText::GetFont ( void ) const {
  return m_pBmpFont;
}

////////////////////////////////////////////////////////////
sf::Uint32 BmpText::GetStyle ( void ) const {
  return m_uiStyle;
}

////////////////////////////////////////////////////////////
GLfloat BmpText::GetCharacterScale ( void ) const {
  return m_fCharacterScale;
}

////////////////////////////////////////////////////////////
const sf::Color& BmpText::GetColor ( void ) const {
  return m_sfColor;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void BmpText::draw ( sf::RenderTarget& target, sf::RenderStates states ) const {
  if (m_pBmpFont) {
    UpdateGeometry ();

    GLboolean bBold = (m_uiStyle & sf::Text::Style::Bold) != 0;

    states.transform *= getTransform ();
    states.texture = &m_pBmpFont->GetTexture (bBold);
    states.shader = m_pBmpFont->GetShader ();
    target.draw (m_sfVertices, states);
  }
}

////////////////////////////////////////////////////////////
void BmpText::DrawUnderline ( GLfloat fX, GLfloat fY, GLfloat fUnderlineOffset, GLfloat fUnderlineThickness ) const {
  GLfloat fTop = fY + fUnderlineOffset;
  GLfloat fBottom = fTop + fUnderlineThickness;

  m_sfVertices.append (sf::Vertex (sf::Vector2f (0,  fTop),    m_sfColor, sf::Vector2f (1, 1)));
  m_sfVertices.append (sf::Vertex (sf::Vector2f (fX, fTop),    m_sfColor, sf::Vector2f (1, 1)));
  m_sfVertices.append (sf::Vertex (sf::Vector2f (fX, fBottom), m_sfColor, sf::Vector2f (1, 1)));
  m_sfVertices.append (sf::Vertex (sf::Vector2f (0,  fBottom), m_sfColor, sf::Vector2f (1, 1)));
}

////////////////////////////////////////////////////////////
void BmpText::UpdateGeometry ( void ) const {
  // Do nothing, if geometry has not changed
  if (!m_bGeometryNeedUpdate)
    return;

  // Mark geometry as updated
  m_bGeometryNeedUpdate = GL_FALSE;

  // Clear the previous geometry
  m_sfVertices.clear ();
  m_sfBounds = sf::FloatRect ();

  // No font: nothing to draw
  if (!m_pBmpFont)
    return;

  // No text: nothing to draw
  if (m_sfString.isEmpty ())
    return;

  // Precompute the variables needed by the algorithm
  GLfloat fHSpace   = static_cast<GLfloat> (m_uiGlyphAdvance) * m_fCharacterScale;
  GLfloat fVSpace   = static_cast<GLfloat> (m_pBmpFont->GetLineSpacing ()) * m_fCharacterScale;
  GLfloat fX        = 0.f;
  GLfloat fY        = m_fCharacterScale;

  // Compute values related to the text style
  GLboolean bBold             = (m_uiStyle & sf::Text::Style::Bold) != 0;
  GLboolean bUnderlined       = (m_uiStyle & sf::Text::Style::Underlined) != 0;
  //GLfloat fItalic             = (m_uiStyle & sf::Text::Style::Italic) ? 0.208f : 0.f; // 12 degrees
  GLfloat fUnderlineOffset    = fVSpace - m_fCharacterScale * 3.f;
  GLfloat fUnderlineThickness = m_fCharacterScale * (bBold ? 2.f : 1.f);
  GLfloat fTabulation         = (static_cast<GLfloat> (m_pBmpFont->GetKerning (L' ', bBold)) * m_fCharacterScale + fHSpace) * 2.f;

  // Create one quad for each character
  GLfloat fMinX = m_fCharacterScale;
  GLfloat fMinY = m_fCharacterScale;
  GLfloat fMaxX = 0.f;
  GLfloat fMaxY = 0.f;
  sf::Uint32 uiPrevChar = 0;
  for (std::size_t i=0 ; i<m_sfString.getSize () ; ++i) {
    sf::Uint32 uiCurChar = m_sfString[i];

    // Apply the kerning offset
    fX += static_cast<GLfloat> (m_pBmpFont->GetKerning (uiPrevChar, bBold)) * m_fCharacterScale;
    uiPrevChar = uiCurChar;

    // If we're using the underlined style and there's a new line, draw a line
    if (bUnderlined && (uiCurChar == L'\n'))
      DrawUnderline (fX, fY, fUnderlineOffset, fUnderlineThickness);

    // Handle special characters
    if ((uiCurChar == L' ') || (uiCurChar == L'\t') || (uiCurChar == L'\n') || (uiCurChar == L'\v')) {
      // Update the current bounds (min coordinates)
      fMinX = std::min (fMinX, fX);
      fMinY = std::min (fMinY, fY);

      switch (uiCurChar) {
        case L' '  : fX += fHSpace;           break;
        case L'\t' : fX += fTabulation;       break;
        case L'\n' : fY += fVSpace; fX = 0.f; break;
        case L'\v' : fY += fVSpace * 2.f;     break;
      }

      // Update the current bounds (max coordinates)
      fMaxX = std::max (fMaxX, fX);
      fMaxY = std::max (fMaxY, fY);

      // Next glyph, no need to create a quad for whitespace
      continue;
    }

    // Extract the current glyph's description
    const sf::Glyph& sfGlyph = m_pBmpFont->GetGlyph (uiCurChar, bBold);

    GLfloat fLeft   = static_cast<GLfloat> (sfGlyph.bounds.left) * m_fCharacterScale;
    GLfloat fTop    = static_cast<GLfloat> (sfGlyph.bounds.top) * m_fCharacterScale;
    GLfloat fRight  = static_cast<GLfloat> (sfGlyph.bounds.left + sfGlyph.bounds.width) * m_fCharacterScale;
    GLfloat fBottom = static_cast<GLfloat> (sfGlyph.bounds.top  + sfGlyph.bounds.height) * m_fCharacterScale;

    GLfloat fU1     = static_cast<GLfloat> (sfGlyph.textureRect.left);
    GLfloat fV1     = static_cast<GLfloat> (sfGlyph.textureRect.top);
    GLfloat fU2     = static_cast<GLfloat> (sfGlyph.textureRect.left + sfGlyph.textureRect.width);
    GLfloat fV2     = static_cast<GLfloat> (sfGlyph.textureRect.top  + sfGlyph.textureRect.height);

    // Add a quad for the current character
    m_sfVertices.append (sf::Vertex (sf::Vector2f (fX + fLeft,  fY + fTop),    m_sfColor, sf::Vector2f (fU1, fV1)));
    m_sfVertices.append (sf::Vertex (sf::Vector2f (fX + fRight, fY + fTop),    m_sfColor, sf::Vector2f (fU2, fV1)));
    m_sfVertices.append (sf::Vertex (sf::Vector2f (fX + fRight, fY + fBottom), m_sfColor, sf::Vector2f (fU2, fV2)));
    m_sfVertices.append (sf::Vertex (sf::Vector2f (fX + fLeft,  fY + fBottom), m_sfColor, sf::Vector2f (fU1, fV2)));

    // Update the current bounds
    fMinX = std::min (fMinX, fX + fLeft);
    fMaxX = std::max (fMaxX, fX + fRight);
    fMinY = std::min (fMinY, fY + fTop);
    fMaxY = std::max (fMaxY, fY + fBottom);

    // Advance to the next character
    fX += static_cast<GLfloat> (m_uiGlyphAdvance) * m_fCharacterScale;
  }

  // If we're using the underlined style, add the last line
  if (bUnderlined)
    DrawUnderline (fX+static_cast<GLfloat> (m_pBmpFont->GetKerning (uiPrevChar, bBold)) * m_fCharacterScale, fY, fUnderlineOffset, fUnderlineThickness);

  // Update the bounding rectangle
  m_sfBounds.left = fMinX;
  m_sfBounds.top = fMinY;
  m_sfBounds.width = fMaxX - fMinX;
  m_sfBounds.height = fMaxY - fMinY;
}

} // namespace drimi
