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

#ifndef CAMERA_HPP__
#define CAMERA_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <DRIMI/Mathematics/Config.hpp>
#include <sstream>
#include <memory>

#define DISTMIN 16.f
#define DISTMAX 32.f

////////////////////////////////////////////////////////////
/// \brief Class to create cameras to see the 3D world.
///
////////////////////////////////////////////////////////////
class Camera {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<Camera>  Ptr; ///< Unique pointer of camera.

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    drimi::Vec3f    m_v3fPosition;
    drimi::Vec3f    m_v3fFocalisation;
    drimi::Vec3f    m_v3fOrientation;
    drimi::Vec3f    m_v3fMoveVector;
    GLint           m_iViewportX, m_iViewportY;
    GLsizei         m_iViewportWidth, m_iViewportHeight;
    GLfloat         m_fFovy, m_fRatio, m_fNear, m_fFar;
    GLfloat         m_fPitch, m_fYaw;
    drimi::Mat4x4f  m_m44Mvp, m_m44Model, m_m44View, m_m44Projection;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a camera.
    ///
    ////////////////////////////////////////////////////////////
    Camera ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Constructor with parameters.
    ///
    /// This constructor defines a camera.
    ///
    ////////////////////////////////////////////////////////////
    Camera ( drimi::Vec3f v3fCoord );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the camera.
    ///
    ////////////////////////////////////////////////////////////
    ~Camera ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize MVP matrix to use it.
    ///
    ////////////////////////////////////////////////////////////
    void UseMVP ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Puts the camera in the first person mode.
    ///
    ////////////////////////////////////////////////////////////
    void FocaliseFirstPerson ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Puts the camera in the third person mode.
    ///
    ////////////////////////////////////////////////////////////
    void FocaliseThirdPerson ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Move the camera back and forth according to
    /// the sign of the distance.
    ///
    /// \param fDistance  Value of the distance of the displacement.
    ///
    ////////////////////////////////////////////////////////////
    void MoveForwardAndBack ( GLfloat fDistance );

    ////////////////////////////////////////////////////////////
    /// \brief Move the camera at the top and below according to
    /// the sign of the distance.
    ///
    /// \param fDistance  Value of the distance of the displacement.
    ///
    ////////////////////////////////////////////////////////////
    void MoveUpAndDown ( GLfloat fDistance );

    ////////////////////////////////////////////////////////////
    /// \brief Move the camera to the right or to the left
    /// according to the sign of the distance.
    ///
    /// \param fDistance  Value of the distance of the displacement.
    ///
    ////////////////////////////////////////////////////////////
    void MoveRightAndLeft ( GLfloat fDistance );

    ////////////////////////////////////////////////////////////
    /// \brief Apply the computed move.
    ///
    ////////////////////////////////////////////////////////////
    void ApplyMove ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Turn the camera in the horizontal for first person.
    ///
    /// \param fAngle   Value of the angle of the rotation in radians.
    ///
    ////////////////////////////////////////////////////////////
    void RotationYFirstPerson ( GLfloat fAngle );

    ////////////////////////////////////////////////////////////
    /// \brief Turn the camera in the horizontal for third person.
    ///
    /// \param fAngle   Value of the angle of the rotation in radians.
    ///
    ////////////////////////////////////////////////////////////
    void RotationYThirdPerson ( GLfloat fAngle );

    ////////////////////////////////////////////////////////////
    /// \brief Turn the camera in the vertical for first person.
    ///
    /// \param fAngle   Value of the angle of the rotation in radians.
    ///
    /// \return True if the processing succeeded, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean RotationZXFirstPerson ( GLfloat fAngle );

    ////////////////////////////////////////////////////////////
    /// \brief Turn the camera in the vertical for third person.
    ///
    /// \param fAngle   Value of the angle of the rotation in radians.
    ///
    /// \return True if the processing succeeded, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean RotationZXThirdPerson ( GLfloat fAngle );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Edit coordinates of the camera position.
    ///
    /// \param v3fCoord   Coordinates position.
    ///
    ////////////////////////////////////////////////////////////
    void SetPosition ( drimi::Vec3f v3fCoord );

    ////////////////////////////////////////////////////////////
    /// \brief Edit coordinates of the camera focalisation.
    ///
    /// \param v3fCoord   Coordinates focalisation.
    ///
    ////////////////////////////////////////////////////////////
    void SetFocalisation ( drimi::Vec3f v3fCoord );

    ////////////////////////////////////////////////////////////
    /// \brief Edit coordinates of the camera orientation.
    ///
    /// \param v3fCoord   Coordinates orientation.
    ///
    ////////////////////////////////////////////////////////////
    void SetOrientation ( drimi::Vec3f v3fCoord );

    ////////////////////////////////////////////////////////////
    /// \brief Edit the viewport of the camera.
    ///
    /// \param uiX        X position of the viewport.
    ///        uiY        Y position of the viewport.
    ///        uiWidth    Width of the viewport.
    ///        uiHeight   Height of the viewport.
    ///
    ////////////////////////////////////////////////////////////
    void SetViewport ( GLuint uiX, GLuint uiY, GLuint uiWidth = 16, GLuint uiHeight = 16 );

    ////////////////////////////////////////////////////////////
    /// \brief Edit perspective of the camera.
    ///
    /// \param dFovy    Fovy of the frustum.
    ///        dNear    Nearest point of view.
    ///        dFar     Farest point of view.
    ///
    ////////////////////////////////////////////////////////////
    void SetPerspective ( GLfloat fFovy, GLfloat fNear, GLfloat fFar );

    ////////////////////////////////////////////////////////////
    /// \brief Get coordinates of the camera position.
    ///
    /// \return Position coordinates.
    ///
    ////////////////////////////////////////////////////////////
    drimi::Vec3f& GetPosition ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get coordinates of the camera focalisation.
    ///
    /// \return Focalisation coordinates.
    ///
    ////////////////////////////////////////////////////////////
    drimi::Vec3f& GetFocalisation ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get coordinates of the camera orientation.
    ///
    /// \return Orientation coordinates.
    ///
    ////////////////////////////////////////////////////////////
    drimi::Vec3f& GetOrientation ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get coordinates of the camera position in string.
    ///
    /// \return String to display position coordinates.
    ///
    ////////////////////////////////////////////////////////////
    std::string ToStringPosition ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get coordinates of the camera focalisation in string.
    ///
    /// \return String to display focalisation coordinates.
    ///
    ////////////////////////////////////////////////////////////
    std::string ToStringFocalisation ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get coordinates of the camera orientation in string.
    ///
    /// \return String to display orientation coordinates.
    ///
    ////////////////////////////////////////////////////////////
    std::string ToStringOrientation ( void );
};

#endif // CAMERA_HPP__
