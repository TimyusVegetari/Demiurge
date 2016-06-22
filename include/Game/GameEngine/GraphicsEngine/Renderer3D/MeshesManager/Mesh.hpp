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
 * \file Mesh.hpp
 * \brief Class for the 3D meshes of the game.
 * \author Anthony Acroute
 * \version 0.4
 * \date 2016
 *
 */

#ifndef MESH_HPP__
#define MESH_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include "../BufferObjects/VertexBufferObject.hpp"
#include "../BufferObjects/NormalBufferObject.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to create meshes of the 3d objects.
///
////////////////////////////////////////////////////////////
class Mesh {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<Mesh>  Ptr; ///< Unique pointer of mesh.

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::string         m_szTypeName;           ///< A name to display the type of mesh
                                                ///  if is necessary (ex. Cube, Sphere, etc...).
    VertexBufferObject  m_oVertexBufferObject;
    NormalBufferObject  m_oNormalBufferObject;

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
    Mesh ( void );

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
    Mesh ( std::string szTypeName,
           GLfloat* fVertexDatasArray, GLsizei iVertexDatasArraySize,
           GLuint* uiIndexDatasArray, GLsizei iIndexDatasArraySize,
           GLfloat* fNormalDatasArray, GLsizei iNormalDatasArraySize );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the mesh.
    ///
    ////////////////////////////////////////////////////////////
    ~Mesh ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the mesh.
    ///
    /// \return True if initialization succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the mesh.
    ///
    /// \param eMode  Display mode with OpenGL
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( GLenum eMode );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the type name of the mesh.
    ///
    /// \return The Type name of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    std::string GetTypeName ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the length of the vertex of the mesh.
    ///
    /// \return The length of the vertex of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei GetVertexDatasLength ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the vertex datas array size of the mesh.
    ///
    /// \return The vertex datas array size of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei GetVertexDatasSize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the vertex step of the mesh.
    ///
    /// \return The vertex step of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLint GetVertexStep ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the vertex datas array of the mesh.
    ///
    /// \return The vertex datas array of the mesh (read-only).
    ///
    ////////////////////////////////////////////////////////////
    const GLfloat* GetVertexDatas ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the length of the index of the mesh.
    ///
    /// \return The length of the index of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei GetIndexDatasLength ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the index datas array size of the mesh.
    ///
    /// \return The index datas array size of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei GetIndexDatasSize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the index step of the mesh.
    ///
    /// \return The index step of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLint GetIndexStep ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the index datas array of the mesh (read-only).
    ///
    /// \return The index datas array of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    const GLuint* GetIndexDatas ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the length of the normale of the mesh.
    ///
    /// \return The length of the normale of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei GetNormalDatasLength ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the normale datas array size of the mesh.
    ///
    /// \return The normale datas array size of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei GetNormalDatasSize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the normal step of the mesh.
    ///
    /// \return The normal step of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    GLint GetNormalStep ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the normale datas array of the mesh (read-only).
    ///
    /// \return The normale datas array of the mesh.
    ///
    ////////////////////////////////////////////////////////////
    const GLfloat* GetNormalDatas ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get a string to display vertex of the mesh.
    ///
    /// \param uiPosition   Position of the vertex
    ///
    /// \return A vertex of the mesh in string.
    ///
    ////////////////////////////////////////////////////////////
    std::string ToStringVertex ( GLuint uiPosition );

    ////////////////////////////////////////////////////////////
    /// \brief Get a string to display normale of the mesh.
    ///
    /// \param uiPosition   Position of the normale
    ///
    /// \return A normale of the mesh in string.
    ///
    ////////////////////////////////////////////////////////////
    std::string ToStringNormal ( GLuint uiPosition );
};

#endif // MESH_HPP__
