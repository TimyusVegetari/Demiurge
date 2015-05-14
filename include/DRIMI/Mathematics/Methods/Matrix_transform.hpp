////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Mathematics.
// Copyright (C) 2014 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file Matrix_transform.hpp
 * \brief Methods to transform the matrix.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014
 *
 */

#ifndef DRIMI_MATHEMATICS_Matrix_transform
#define DRIMI_MATHEMATICS_Matrix_transform

#if defined(DRIMI_MATHEMATICS_MESSAGES)
# pragma message("DRIMI: DRIMI_MATHEMATICS_Matrix_transform extension included")
#endif

namespace drimi {

  ////////////////////////////////////////////////////////////
  /// \brief Builds a translation 4x4 matrix created from a vector of 3 components.
  ///
  /// \return Translated 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Translate (
    Mat4x4f const & m4fM,
    Vec3f const & v3fV
  );

  ////////////////////////////////////////////////////////////
  /// \brief Builds a rotation 4x4 matrix created from an axis vector and an angle.
  ///
  /// \return Rotated 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Rotate (
    Mat4x4f const & m4fM,
    GLfloat const & fAngle,
    Vec3f const & v3fAxis
  );

  ////////////////////////////////////////////////////////////
  /// \brief Builds a scale 4x4 matrix created from 3 scalars.
  ///
  /// \return Scaled 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Scale (
    Mat4x4f const & m4fM,
    Vec3f const & v3fV
  );

  ////////////////////////////////////////////////////////////
  /// \brief Creates a matrix for an orthographic parallel viewing volume.
  ///
  /// \return Orthographic parallel viewing volume 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Ortho (
    GLfloat const & fLeft,
    GLfloat const & fRight,
    GLfloat const & fBottom,
    GLfloat const & fTop,
    GLfloat const & fZNear,
    GLfloat const & fZFar
  );

  ////////////////////////////////////////////////////////////
  /// \brief Creates a matrix for an orthographic parallel viewing volume.
  ///
  /// \return Orthographic parallel viewing volume 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Ortho (
    GLfloat const & fLeft,
    GLfloat const & fRight,
    GLfloat const & fBottom,
    GLfloat const & fTop
  );

  ////////////////////////////////////////////////////////////
  /// \brief Creates a frustum matrix.
  ///
  /// \return Frustum 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Frustum (
    GLfloat const & fLeft,
    GLfloat const & fRight,
    GLfloat const & fBottom,
    GLfloat const & fTop,
    GLfloat const & fNear,
    GLfloat const & fFar
  );

  ////////////////////////////////////////////////////////////
  /// \brief Creates a matrix for a symetric perspective-view frustum.
  ///
  /// \return Perspective-view frustum 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f Perspective (
    GLfloat const & fFovy,
    GLfloat const & fAspect,
    GLfloat const & fNear,
    GLfloat const & fFar
  );

  ////////////////////////////////////////////////////////////
  /// \brief Builds a perspective projection matrix based on a field of view.
  ///
  /// \return Perspective projection 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f PerspectiveFov (
    GLfloat const & fFov,
    GLfloat const & fWidth,
    GLfloat const & fHeight,
    GLfloat const & fNear,
    GLfloat const & fFar
  );

  ////////////////////////////////////////////////////////////
  /// \brief Creates a matrix for a symmetric perspective-view frustum with far plane at infinite.
  ///
  /// \return Infinite perspective 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f InfinitePerspective (
    GLfloat fFovy, GLfloat fAspect, GLfloat fNear
  );

  ////////////////////////////////////////////////////////////
  /// \brief Creates a matrix for a symetric perspective-view frustum with far plane at infinite for graphics har...
  ///
  /// \return Tweaked infinite perspective 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f TweakedInfinitePerspective (
    GLfloat fFovy, GLfloat fAspect, GLfloat fNear
  );

  ////////////////////////////////////////////////////////////
  /// \brief Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
  ///
  /// \return Window coordinates of the 3D world coordinates.
  ///
  ////////////////////////////////////////////////////////////
  Vec3f Project (
    Vec3f const & v3fObj,
    Mat4x4f const & m4fModel,
    Mat4x4f const & m4fProj,
    Vec4f const & v4fViewport
  );

  ////////////////////////////////////////////////////////////
  /// \brief Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
  ///
  /// \return 3D world coordinates of window coordinates.
  ///
  ////////////////////////////////////////////////////////////
  Vec3f UnProject (
    Vec3f const & v3fWin,
    Mat4x4f const & m4fModel,
    Mat4x4f const & m4fProj,
    Vec4f const & v4fViewport
  );

  ////////////////////////////////////////////////////////////
  /// \brief Define a picking region.
  ///
  /// \return Picked 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f PickMatrix (
    Vec2f const & v2fCenter,
    Vec2f const & v2fDelta,
    Vec4f const & v4fViewport
  );

  ////////////////////////////////////////////////////////////
  /// \brief Build a look at view matrix.
  ///
  /// \return Look At 4x4 matrix.
  ///
  ////////////////////////////////////////////////////////////
  Mat4x4f LookAt (
    Vec3f const & v3fEye,
    Vec3f const & v3fCenter,
    Vec3f const & v3fUp
  );

} // namespace drimi

#endif // DRIMI_MATHEMATICS_Matrix_transform
