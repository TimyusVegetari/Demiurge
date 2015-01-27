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
 * \file BmpText.hpp
 * \brief Class to define a bitmap text.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2013-2015
 *
 */

#ifndef DRIMI_BITMAPFONT_TEXT_HPP__
#define DRIMI_BITMAPFONT_TEXT_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "BmpFont.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

namespace drimi {
////////////////////////////////////////////////////////////
/// \brief Graphical bitmap text can be drawn to a render target
///
////////////////////////////////////////////////////////////
class BmpText : public sf::Drawable, public sf::Transformable {
  private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::String              m_sfString;             ///< String to display
    const BmpFont*          m_pBmpFont;             ///< Font used to display the string
    GLuint                  m_uiGlyphAdvance;       ///< Horizontal space between characters
    GLfloat                 m_fCharacterScale;      ///< Base scale of characters
    sf::Uint32              m_uiStyle;              ///< Text style (see sf::Text::Style enum)
    sf::Color               m_sfColor;              ///< Text color
    mutable sf::VertexArray m_sfVertices;           ///< Vertex array containing the text's geometry
    mutable sf::FloatRect   m_sfBounds;             ///< Bounding rectangle of the text (in local coordinates)
    mutable GLboolean       m_bGeometryNeedUpdate;  ///< Does the geometry need to be recomputed ?

  public:

    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default contructor
    ///
    /// Create a text empty.
    ///
    ////////////////////////////////////////////////////////////
    BmpText ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Construct the text from a string, font and scale
    ///
    /// \param szString         Text assigned to the string
    /// \param oBmpFont         Font used to draw the string
    /// \param fCharacterScale  Case scale of characters
    ///
    ////////////////////////////////////////////////////////////
    BmpText ( const sf::String& sfString, const BmpFont& oBmpFont, GLfloat fCharacterScale = 1.f );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Destruct the text.
    ///
    ////////////////////////////////////////////////////////////
    ~BmpText ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Return the position of the \a index-th character
    ///
    /// This function computes the visual position of a character
    /// from its index in the string. The returned position is
    /// in global coordinates (translation, rotation, scale and
    /// origin are applied).
    /// If \a index is out of range, the position of the end of
    /// the string is returned.
    ///
    /// \param index Index of the character
    ///
    /// \return Position of the character
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f FindCharacterPos ( std::size_t index ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the local bounding rectangle of the entity
    ///
    /// The returned rectangle is in local coordinates, which means
    /// that it ignores the transformations (translation, rotation,
    /// scale, ...) that are applied to the entity.
    /// In other words, this function returns the bounds of the
    /// entity in the entity's coordinate system.
    ///
    /// \return Local bounding rectangle of the entity
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect GetLocalBounds ( void ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global bounding rectangle of the entity
    ///
    /// The returned rectangle is in global coordinates, which means
    /// that it takes in account the transformations (translation,
    /// rotation, scale, ...) that are applied to the entity.
    /// In other words, this function returns the bounds of the
    /// sprite in the global 2D world's coordinate system.
    ///
    /// \return Global bounding rectangle of the entity
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect GetGlobalBounds ( void ) const;

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's string
    ///
    /// A text's string is empty by default.
    ///
    /// \param sfString New string
    ///
    /// \see GetString
    ///
    ////////////////////////////////////////////////////////////
    void SetString ( const sf::String& sfString );

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's font
    ///
    /// The \a font argument refers to a font that must
    /// exist as long as the text uses it. Indeed, the text
    /// doesn't store its own copy of the font, but rather keeps
    /// a pointer to the one that you passed to this function.
    /// If the font is destroyed and the text tries to
    /// use it, the behaviour is undefined.
    ///
    /// \param oBmpFont New font
    ///
    /// \see GetFont
    ///
    ////////////////////////////////////////////////////////////
    void SetFont ( const BmpFont& oBmpFont );

    ////////////////////////////////////////////////////////////
    /// \brief Set the character scale
    ///
    /// The default scale is 1.f.
    ///
    /// \param fScale New character scale
    ///
    /// \see GetCharacterScale
    ///
    ////////////////////////////////////////////////////////////
    void SetCharacterScale ( GLfloat fScale );

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's style
    ///
    /// You can pass a combination of one or more styles, for
    /// example drimi::BmpText::Bold | drimi::BmpText::Italic.
    /// The default style is drimi::BmpText::Regular.
    ///
    /// \param uiStyle New style
    ///
    /// \see GetStyle
    ///
    ////////////////////////////////////////////////////////////
    void SetStyle ( sf::Uint32 uiStyle );

    ////////////////////////////////////////////////////////////
    /// \brief Set the global color of the text
    ///
    /// By default, the text's color is opaque white.
    ///
    /// \param sfColor New color of the text
    ///
    /// \see GetColor
    ///
    ////////////////////////////////////////////////////////////
    void SetColor ( const sf::Color& sfColor );

    ////////////////////////////////////////////////////////////
    /// \brief set the local origin of the object
    ///
    /// The origin of an object defines the center point for
    /// all transformations (position, scale, rotation).
    /// The coordinates of this point must be relative to the
    /// top-left corner of the object, and ignore all
    /// transformations (position, scale, rotation).
    /// The default origin of a transformable object is (0, 0).
    ///
    /// \param x  X coordinate of the new origin
    /// \param y  Y coordinate of the new origin
    ///
    /// \see getOrigin in sf::Transformable
    ///
    ////////////////////////////////////////////////////////////
    inline void SetOrigin ( GLfloat x, GLfloat y ) { sf::Transformable::setOrigin (floorf (x), floorf (y)); }

    ////////////////////////////////////////////////////////////
    /// \brief Get the text's string
    ///
    /// \return Text's string
    ///
    /// \see SetString
    ///
    ////////////////////////////////////////////////////////////
    const sf::String& GetString ( void ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the text's font
    ///
    /// If the text has no font attached, a NULL pointer is returned.
    /// The returned reference is const, which means that you
    /// cannot modify the font when you get it from this function.
    ///
    /// \return Pointer to the text's font
    ///
    /// \see SetFont
    ///
    ////////////////////////////////////////////////////////////
    const BmpFont* GetFont ( void ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the character scale
    ///
    /// \return Scale of the characters
    ///
    /// \see SetCharacterScale
    ///
    ////////////////////////////////////////////////////////////
    GLfloat GetCharacterScale ( void ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the text's style
    ///
    /// \return Text's style
    ///
    /// \see SetStyle
    ///
    ////////////////////////////////////////////////////////////
    sf::Uint32 GetStyle ( void ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global color of the text
    ///
    /// \return Global color of the text
    ///
    /// \see SetColor
    ///
    ////////////////////////////////////////////////////////////
    const sf::Color& GetColor ( void ) const;

  private:

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Draw the text to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Draw the underline
    ///
    ////////////////////////////////////////////////////////////
    void DrawUnderline ( GLfloat fX, GLfloat fY, GLfloat fUnderlineOffset, GLfloat fUnderlineThickness ) const;

    ////////////////////////////////////////////////////////////
    /// \brief Update the text's geometry
    ///
    ////////////////////////////////////////////////////////////
    void UpdateGeometry ( void ) const;
};

} // namespace drimi

#endif // DRIMI_BITMAPFONT_TEXT_HPP__
