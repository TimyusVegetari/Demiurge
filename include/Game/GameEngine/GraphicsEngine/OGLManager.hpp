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
 * \file OGLManager.hpp
 * \brief Class to manage the usage of OpenGL in the graphics engine.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2013-2015
 *
 */

#ifndef OGLMANAGER_HPP_
#define OGLMANAGER_HPP_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <set>

////////////////////////////////////////////////////////////
/// \brief Class to manage the usage of OpenGL in the graphics engine.
///
////////////////////////////////////////////////////////////
class OGLManager {

  public:
    ////////////////////////////////////////////////////////////
    // Type struct
    ////////////////////////////////////////////////////////////
    struct OGLConfig {
      GLuint  uiWidth,
              uiHeight,
              uiDepth;
    };

  private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    OGLConfig             m_stOGLConfig;
    sf::Context*          m_psfContext;
    std::set<std::string> m_szExtensions;
    GLboolean             m_bErrorGLExt;

  public:
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the OpenGL manager.
    ///
    ////////////////////////////////////////////////////////////
    OGLManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the OpenGL manager.
    ///
    ////////////////////////////////////////////////////////////
    ~OGLManager ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Create the OpenGL context with SFML.
    ///
    ////////////////////////////////////////////////////////////
    void CreateOpenGLContext ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize GLEW.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean InitializeGlew ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check if OpenGL supports the expected version.
    ///
    /// \param dVersionLimit  The expected version.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean CheckGLversion ( const GLdouble dVersionLimit );

    ////////////////////////////////////////////////////////////
    /// \brief Check if OpenGL detected an error in a function.
    ///
    /// \param szExtension  Name of the OpenGL function.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean CheckError ( const std::string& szName );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the OpenGL extensions.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean InitializeGLExtensions ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the support of an OpenGL extension.
    ///        The OpenGL Manager store the error data.
    ///        To get back it, see GetErrorGLExt.
    ///
    /// \param szExtension  Name of the extension.
    ///
    ////////////////////////////////////////////////////////////
    void CheckExtension ( const std::string& szExtension );

    ////////////////////////////////////////////////////////////
    /// \brief Return if no support problem of OpenGL extension was find.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean GetErrorGLExt ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the OpenGL context configuration datas to edit it.
    ///
    /// \return OpenGL context configuration datas.
    ///
    ////////////////////////////////////////////////////////////
    OGLConfig& GetConfig ( void );
};

#endif //OGLMANAGER_HPP_