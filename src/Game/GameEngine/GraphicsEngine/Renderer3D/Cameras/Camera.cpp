////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2014-2015 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file Camera.hpp
 * \brief Class for the 3D cameras of the game.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2011-2015
 *
 */

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Cameras/Camera.hpp>

////////////////////////////////////////////////////////////
Camera::Camera ( void ) :
  m_v3fPosition       (),
  m_v3fLocalFocalisation  (0.f, 0.f, DISTMAX),
  m_v3fGlobalFocalisation (m_v3fLocalFocalisation),
  m_v3fOrientation    (0.f, 1.f, 0.f),
  m_v3fMoveVector     (),
  m_iViewportX        (0),
  m_iViewportY        (0),
  m_iViewportWidth    (0),
  m_iViewportHeight   (0),
  m_fFovy             (0.0),
  m_fRatio            (0.0),
  m_fNear             (0.0),
  m_fFar              (0.0),
  m_fPitch            (0.f),
  m_fYaw              (0.f),
  m_m44LocalMvp       (),
  m_m44GlobalMvp      (),
  m_m44Model          (),
  m_m44LocalView      (),
  m_m44GlobalView     (),
  m_m44Projection     ()
{
}

////////////////////////////////////////////////////////////
Camera::Camera ( drimi::Vec3f v3fCoord ) :
  m_v3fPosition       (v3fCoord),
  m_v3fLocalFocalisation  (drimi::Vec3f (0.f, 0.f, DISTMAX)),
  m_v3fGlobalFocalisation (v3fCoord + m_v3fLocalFocalisation),
  m_v3fOrientation    (0.f, 1.f, 0.f),
  m_v3fMoveVector     (),
  m_iViewportX        (0),
  m_iViewportY        (0),
  m_iViewportWidth    (0),
  m_iViewportHeight   (0),
  m_fFovy             (0.0),
  m_fRatio            (0.0),
  m_fNear             (0.0),
  m_fFar              (0.0),
  m_fPitch            (0.f),
  m_fYaw              (0.f),
  m_m44LocalMvp       (),
  m_m44GlobalMvp      (),
  m_m44Model          (),
  m_m44LocalView      (),
  m_m44GlobalView     (),
  m_m44Projection     ()
{
}

////////////////////////////////////////////////////////////
Camera::~Camera ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Camera::UseMVP ( void ) {
  glViewport (m_iViewportX, m_iViewportY, m_iViewportWidth, m_iViewportHeight);
  // Remember, matrix multiplication is the other way around
  m_m44GlobalMvp  = m_m44Projection * m_m44GlobalView * m_m44Model;
  m_m44LocalMvp   = m_m44Projection * m_m44LocalView * m_m44Model;
}

////////////////////////////////////////////////////////////
void Camera::FocaliseFirstPerson ( void ) {
  m_m44GlobalView = drimi::LookAt (
      m_v3fPosition,            // Camera position in World Space
      m_v3fGlobalFocalisation,  // and looks at the origin
      m_v3fOrientation          // Head is up (set to 0,-1,0 to look upside-down)
  );
  m_m44LocalView = drimi::LookAt (
      drimi::Vec3f (0.f, 0.f, 0.f), // Camera position to zero
      m_v3fLocalFocalisation,       // and looks at the origin
      m_v3fOrientation              // Head is up (set to 0,-1,0 to look upside-down)
  );
}

////////////////////////////////////////////////////////////
void Camera::FocaliseThirdPerson ( void ) {
  m_m44GlobalView = drimi::LookAt (
      -m_v3fGlobalFocalisation, // Camera position behind the observer
      m_v3fPosition,            // and looks at the observer
      m_v3fOrientation          // Head is up (set to 0,-1,0 to look upside-down)
  );
}

////////////////////////////////////////////////////////////
void Camera::MoveForwardAndBack ( GLfloat fDistance ) {
  m_v3fMoveVector += drimi::Normalize (m_v3fLocalFocalisation) * fDistance;
}

////////////////////////////////////////////////////////////
void Camera::MoveUpAndDown ( GLfloat fDistance ) {
  m_v3fMoveVector += m_v3fOrientation * fDistance;
}

