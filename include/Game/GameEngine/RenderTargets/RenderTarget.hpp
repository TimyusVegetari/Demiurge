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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file RenderTarget.hpp
 * \brief Class to add some functionalities to sf::RenderTarget.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef GAME_RENDERTARGET_HPP__
#define GAME_RENDERTARGET_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to add some functionalities to sf::RenderTarget.
///
////////////////////////////////////////////////////////////
namespace gm {  ///< Corresponds to the word "game".

class RenderTarget {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Vector2u  m_v2uMinimalSize;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a render target.
    ///
    ////////////////////////////////////////////////////////////
    RenderTarget ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the render target.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderTarget ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the minimal size of the target.
    ///
    /// \param uiWidth    Minimal width of the target
    ///        uiHeight   Minimal height of the target
    ///
    ////////////////////////////////////////////////////////////
    void SetMinimalSize ( GLuint uiWidth, GLuint uiHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the target.
    ///
    /// \param uiWidth    Width of the target
    ///        uiHeight   Height of the target
    ///
    /// \return Vector of the legal size
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2u GetLegalSize ( GLuint uiWidth, GLuint uiHeight );
};

}

#endif // GAME_RENDERTARGET_HPP__
