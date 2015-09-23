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
 * \file GOSkybox.hpp
 * \brief Class for the skybox of the world state.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef GOSKYBOX_HPP__
#define GOSKYBOX_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObject3D.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/VertexBufferObject.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/BufferObjects/Tex3DCoordsBufferObject.hpp>
#include <glm/vec3.hpp> // glm::vec3

////////////////////////////////////////////////////////////
/// \brief Class to create the skybox for the world.
///
////////////////////////////////////////////////////////////
class GOSkybox : public GameObject, public GameObject3D, private VertexBufferObject, private Tex3DCoordsBufferObject {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint          m_uiCubeMapID;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the game object.
    ///
    ////////////////////////////////////////////////////////////
    GOSkybox ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GOSkybox ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the game object.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Upgrade all the composants of the game object when
    /// the render target view is resized.
    ///
    ////////////////////////////////////////////////////////////
    void ResizeView ( void ) {};

    ////////////////////////////////////////////////////////////
    /// \brief Update the mvp matrix.
    ///
    /// \param v3fCamLocalFocalisation  Focalisation of the camera.
    ///        v3fCamOrientation        Orientation of the camera.
    ///
    ////////////////////////////////////////////////////////////
    void UpdateMVP ( const glm::vec3& v3fCamLocalFocalisation, const glm::vec3& v3fCamOrientation );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the skybox.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the update of the components of the game object.
    ///
    /// \return True to permit the other game objects to be updated, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Update ( void ) { return GL_TRUE; }

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the state.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) { return GL_TRUE; }

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the game object.
    ///
    /// \return True to permit the inputs of the other game objects to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void ) { return GL_TRUE; }

  private :
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

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
};

#endif // GOSKYBOX_HPP__
