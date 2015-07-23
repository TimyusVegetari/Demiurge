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
 * \file VertexBufferObject.hpp
 * \brief Class to define a VBO.
 * \author Anthony Acroute
 * \version 0.4
 * \date 2013-2015
 *
 */

#ifndef VERTEXBUFFEROBJECT_HPP__
#define VERTEXBUFFEROBJECT_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/VertexArray.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/IndexArray.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to define the base of the VBOs.
///
////////////////////////////////////////////////////////////
class VertexBufferObject {

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::string       m_szTypeName;   ///< A name to display the type of VBO
                                      ///  if is necessary (ex. Cube, Sphere, etc...).
    VertexArray       m_oVertex;
    IndexArray        m_oIndex;

  public:
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a VBO.
    ///
    ////////////////////////////////////////////////////////////
    VertexBufferObject          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the VBO.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~VertexBufferObject ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the VBO datas (Vertex, normale, etc...).
    ///
    ////////////////////////////////////////////////////////////
    virtual void InitializeDatas ( void ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the VBO.
    ///
    /// \return True if initialization succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean InitializeVBO ( void ) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Generate the OpenGL buffers.
    ///
    /// \param iNoError   Variable to check if no error is detected.
    ///
    ////////////////////////////////////////////////////////////
    void GenBuffers ( GLint &iNoError );

    ////////////////////////////////////////////////////////////
    /// \brief Send the VBO datas to the graphic card.
    ///
    /// \param iNoError   Variable to check if no error is detected.
    ///
    ////////////////////////////////////////////////////////////
    void SendDatas ( GLint &iNoError );

    ////////////////////////////////////////////////////////////
    /// \brief Delete the OpenGL buffers.
    ///
    ////////////////////////////////////////////////////////////
    void DeleteBuffers ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Delete the VBO datas.
    ///
    ////////////////////////////////////////////////////////////
    void DeleteDatas ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the type name of the VBO.
    ///
    /// \return The Type name of the VBO.
    ///
    ////////////////////////////////////////////////////////////
    std::string GetTypeName ( void );

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Active the vertex pointer of OpenGL.
    ///
    /// \return True if activation succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean ActiveVertexPointer ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Bind the index of the VBO.
    ///
    /// \return The index datas size if binding succeeded, 0 if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLsizei BindIndex ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Render the VBO (vertex and index).
    ///
    /// \param eMode    Specifies what kind of primitives to render.
    ///                 Symbolic constants : GL_POINTS, GL_LINE_STRIP,
    ///                 GL_TRIANGLE_STRIP, GL_QUADS, etc...
    ///
    ////////////////////////////////////////////////////////////
    void Render ( GLenum eMode );
};

#endif // VERTEXBUFFEROBJECT_HPP__
