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
 * \file Renderer3D.hpp
 * \brief Class for the renderer 3D of the graphics engine.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2015
 *
 */

#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include "RenderList3D.hpp"
//#include "Render3D.hpp"
//#include <Game/GameEngine/RenderTargets/RenderWindow.hpp>
#include "Cameras/CameraManager.hpp"
#include "../OGLManager.hpp"
#include "Shaders/ShadersManager.hpp"
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Objects3D/Skybox.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Objects3D/Box.hpp>

////////////////////////////////////////////////////////////
/// \brief Class for initialising and manage the 3D objects and 3D rendering.
///
////////////////////////////////////////////////////////////
class Renderer3D {

    ////////////////////////////////////////////////////////////
    // Enumeration
    ////////////////////////////////////////////////////////////
    enum Error {
      NONE,
      UNCONSTRUCTED_OBJECT,
      OVERFLOWED_OBJECT,
      UNCONSTRUCTED_RENDERLIST,
      OVERFLOWED_RENDERLIST
    };

  public :
    enum InsertionType {
      PUSHBACK,
      PUSHFRONT,
      INSERT
    };

  private :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::pair<GLuint, RenderList3D::Ptr>            RL3D_Pair;      ///< std::pair of render list pointers.
    typedef std::pair<GLuint, Object3D::Ptr>                O3D_Pair;       ///< std::pair of 3d objects pointers.
    typedef std::map<GLuint, RenderList3D::Ptr>::size_type  RL3DSize_type;  ///< Size_type of the list of 3D objects identifiers

    ////////////////////////////////////////////////////////////
    // Structure
    ////////////////////////////////////////////////////////////
    struct ST_Objects3D {
      std::map<GLuint,
          Object3D::Ptr>      m_mIndex;           ///< Index of 3D objects pointers.
      GLuint                  m_uiIdAccumulator;  ///< Greater identifier generated since the begin
      Error                   m_eError;           ///< Error value if an error arose.

      ST_Objects3D  ( void );
      ~ST_Objects3D ( void );
      template <typename T>
      GLuint AddObject3D ( void );
    };

    struct ST_RenderLists3D {
      std::map<GLuint,
          RenderList3D::Ptr>  m_mIndex;           ///< Index of render list pointers.
      GLuint                  m_uiIdAccumulator;  ///< Greater identifier generated since the begin
      Error                   m_eError;           ///< Error value if an error arose.

      ST_RenderLists3D  ( void );
      ~ST_RenderLists3D ( void );
      GLuint CreateRenderList3D ( void );
    };

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ST_Objects3D            m_stObjects3D[Objects3D::Type::Count];  ///< Array of objects 3D by types.
    ST_RenderLists3D        m_stRenderLists[Shaders::ID::Count]; ///< Array of render list by types.
    CameraManager           m_oCameraManager;                       ///< Manager for 3D cameras.
    OGLManager&             m_oOGLManager;                          ///< Manager for OpenGL.
    Textures2DManager&      m_oTextures2DManager;                   ///< Manager for the textures.
  public :
    ShadersManager          m_oShadersManager;                      ///< Manager for shaders.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the renderer 3D.
    ///
    /// \param oOGLManager          Instance of the manager for OpenGL.
    ///        oTextures2DManager   Instance of the manager for textures.
    ///
    ////////////////////////////////////////////////////////////
    Renderer3D          ( OGLManager& oOGLManager, Textures2DManager& oTextures2DManager );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the renderer 3D.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Renderer3D ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the renderer 3D.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( void );

    /// Objects3D //////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3D object and return its identifier.
    ///
    /// \tparam T   Class which inherit from the 3D object.
    ///
    /// \param eObjectType  Type of 3D object.
    ///
    /// \return Identifier of the 3D object.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint AddObject3D ( Objects3D::Type eObjectType );

