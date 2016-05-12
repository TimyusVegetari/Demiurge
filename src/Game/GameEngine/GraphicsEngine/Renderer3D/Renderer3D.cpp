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

#include <Game/GameEngine/GraphicsEngine/Renderer3D/Renderer3D.hpp>

////////////////////////////////////////////////////////////
// Structure
////////////////////////////////////////////////////////////

/// Objects3D //////////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer3D::ST_Objects3D::ST_Objects3D ( void ) :
  m_mIndex          (),
  m_uiIdAccumulator (0),
  m_eError          (Error::NONE)
{
}

////////////////////////////////////////////////////////////
Renderer3D::ST_Objects3D::~ST_Objects3D ( void ) {
}

/// RenderLists3D //////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer3D::ST_RenderLists3D::ST_RenderLists3D ( void ) :
  m_mIndex          (),
  m_uiIdAccumulator (0),
  m_eError          (Error::NONE)
{
}

////////////////////////////////////////////////////////////
Renderer3D::ST_RenderLists3D::~ST_RenderLists3D ( void ) {
}

////////////////////////////////////////////////////////////
GLuint Renderer3D::ST_RenderLists3D::CreateRenderList3D ( void ) {
  m_uiIdAccumulator++;
  m_mIndex.insert (Renderer3D::RL3D_Pair (m_uiIdAccumulator, RenderList3D::Ptr (new RenderList3D ())));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Renderer3D::Renderer3D ( OGLManager& oOGLManager, Textures2DManager& oTextures2DManager ) :
  m_oCameraManager      (),
  m_oOGLManager         (oOGLManager),
  m_oTextures2DManager  (oTextures2DManager),
  m_oShadersManager     ()
{
}

////////////////////////////////////////////////////////////
Renderer3D::~Renderer3D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer3D::Initialize ( void ) {
  std::cout << "Renderer 3D : Initializing..." << std::endl;
  GLboolean bSuccess = GL_TRUE;

  // Initialization of the managers.
  bSuccess = m_oShadersManager.Initialize ();

  // Initialization of the textures of the blocks.
  //bSuccess = m_gTexturesManager.InitializeBlockTextures ("data/materials/textures/blocks/blocktextures.xml");

  // Initialization of the meshes.
  //bSuccess = m_gMeshesManager.Initialize ();

  if (bSuccess)
    std::cout << "Renderer 3D : Initialization succeed" << std::endl;
  else
    std::cout << "Renderer 3D : Initialization failed" << std::endl;
  return bSuccess;
}

/// RenderLists3D //////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint Renderer3D::CreateRenderList ( Shaders::ID eShaderID ) {
  return m_stRenderLists[eShaderID].CreateRenderList3D ();
}