////////////////////////////////////////////////////////////
void Camera::MoveRightAndLeft ( GLfloat fDistance ) {
  drimi::Vec3f v3fMoveVector (m_v3fLocalFocalisation.x, 0.f, m_v3fLocalFocalisation.z);
  drimi::Vec3f v3fVerticalAxis (m_v3fOrientation.x, m_v3fOrientation.y, m_v3fOrientation.z);
  m_v3fMoveVector += drimi::Cross (v3fVerticalAxis, drimi::Normalize (v3fMoveVector) * fDistance);
}

////////////////////////////////////////////////////////////
void Camera::ApplyMove ( void ) {
  m_v3fPosition           += m_v3fMoveVector;
  m_v3fGlobalFocalisation += m_v3fMoveVector;
  m_v3fLocalFocalisation  += m_v3fMoveVector;
  m_v3fMoveVector         = drimi::Vec3f ();
}

////////////////////////////////////////////////////////////
void Camera::RotationYFirstPerson ( GLfloat fAngle ) {
  SetFocalisation (drimi::Vec3f (((m_v3fLocalFocalisation.x)*drimi::Cos (fAngle) -
                                  (m_v3fLocalFocalisation.z)*drimi::Sin (fAngle))+
                                 m_v3fPosition.x,
                                 m_v3fGlobalFocalisation.y,
                                 ((m_v3fLocalFocalisation.x)*drimi::Sin (fAngle) +
                                  (m_v3fLocalFocalisation.z)*drimi::Cos (fAngle))+
                                 m_v3fPosition.z));
}

////////////////////////////////////////////////////////////
void Camera::RotationYThirdPerson ( GLfloat fAngle ) {
  SetPosition (drimi::Vec3f (((m_v3fPosition.x-m_v3fGlobalFocalisation.x)*drimi::Cos (fAngle) -
                              (m_v3fPosition.z-m_v3fGlobalFocalisation.z)*drimi::Sin (fAngle))+
                             m_v3fGlobalFocalisation.x,
                             m_v3fPosition.y,
                             ((m_v3fPosition.x-m_v3fGlobalFocalisation.x)*drimi::Sin (fAngle) +
                              (m_v3fPosition.z-m_v3fGlobalFocalisation.z)*drimi::Cos (fAngle))+
                             m_v3fGlobalFocalisation.z));
}

////////////////////////////////////////////////////////////
void Camera::RotationZXFirstPerson ( GLfloat fAngle ) {
  GLfloat fRadius;

  // Computing of the radius of the local focalisation
  fRadius = drimi::Length (m_v3fLocalFocalisation);
  // Computing of the pitch (horizontal angle)
  if (m_v3fLocalFocalisation.x == 0.f)
    m_fPitch = 1.f;
  else
    m_fPitch = drimi::Atan (m_v3fLocalFocalisation.z/m_v3fLocalFocalisation.x);
  if (m_v3fLocalFocalisation.x < 0.f) m_fPitch += DRIMI_fPI;
  else if (m_v3fLocalFocalisation.z < 0.f) m_fPitch += 2.f*DRIMI_fPI;

  // Computing of the yaw (vertical angle)
  m_fYaw = drimi::Asin (m_v3fLocalFocalisation.y/fRadius) + fAngle;
  if (m_fYaw > DRIMI_fPI/2.f) m_fYaw = DRIMI_fPI/2.f;
  else if (m_fYaw < -DRIMI_fPI/2.f) m_fYaw = -DRIMI_fPI/2.f;

  // Computing of P after rotation
  m_v3fLocalFocalisation = fRadius * drimi::Vec3f (drimi::Cos (m_fPitch)*drimi::Cos (m_fYaw), drimi::Sin (m_fYaw), drimi::Sin (m_fPitch)*drimi::Cos (m_fYaw));
  m_v3fGlobalFocalisation = m_v3fLocalFocalisation + m_v3fPosition;
}

