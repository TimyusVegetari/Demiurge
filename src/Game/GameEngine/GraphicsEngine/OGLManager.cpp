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
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/OGLManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
OGLManager::OGLManager ( void ) :
  m_stOGLConfig   {0, 0, 0},
  m_psfContext    (NULL),
  m_szExtensions  (),
  m_bErrorGLExt   (GL_TRUE),
  m_uiVersion     (0)
{
}

////////////////////////////////////////////////////////////
OGLManager::~OGLManager ( void ) {
  if (m_psfContext != NULL)
    delete m_psfContext;
}

////////////////////////////////////////////////////////////
void OGLManager::CreateOpenGLContext ( void ) {
  m_psfContext = new sf::Context (sf::ContextSettings (m_stOGLConfig.uiDepth), m_stOGLConfig.uiWidth, m_stOGLConfig.uiHeight);
}

////////////////////////////////////////////////////////////
GLboolean OGLManager::InitializeGlew ( void ) {
  GLenum eErr = glewInit ();
  if (GLEW_OK != eErr) {
    std::cout << "OGLManager : GLEW failed" << std::endl;
    std::cout << " > Error: " << glewGetErrorString (eErr) << std::endl;
    return GL_FALSE;
  } else
    std::cout << "OGLManager : GLEW succeed" << std::endl;

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean OGLManager::CheckGLversion ( void ) {
  std::cout << "Status: Using GLEW " << glewGetString (GLEW_VERSION) << std::endl;
  std::cout << "Status: Using OpenGL " << glGetString (GL_VERSION) << std::endl;
  std::cout << "Status: Using GLSL " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;

  if (atof ((char*)glGetString (GL_VERSION)) < 3.0) {
    m_uiVersion = 2;
    std::cout << "Warning : OGLManager has detected your OpenGL version is previous to 3.0 !" << std::endl;
    std::cout << " > This game can works with your OpenGL version, but no optimal way and can miss some special effects." << std::endl <<
                 " > If it is possible, update the driver of your graphic card to have a better game experience." << std::endl;
  } else {
    m_uiVersion = 3;
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean OGLManager::CheckError ( const std::string& szName ) {
  if (szName == "glCheckFramebufferStatus") { // Special case for the FBOs
    if (glCheckFramebufferStatus (GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
      return GL_TRUE;
    else
      std::cout << "Invalid Framebuffer value" << std::endl;
  } else {
    GLenum glError = glGetError ();
    switch (glError) {
      case GL_NO_ERROR:
        return GL_TRUE;
        break;
      case GL_INVALID_ENUM:
        std::cout << "Invalid enumerator";
        break;
      case GL_INVALID_VALUE:
        std::cout << "Invalid value";
        break;
      case GL_INVALID_OPERATION:
        std::cout << "Invalid operation";
        break;
      case GL_OUT_OF_MEMORY:
        std::cout << "Out of memory";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION: // Special case for the FBOs
        std::cout << "Invalid Framebuffer operation";
        break;
      default:
        std::cout << "Unknown GL error (" << glError << ")";
        break;
    }
  }
  std::cout << " for " << szName << std::endl;

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean OGLManager::InitializeGLExtensions ( void ) {
  const GLubyte *glExtensionsString = glGetString (GL_EXTENSIONS);

  if (!glExtensionsString) {
    std::cout << "OGLManager : OpenGL extension initialization failed" << std::endl;
    std::cout << " > Error: Getting of extensions impossible !" << std::endl;
    return GL_FALSE;
  } else {
    std::string szExt = std::string ((const char*) glExtensionsString);
    std::string szExtension = "";

    for (std::size_t i=0 ; i < szExt.size () ; i++) {
      if (szExt[i] != ' ')
        szExtension += szExt[i];
      else {
        m_szExtensions.insert (szExtension);
        szExtension = "";
      }
    }
  }
  std::cout << "OGLManager : OpenGL extension initialization succeed" << std::endl;

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void OGLManager::CheckExtension ( const std::string& szExtension ) {
  if (m_szExtensions.find (szExtension) == m_szExtensions.end ()) {
    if (m_bErrorGLExt)
      std::cout << "OGLManager : OpenGL extension check failed" << std::endl;
    std::cout << " > Error : " << szExtension << " is not supported !" << std::endl;
    m_bErrorGLExt = GL_FALSE;
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean OGLManager::GetErrorGLExt ( void ) {
  return m_bErrorGLExt;
}

////////////////////////////////////////////////////////////
OGLManager::OGLConfig& OGLManager::GetConfig ( void ) {
  return m_stOGLConfig;
}

////////////////////////////////////////////////////////////
GLuint OGLManager::GetVersion ( void ) {
  return m_uiVersion;
}
