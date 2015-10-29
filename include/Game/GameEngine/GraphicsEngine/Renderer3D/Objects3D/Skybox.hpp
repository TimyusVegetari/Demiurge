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
 * \file Skybox.hpp
 * \brief Class to define a skybox.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2012-2015
 *
 */

#ifndef VBO_SKYBOX_HPP__
#define VBO_SKYBOX_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/GraphicsEngine/Textures2D/Textures2DManager.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Object3D.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/VertexBufferObject.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/Tex3DCoordsBufferObject.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

////////////////////////////////////////////////////////////
/// \brief Class to create a sky around the player.
///
////////////////////////////////////////////////////////////
class Skybox : public Object3D, private VertexBufferObject, Tex3DCoordsBufferObject {

  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint    m_uiCubeMapID;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a skybox.
    ///
    ////////////////////////////////////////////////////////////
    Skybox ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the skybox.
    ///
    ////////////////////////////////////////////////////////////
    ~Skybox ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the identifier of the cube map texture.
    ///
    /// \param uiTextureID  Identifier of the texture.
    ///
    ////////////////////////////////////////////////////////////
    void SetCubeMapID ( const GLuint uiTextureID );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the VBO datas (Vertex and textures coordinates).
    ///
    ////////////////////////////////////////////////////////////
    virtual void InitializeDatas ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the VBO.
    ///
    /// \return True if initialization succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean InitializeVBO ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the skybox.
    ///
    /// \param oTextures2DManager   The manager to get the texture of the skybox.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( Textures2DManager& oTextures2DManager );
};

#endif // VBO_SKYBOX_HPP__
