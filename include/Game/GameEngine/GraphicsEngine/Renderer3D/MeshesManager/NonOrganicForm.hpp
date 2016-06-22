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
// A big part of the code in this file is inspired by the book
// "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file NonOrganicForm.hpp
 * \brief Class for the non-organic form meshes.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2016
 *
 */

#ifndef NONORGANICFORM_HPP__
#define NONORGANICFORM_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include "Mesh.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to create meshes of the 3d objects.
///
////////////////////////////////////////////////////////////
class NonOrganicForm : public Mesh {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<NonOrganicForm>  Ptr; ///< Unique pointer of non-organic form mesh.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a mesh.
    ///
    ////////////////////////////////////////////////////////////
    NonOrganicForm ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a mesh.
    ///
    /// \param szTypeName             Type name of the mesh
    ///        fVertexDatasArray      Vertex datas array.
    ///        iVertexDatasArraySize  Size of the vertex datas array.
    ///        uiIndexDatasArray      Index datas array.
    ///        iIndexDatasArraySize   Size of the index datas array.
    ///        fNormalDatasArray      Normal datas array.
    ///        iNormalDatasArraySize  Size of the normal datas array.
    ///
    ////////////////////////////////////////////////////////////
    NonOrganicForm ( std::string szTypeName,
                     GLfloat* fVertexDatasArray, GLsizei iVertexDatasArraySize,
                     GLuint* uiIndexDatasArray, GLsizei iIndexDatasArraySize,
                     GLfloat* fNormalDatasArray, GLsizei iNormalDatasArraySize );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the mesh.
    ///
    ////////////////////////////////////////////////////////////
    ~NonOrganicForm ( void );
};

#endif // NONORGANICFORM_HPP__
