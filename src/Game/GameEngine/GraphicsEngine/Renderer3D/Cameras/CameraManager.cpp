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

#include <Game/GameEngine/GraphicsEngine/Renderer3D/Cameras/CameraManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
CameraManager::CameraManager ( void ) :
  m_mIndex          (),
  m_uiIdAccumulator (0),
  m_uiError         (Error::NONE)
{
}

////////////////////////////////////////////////////////////
CameraManager::~CameraManager ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLuint CameraManager::CreateCamera ( void ) {
  m_uiIdAccumulator++;
  m_mIndex.insert (CameraManager::Pair (m_uiIdAccumulator, Camera::Ptr (new Camera ())));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
void CameraManager::Erase ( GLuint uiCameraID ) {
  auto mFound = m_mIndex.find (uiCameraID);
  if (mFound == m_mIndex.end ()) {
    CheckIDError (uiCameraID);
  } else {
    m_mIndex.erase (mFound);
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean CameraManager::IsEmpty ( void ) {
	return m_mIndex.empty ();
}

////////////////////////////////////////////////////////////
GLuint CameraManager::CheckError ( void ) {
	return m_uiError;
}

////////////////////////////////////////////////////////////
Camera& CameraManager::GetCamera ( GLuint uiCameraID ) {
  auto mFound = m_mIndex.find (uiCameraID);
  if (mFound == m_mIndex.end ()) {
    CheckIDError (uiCameraID);

    m_mIndex.insert (CameraManager::Pair (uiCameraID, Camera::Ptr (new Camera ())));
    return (*m_mIndex[uiCameraID]);
  }
  return (*mFound->second);
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void CameraManager::CheckIDError ( GLuint uiCameraID ) {
  if (uiCameraID > m_uiIdAccumulator) {
    m_uiIdAccumulator = uiCameraID;
    m_uiError = Error::OVERFLOWED_OBJECT;
  } else
    m_uiError = Error::UNCONSTRUCTED_OBJECT;
}