////////////////////////////////////////////////////////////
GLboolean Renderer3D::RenderListAddObjectID ( Renderer3D::InsertionType eInsertionType, Shaders::ID eShaderID, GLuint uiRenderListID, Objects3D::Type eObjectType, GLuint uiObjectID, const GLuint uiListedObjectID ) {
  auto mFound = m_stObjects3D[eObjectType].m_mIndex.find (uiObjectID);
  if (mFound == m_stObjects3D[eObjectType].m_mIndex.end ()) {
    CheckIDErrorObject (eObjectType, uiObjectID);

    return GL_FALSE;
  }
  if (eInsertionType == Renderer3D::InsertionType::PUSHBACK)
    (*mFound->second).m_lRenderListIter = m_stRenderLists[eShaderID].m_mIndex[uiRenderListID]->PushBack (eObjectType, uiObjectID);
  else if (eInsertionType == Renderer3D::InsertionType::PUSHFRONT)
    (*mFound->second).m_lRenderListIter = m_stRenderLists[eShaderID].m_mIndex[uiRenderListID]->PushFront (eObjectType, uiObjectID);
  else
    (*mFound->second).m_lRenderListIter = m_stRenderLists[eShaderID].m_mIndex[uiRenderListID]->Insert (eObjectType, uiObjectID, uiListedObjectID);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
Renderer3D::RL3DSize_type Renderer3D::EraseRenderList ( Shaders::ID eShaderID, GLuint uiRenderListID ) {
  auto mFound = m_stRenderLists[eShaderID].m_mIndex.find (uiRenderListID);
  if (mFound == m_stRenderLists[eShaderID].m_mIndex.end ()) {
    CheckIDErrorRenderList (eShaderID, uiRenderListID);
  } else {
    m_stRenderLists[eShaderID].m_mIndex.erase (mFound);
  }

  return m_stRenderLists[eShaderID].m_mIndex.size ();
}

////////////////////////////////////////////////////////////
//void Renderer3D::PerspectiveOGL2 ( gm::RenderWindow& gmRenderWindow ) {
//  glMatrixMode (GL_PROJECTION);
//  glLoadIdentity ();
//  gluPerspective (69.0, static_cast<GLdouble> (gmRenderWindow.GetWidth ())/static_cast<GLdouble> (gmRenderWindow.GetHeight ()), 0.1, 128.0);
//  glMatrixMode (GL_MODELVIEW);
//  glLoadIdentity ();
//}

////////////////////////////////////////////////////////////
void Renderer3D::Render_OGL2 ( Shaders::ID eShaderID, GLuint uiRenderListID, Objects3D::Type eObjectType ) {
  auto mFound = m_stRenderLists[eShaderID].m_mIndex.find (uiRenderListID);
  if (mFound == m_stRenderLists[eShaderID].m_mIndex.end ()) {
    CheckIDErrorRenderList (eShaderID, uiRenderListID);
  } else {
    if ((*mFound->second).Reset (eObjectType)) {
      // Preparing of the needed systems
      Camera& oCamera = m_oCameraManager.GetCamera ();
      ShaderProgram& oShaderProgram = m_oShadersManager.GetShaderProgram (eShaderID);

      if (eShaderID == Shaders::ID::Skybox) {
        // Open the rendering.
        glPushMatrix ();
        glLoadIdentity ();
        gluLookAt (0, 0, 0,
           oCamera.GetLocalFocalisation ().x, oCamera.GetLocalFocalisation ().y, oCamera.GetLocalFocalisation ().z,
           oCamera.GetOrientation ().x, oCamera.GetOrientation ().y, oCamera.GetOrientation ().z);

        // Rendering of the objects for the selected type.
        do {
          Skybox& oSkybox = static_cast<Skybox&> (*m_stObjects3D[eObjectType].m_mIndex[(*mFound->second).GetObjectID (eObjectType)]);
          oSkybox.Draw (m_oTextures2DManager);
        } while ((*mFound->second).Advance (eObjectType));

        // Close the rendering.
        glPopMatrix ();
      } else if (eShaderID == Shaders::ID::Wired) {
        // Open the rendering.
        glPushMatrix ();
        glLoadIdentity ();
        gluLookAt (oCamera.GetPosition ().x, oCamera.GetPosition ().y, oCamera.GetPosition ().z,
           oCamera.GetGlobalFocalisation ().x, oCamera.GetGlobalFocalisation ().y, oCamera.GetGlobalFocalisation ().z,
           oCamera.GetOrientation ().x, oCamera.GetOrientation ().y, oCamera.GetOrientation ().z);

        // Rendering of the objects for the selected type.
        glEnable (GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        do {
          Box& oBox = static_cast<Box&> (*m_stObjects3D[eObjectType].m_mIndex[(*mFound->second).GetObjectID (eObjectType)]);
          oBox.Draw (GL_QUADS);
        } while ((*mFound->second).Advance (eObjectType));
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable (GL_DEPTH_TEST);

        // Close the rendering.
        glPopMatrix ();
      }
    }
  }
}

////////////////////////////////////////////////////////////
void Renderer3D::Render_OGL3 ( Shaders::ID eShaderID, GLuint uiRenderListID, Objects3D::Type eObjectType ) {
  auto mFound = m_stRenderLists[eShaderID].m_mIndex.find (uiRenderListID);
  if (mFound == m_stRenderLists[eShaderID].m_mIndex.end ()) {
    CheckIDErrorRenderList (eShaderID, uiRenderListID);
  } else {
    if ((*mFound->second).Reset (eObjectType)) {
      // Preparing of the needed systems
      Camera& oCamera = m_oCameraManager.GetCamera ();
      ShaderProgram& oShaderProgram = m_oShadersManager.GetShaderProgram (eShaderID);

      if (eShaderID == Shaders::ID::Skybox) {
        // Open the rendering.
        oShaderProgram.EnableShaderProgram ();
        oShaderProgram.SendUnitTexture ("cubemap", 0);
        oShaderProgram.SendCurrentMatrix ("mvpMatrix", oCamera.GetLocalMVP ());

        // Rendering of the objects for the selected type.
        do {
          Skybox& oSkybox = static_cast<Skybox&> (*m_stObjects3D[eObjectType].m_mIndex[(*mFound->second).GetObjectID (eObjectType)]);
          oSkybox.Draw (m_oTextures2DManager);
        } while ((*mFound->second).Advance (eObjectType));

        // Close the rendering.
        oShaderProgram.DisableShaderProgram ();
      } else if (eShaderID == Shaders::ID::Wired) {
        // Open the rendering.
        oShaderProgram.EnableShaderProgram ();
        oShaderProgram.SendCurrentMatrix ("mvpMatrix", oCamera.GetGlobalMVP ());

        // Rendering of the objects for the selected type.
        if (eShaderID == Shaders::ID::Wired) {
          glEnable (GL_DEPTH_TEST);
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        do {
          Box& oBox = static_cast<Box&> (*m_stObjects3D[eObjectType].m_mIndex[(*mFound->second).GetObjectID (eObjectType)]);
          oBox.Draw (GL_QUADS);
        } while ((*mFound->second).Advance (eObjectType));
        if (eShaderID == Shaders::ID::Wired) {
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
          glDisable (GL_DEPTH_TEST);
        }

        // Close the rendering.
        oShaderProgram.DisableShaderProgram ();
      }
    }
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

/// Objects3D //////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer3D::IsEmptyObject3D ( Objects3D::Type eObjectType ) {
	return m_stObjects3D[eObjectType].m_mIndex.empty ();
}

////////////////////////////////////////////////////////////
GLuint Renderer3D::CheckErrorObject ( Objects3D::Type eObject ) {
	return m_stObjects3D[eObject].m_eError;
}

/// RenderLists3D ///////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Renderer3D::IsEmptyRenderList ( Shaders::ID eShaderID ) {
	return m_stRenderLists[eShaderID].m_mIndex.empty ();
}

////////////////////////////////////////////////////////////
RenderList3D& Renderer3D::GetRenderList3D ( Shaders::ID eShaderID, GLuint uiRenderListID ) {
  auto mFound = m_stRenderLists[eShaderID].m_mIndex.find (uiRenderListID);
  if (mFound == m_stRenderLists[eShaderID].m_mIndex.end ()) {
    CheckIDErrorRenderList (eShaderID, uiRenderListID);

    m_stRenderLists[eShaderID].m_mIndex.insert (Renderer3D::RL3D_Pair (uiRenderListID, RenderList3D::Ptr (new RenderList3D ())));
    return (*m_stRenderLists[eShaderID].m_mIndex[uiRenderListID]);
  }
  return (*mFound->second);
}

////////////////////////////////////////////////////////////
GLuint Renderer3D::CheckErrorRenderList ( Shaders::ID eShaderID ) {
	return m_stRenderLists[eShaderID].m_eError;
}

////////////////////////////////////////////////////////////
CameraManager& Renderer3D::GetCameraManager ( void ) {
  return m_oCameraManager;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Renderer3D::CheckIDErrorObject ( Objects3D::Type eObjectType, GLuint uiObjectID ) {
  if (uiObjectID > m_stObjects3D[eObjectType].m_uiIdAccumulator) {
    m_stObjects3D[eObjectType].m_eError = Error::OVERFLOWED_OBJECT;
  } else
    m_stObjects3D[eObjectType].m_eError = Error::UNCONSTRUCTED_OBJECT;
}

////////////////////////////////////////////////////////////
void Renderer3D::CheckIDErrorRenderList ( Shaders::ID eShaderID, GLuint uiRenderListID ) {
  if (uiRenderListID > m_stRenderLists[eShaderID].m_uiIdAccumulator) {
    m_stRenderLists[eShaderID].m_eError = Error::OVERFLOWED_RENDERLIST;
  } else
    m_stRenderLists[eShaderID].m_eError = Error::UNCONSTRUCTED_RENDERLIST;
}
