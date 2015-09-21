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
 * \file GameObject3D.hpp
 * \brief Class for the 3D game objects.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef GAMEOBJECT3D_HPP__
#define GAMEOBJECT3D_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>

////////////////////////////////////////////////////////////
/// \brief Enumeration of types for the game objects 3D.
///
////////////////////////////////////////////////////////////
namespace GameObjects3D {

enum Type {
  None,
  Skybox,
  WiredObject,
  TexturedObject,
  Count
};

}

////////////////////////////////////////////////////////////
/// \brief Class to create game objects like as players,
/// creatures, equipments, vehicules, etc...
///
////////////////////////////////////////////////////////////
class GameObject3D {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<GameObject3D> Ptr;  ///< Unique pointer of 3D game object.

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint    m_uiRenderList3D_ID;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a game object.
    ///
    ////////////////////////////////////////////////////////////
    GameObject3D ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GameObject3D ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the 3D render list identifier to insert the 3D game object.
    ///
    /// \param uiRenderList3D_ID  Identifier of the render list.
    ///
    ////////////////////////////////////////////////////////////
    void SetRenderList3D_ID ( GLuint uiRenderList3D_ID );
};

#endif // GAMEOBJECT_HPP__