////////////////////////////////////////////////////////////
void Camera::RotationZXThirdPerson ( GLfloat fAngle ) {
  GLfloat fRadius;
  drimi::Vec3f P = m_v3fPosition - m_v3fGlobalFocalisation;

  fRadius = drimi::Length (P);
  m_fPitch = drimi::Acos (P.z/fRadius);
  if (P.x == 0.f)
    m_fYaw = 1.f;
  else
    m_fYaw = drimi::Atan (P.y/P.x);

  m_fPitch += fAngle;
  if (m_fPitch <= 0.f) m_fPitch = 0.00001f;
  else if (m_fPitch >= DRIMI_fPI) m_fPitch = DRIMI_fPI-0.00001f;

  P = fRadius * drimi::Vec3f (drimi::Sin (m_fPitch)*drimi::Cos (m_fYaw), drimi::Sin (m_fPitch)*drimi::Sin (m_fYaw), drimi::Cos (m_fPitch)) + m_v3fGlobalFocalisation;
  SetPosition (P);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Camera::SetPosition ( drimi::Vec3f v3fCoord ) {
  m_v3fPosition = v3fCoord;
}

////////////////////////////////////////////////////////////
void Camera::SetFocalisation ( drimi::Vec3f v3fCoord ) {
  m_v3fGlobalFocalisation = v3fCoord;
  m_v3fLocalFocalisation = m_v3fGlobalFocalisation - m_v3fPosition;
}

////////////////////////////////////////////////////////////
void Camera::SetOrientation ( drimi::Vec3f v3fCoord ) {
  m_v3fOrientation = v3fCoord;
}

////////////////////////////////////////////////////////////
void Camera::SetViewport ( GLuint uiX, GLuint uiY, GLuint uiWidth, GLuint uiHeight ) {
  if (uiWidth < 16)
    m_iViewportWidth = 16;
  else
    m_iViewportWidth = static_cast<GLsizei> (uiWidth);
  if (uiHeight < 16)
    m_iViewportHeight = 16;
  else
    m_iViewportHeight = static_cast<GLsizei> (uiHeight);
  m_iViewportX = static_cast<GLint> (uiX);
  m_iViewportY = static_cast<GLint> (uiY);
}

////////////////////////////////////////////////////////////
void Camera::SetPerspective ( GLfloat fFovy, GLfloat fNear, GLfloat fFar ) {
  if (fFovy <= 0.f || fFovy > 360.f)
    m_fFovy = 45.f;
  else
    m_fFovy = fFovy;
  if (fNear <= 0.f || fNear > fFar)
    m_fNear = 1.f;
  else
    m_fNear = fNear;
  if (fFar <= 0.f || fNear > fFar)
    m_fFar = 100.f;
  else
    m_fFar = fFar;

  // Projection matrix : A° Field of View, B:C ratio, display range : D unit <-> E units
  m_m44Projection = drimi::Perspective (m_fFovy, static_cast<GLfloat> (m_iViewportWidth)/static_cast<GLfloat> (m_iViewportHeight), m_fNear, m_fFar);
  // Model matrix : an identity matrix (model will be at the origin)
  m_m44Model    = drimi::Mat4x4f (1.0f); // Changes for each model !

  m_fPitch = 0.f;
  m_fYaw = 0.f;
}

////////////////////////////////////////////////////////////
drimi::Vec3f& Camera::GetPosition ( void ) {
  return m_v3fPosition;
}

////////////////////////////////////////////////////////////
drimi::Vec3f& Camera::GetFocalisation ( void ) {
  return m_v3fGlobalFocalisation;
}

////////////////////////////////////////////////////////////
drimi::Vec3f& Camera::GetOrientation ( void ) {
  return m_v3fOrientation;
}

////////////////////////////////////////////////////////////
std::string Camera::ToStringPosition ( void ) {
  std::ostringstream oss;
  oss << m_v3fPosition.x << ", " << m_v3fPosition.y << ", " << m_v3fPosition.z;
  return oss.str ();
}

////////////////////////////////////////////////////////////
std::string Camera::ToStringFocalisation ( void ) {
  std::ostringstream oss;
  oss << m_v3fGlobalFocalisation.x << ", " << m_v3fGlobalFocalisation.y << ", " << m_v3fGlobalFocalisation.z;
  return oss.str ();
}

////////////////////////////////////////////////////////////
std::string Camera::ToStringOrientation ( void ) {
  std::ostringstream oss;
  oss << m_v3fOrientation.x << ", " << m_v3fOrientation.y << ", " << m_v3fOrientation.z;
  return oss.str ();
}

////////////////////////////////////////////////////////////
drimi::Vec3f& Camera::GetMoveVector ( void ) {
  return m_v3fMoveVector;
}

////////////////////////////////////////////////////////////
drimi::Mat4x4f& Camera::GetGlobalMVP ( void ) {
  return m_m44GlobalMvp;
}

////////////////////////////////////////////////////////////
drimi::Mat4x4f& Camera::GetLocalMVP ( void ) {
  return m_m44LocalMvp;
}