    /// RenderLists3D //////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Create a render list and return its identifier.
    ///
    /// \param eShaderID  Type of 3D render.
    ///
    /// \return Identifier of the render list.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CreateRenderList ( Shaders::ID eShaderID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3D object identifier in a render list.
    ///
    /// \param eInsertionType     Type of insertion (PushBack, PushFront or Insert).
    ///        eShaderID          Type of render list.
    ///        uiRenderListID     Identifier of the render list.
    ///        eObjectType        Type of 3D object.
    ///        uiObjectID         Identifier of the 3D object to insert.
    ///        uiListedObjectID   Identifier of the 3D object before which insert the object.
    ///
    /// \return True if insertion succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean RenderListAddObjectID ( Renderer3D::InsertionType eInsertionType,
                                      Shaders::ID eShaderID,
                                      GLuint uiRenderListID,
                                      Objects3D::Type eObjectType,
                                      GLuint uiObjectID,
                                      const GLuint uiListedObjectID = 0 );

    ////////////////////////////////////////////////////////////
    /// \brief Erase a render list.
    ///
    /// \param eShaderID        Type of render list.
    ///        uiRenderListID   Identifier of the render list.
    ///
    /// \return New size of the list.
    ///
    ////////////////////////////////////////////////////////////
    RL3DSize_type EraseRenderList ( Shaders::ID eShaderID, GLuint uiRenderListID );

    ////////////////////////////////////////////////////////////
    /// \brief Prepare the perspective projection of the render for OpenGL 2.
    ///
    /// \param gmRenderWindow   Render window to render.
    ///
    ////////////////////////////////////////////////////////////
    //void PerspectiveOGL2 ( gm::RenderWindow& gmRenderWindow );

    ////////////////////////////////////////////////////////////
    /// \brief Render the content of the list identified by its type for OpenGL 2.
    ///
    /// \param eShaderID        Type of the 3D render.
    ///        uiRenderListID   Identifier of the 3D render list.
    ///        eObjectType      Type of the 3D objects.
    ///
    ////////////////////////////////////////////////////////////
    void Render_OGL2 ( Shaders::ID eShaderID, GLuint uiRenderListID, Objects3D::Type eObjectType );

    ////////////////////////////////////////////////////////////
    /// \brief Render the content of the list identified by its type for OpenGL 3.
    ///
    /// \param eShaderID        Type of the 3D render.
    ///        uiRenderListID   Identifier of the 3D render list.
    ///        eObjectType      Type of the 3D objects.
    ///
    ////////////////////////////////////////////////////////////
    void Render_OGL3 ( Shaders::ID eShaderID, GLuint uiRenderListID, Objects3D::Type eObjectType );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    /// Objects3D //////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list of objects 3D is empty.
    ///
    /// \param eObjectType  Type of 3D object.
    ///
    /// \return True if the list of objects 3D is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmptyObject3D ( Objects3D::Type eObjectType );

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified 3D object.
    ///
    /// \tparam T   Class which inherit from the 3D object.
    ///
    /// \param eObjectType      Type of 3D object.
    ///        uiRenderListID   Identifier of the render list.
    ///
    /// \return Instance of the identified 3D object.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetObject3D ( Objects3D::Type eObjectType, GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error for 3D objects.
    ///
    /// \param eRenderType      Type of 3D render.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckErrorObject ( Objects3D::Type eObject );

    /// RenderLists3D //////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list of render lists is empty.
    ///
    /// \param eShaderID    Type of 3D render.
    ///
    /// \return True if the list of render lists is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmptyRenderList ( Shaders::ID eShaderID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified render list.
    ///
    /// \param eShaderID        Type of 3D render.
    ///        uiRenderListID   Identifier of the render list.
    ///
    /// \return Instance of the identified render list.
    ///
    ////////////////////////////////////////////////////////////
    RenderList3D& GetRenderList3D ( Shaders::ID eShaderID, GLuint uiRenderListID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error for 3D render lists.
    ///
    /// \param eShaderID        Type of 3D render.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckErrorRenderList ( Shaders::ID eShaderID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the manager of 3D cameras.
    ///
    /// \param eObjectType  Type of 3D object.
    ///
    /// \return Instance of the manager of 3D cameras.
    ///
    ////////////////////////////////////////////////////////////
    CameraManager& GetCameraManager ( void );

  private :
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Check what type of error arose.
    ///
    /// \param eObjectType  Type of 3D object.
    ///        uiObjectID   Identifier of 3D object which make an error.
    ///
    ////////////////////////////////////////////////////////////
    void CheckIDErrorObject ( Objects3D::Type eObjectType, GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Check what type of error arose.
    ///
    /// \param eShaderID        Type of 3D render.
    ///        uiRenderListID   Identifier of render list which make an error.
    ///
    ////////////////////////////////////////////////////////////
    void CheckIDErrorRenderList ( Shaders::ID eShaderID, GLuint uiRenderListID );

};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
GLuint Renderer3D::ST_Objects3D::AddObject3D ( void ) {
  m_uiIdAccumulator++;
  m_mIndex.insert (Renderer3D::O3D_Pair (m_uiIdAccumulator, Object3D::Ptr (new T ())));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
template <typename T>
GLuint Renderer3D::AddObject3D ( Objects3D::Type eObjectType ) {
  return m_stObjects3D[eObjectType].AddObject3D<T> ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
T& Renderer3D::GetObject3D ( Objects3D::Type eObjectType, GLuint uiObjectID ) {
  auto mFound = m_stObjects3D[eObjectType].m_mIndex.find (uiObjectID);
  if (mFound == m_stObjects3D[eObjectType].m_mIndex.end ()) {
    CheckIDErrorObject (eObjectType, uiObjectID);

    m_stObjects3D[eObjectType].m_mIndex.insert (Renderer3D::O3D_Pair (uiObjectID, Object3D::Ptr (new Object3D ())));
    return static_cast<T&> (*m_stObjects3D[eObjectType].m_mIndex[uiObjectID]);
  }
  return static_cast<T&> (*mFound->second);
}

#endif // RENDERER2D_HPP
