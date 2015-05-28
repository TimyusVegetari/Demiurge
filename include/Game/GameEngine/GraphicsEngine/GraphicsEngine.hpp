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
 * \file GraphicsEngine.hpp
 * \brief Class for the graphics engine of Demiurge.
 * \author Anthony Acroute
 * \version 0.4
 * \date 2013-2015
 *
 */

#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include "OGLManager.hpp"
#include "Textures2D/Textures2DManager.hpp"
#include "Renderer2D/Renderer2D.hpp"
#include "Renderer3D.hpp"

#include <string>

class GraphicsEngine;

////////////////////////////////////////////////////////////
/// \brief Class for initialising and manage the graphical objects and rendering.
///
////////////////////////////////////////////////////////////
class GraphicsEngine {

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    OGLManager            m_oOGLManager;
    Textures2DManager     m_oTextures2DManager; ///< Textures 2D of the game.
    Renderer2D            m_oRenderer2D;
    Renderer3D            m_oRenderer3D;

    // Time for the graphics mecanic
		GLuint                m_uiPrevElapsedTime;
		GLuint                m_uiFrameDelay;
    GLfloat               m_fFrameDelayInSeconds;
    GLuint                m_uiFrameRate;
    std::string           m_szFrameRate;
    GLuint                m_uiFrameTrigger;
    GLuint                m_uiElapsedFrames;
  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the graphics engine.
    ///
    ////////////////////////////////////////////////////////////
    GraphicsEngine          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the graphics engine.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GraphicsEngine ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Configurate OpenGL context of the graphics engine.
    ///
    /// \param fWidth   Width of the OpenGL context.
    ///        fHeight  Height of the OpenGL context.
    ///        uiDepth  Depth of the OpenGL context.
    ///
    ////////////////////////////////////////////////////////////
    void Configurate ( GLuint uiWidth, GLuint uiHeight, GLuint uiDepth );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the graphics engine.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the frame delay for the graphics mecanic from the frame rate.
    ///
    /// \param uiFrameRate   Frame rate of the graphics mecanic, in frames.
    ///
    ////////////////////////////////////////////////////////////
    void SetFrameRate ( GLuint uiFrameRate );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame delay in frames.
    ///
    /// \return Frame delay value, in frames.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetFrameDelay ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame delay in seconds.
    ///
    /// \return Frame delay value, in seconds.
    ///
    ////////////////////////////////////////////////////////////
    GLfloat GetFrameDelayInSeconds ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Compute the frame rate of the time of graphics mecanic.
    ///
    /// \param uiElapsedTime  Elapsed time to compute the frame rate of the graphics mecanic.
    ///
    ////////////////////////////////////////////////////////////
    void ComputeFrameRate ( GLuint uiElapsedTime );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame rate of the time of graphics mecanic.
    ///
    /// \return Frame rate value.
    ///
    ////////////////////////////////////////////////////////////
    std::string GetFrameRate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Set the frame trigger with the elapsed time.
    ///
    /// \param uiElapsedTime  Elapsed time to permit the update of the trigger.
    ///
    ////////////////////////////////////////////////////////////
    void SetFrameTrigger ( GLuint uiElapsedTime );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame trigger.
    ///
    /// \return Frame trigger value.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetFrameTrigger ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the elapsed frames.
    ///
    /// \return Elapsed frame value.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetElapsedFrames ( void );

    Textures2DManager& GetTextures2DManager ( void );
};

#endif // GRAPHICSENGINE_HPP
