////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2015 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file RenderList3D.hpp
 * \brief Class for the list of 3D objects to render.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2015
 *
 */

#ifndef RENDERLIST3D_HPP
#define RENDERLIST3D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Object3D.hpp>
#include <list>

////////////////////////////////////////////////////////////
/// \brief Class to make a list of render for the 2D objects.
///
////////////////////////////////////////////////////////////
class RenderList3D {

  private :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::list<GLuint>::size_type        Size_type;      ///< Size_type of the list of 3D objects identifiers
    typedef std::list<GLuint>::iterator         Iter;           ///< Iterator of the list of 3D objects identifiers
  public :
    typedef std::unique_ptr<RenderList3D>       Ptr;            ///< Unique pointer of render list 3D.

    ////////////////////////////////////////////////////////////
    // Structure
    ////////////////////////////////////////////////////////////
    struct ST_Identifiers {
      std::list<GLuint>           m_lList;          ///< List of 3D objects identifiers.
      Iter                        m_lListIter;      ///< Internal iterator to path the list of 3D objects pointers.

      ST_Identifiers  ( void );
      ~ST_Identifiers ( void );
    };

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ST_Identifiers    m_stIdentifiers[Objects3D::Type::Count];  ///< Array of 3D objects identifiers.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the render list 3D.
    ///
    ////////////////////////////////////////////////////////////
    RenderList3D          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the render list 3D.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderList3D ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3d object at the end of the list.
    ///
    /// \param eTypeID          Identifier of the type of the 3d object.
    ///        uiObjectID       Identifier of the 3d object to add.
    ///
    /// \return An iterator to the 3D object.
    ///
    ////////////////////////////////////////////////////////////
    Iter PushBack ( Objects3D::Type eTypeID, GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3d object at the begin of the list.
    ///
    /// \param eTypeID          Identifier of the type of the 3d object.
    ///        uiObjectID       Identifier of the 3d object to add.
    ///
    /// \return An iterator to the 3D object.
    ///
    ////////////////////////////////////////////////////////////
    Iter PushFront ( Objects3D::Type eTypeID, GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3d object after another 3d object in the list.
    ///
    /// \param eTypeID            Identifier of the type of the 3d object.
    ///        uiListedObjectID   Identifier of the preview 3d object.
    ///        uiObjectID         Identifier of the game object to insert.
    ///
    /// \return An iterator to the 3D object.
    ///
    ////////////////////////////////////////////////////////////
    Iter Insert ( Objects3D::Type eTypeID, const GLuint uiListedObjectID, GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Erase a 3d object in the list.
    ///
    /// \param eTypeID            Identifier of the type of the 3d object.
    ///        uiListedObjectID   Identifier of the 3d object to erase.
    ///
    /// \return New size of the list.
    ///
    ////////////////////////////////////////////////////////////
    Size_type Erase ( Objects3D::Type eTypeID, const GLuint uiListedObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Reset the internal iterator.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return True if the internal iterator isn't at the end of the list, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Reset ( Objects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Increment the internal iterator.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return True if the internal iterator isn't at the end of the list, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Advance ( Objects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list is empty.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return True if the list is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmpty ( Objects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the current 3d object identifier stored in the internal iterator.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return The 3d object identifier stored in the internal iterator.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetObjectID ( Objects3D::Type eTypeID );
};

#endif // RENDERLIST3D_HPP
