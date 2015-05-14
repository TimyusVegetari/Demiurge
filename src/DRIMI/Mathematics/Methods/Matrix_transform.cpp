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

#include <DRIMI/Mathematics/Config.hpp>

namespace drimi {

  ////////////////////////////////////////////////////////////
	Mat4x4f Translate ( Mat4x4f const & m4fM, Vec3f const & v3fV ) {
		Mat4x4f m4fResult (m4fM);
		m4fResult[3] = m4fM[0] * v3fV[0] + m4fM[1] * v3fV[1] + m4fM[2] * v3fV[2] + m4fM[3];

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Rotate ( Mat4x4f const & m4fM, GLfloat const & fAngle, Vec3f const & v3fV ) {
#ifdef DRIMI_MATHEMATICS_FORCE_RADIANS
		GLfloat fA = fAngle;
#else
		GLfloat fA = drimi::Radians (fAngle);
#endif
		GLfloat fC = drimi::Cos (fA);
		GLfloat fS = drimi::Sin (fA);

		Vec3f v3fAxis = drimi::Normalize (v3fV);
		Vec3f v3fTemp = (1.f - fC) * v3fAxis;

		Mat4x4f m4fRotate (0.f);
		m4fRotate[0][0] = fC + v3fTemp[0] * v3fAxis[0];
		m4fRotate[0][1] = 0.f + v3fTemp[0] * v3fAxis[1] + fS * v3fAxis[2];
		m4fRotate[0][2] = 0.f + v3fTemp[0] * v3fAxis[2] - fS * v3fAxis[1];

		m4fRotate[1][0] = 0.f + v3fTemp[1] * v3fAxis[0] - fS * v3fAxis[2];
		m4fRotate[1][1] = fC + v3fTemp[1] * v3fAxis[1];
		m4fRotate[1][2] = 0.f + v3fTemp[1] * v3fAxis[2] + fS * v3fAxis[0];

		m4fRotate[2][0] = 0.f + v3fTemp[2] * v3fAxis[0] + fS * v3fAxis[1];
		m4fRotate[2][1] = 0.f + v3fTemp[2] * v3fAxis[1] - fS * v3fAxis[0];
		m4fRotate[2][2] = fC + v3fTemp[2] * v3fAxis[2];

		Mat4x4f m4fResult;
		m4fResult[0] = m4fM[0] * m4fRotate[0][0] + m4fM[1] * m4fRotate[0][1] + m4fM[2] * m4fRotate[0][2];
		m4fResult[1] = m4fM[0] * m4fRotate[1][0] + m4fM[1] * m4fRotate[1][1] + m4fM[2] * m4fRotate[1][2];
		m4fResult[2] = m4fM[0] * m4fRotate[2][0] + m4fM[1] * m4fRotate[2][1] + m4fM[2] * m4fRotate[2][2];
		m4fResult[3] = m4fM[3];

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Scale ( Mat4x4f const & m4fM, Vec3f const & v3fV ) {
		Mat4x4f m4fResult (0.f);
		m4fResult[0] = m4fM[0] * v3fV[0];
		m4fResult[1] = m4fM[1] * v3fV[1];
		m4fResult[2] = m4fM[2] * v3fV[2];
		m4fResult[3] = m4fM[3];

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Ortho ( GLfloat const & fLeft, GLfloat const & fRight, GLfloat const & fBottom, GLfloat const & fTop, GLfloat const & fZNear, GLfloat const & fZFar ) {
		Mat4x4f m4fResult (1.f);
		m4fResult[0][0] = 2.f / (fRight - fLeft);
		m4fResult[1][1] = 2.f / (fTop - fBottom);
		m4fResult[2][2] = -2.f / (fZFar - fZNear);
		m4fResult[3][0] = -(fRight + fLeft) / (fRight - fLeft);
		m4fResult[3][1] = -(fTop + fBottom) / (fTop - fBottom);
		m4fResult[3][2] = -(fZFar + fZNear) / (fZFar - fZNear);

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Ortho ( GLfloat const & fLeft, GLfloat const & fRight, GLfloat const & fBottom, GLfloat const & fTop ) {
		Mat4x4f m4fResult (1.f);
		m4fResult[0][0] = 2.f / (fRight - fLeft);
		m4fResult[1][1] = 2.f / (fTop - fBottom);
		m4fResult[2][2] = -1.f;
		m4fResult[3][0] = -(fRight + fLeft) / (fRight - fLeft);
		m4fResult[3][1] = -(fTop + fBottom) / (fTop - fBottom);

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Frustum ( GLfloat const & fLeft, GLfloat const & fRight, GLfloat const & fBottom, GLfloat const & fTop, GLfloat const & fNearVal, GLfloat const & fFarVal ) {
		Mat4x4f m4fResult (0.f);
		m4fResult[0][0] = (2.f * fNearVal) / (fRight - fLeft);
		m4fResult[1][1] = (2.f * fNearVal) / (fTop - fBottom);
		m4fResult[2][0] = (fRight + fLeft) / (fRight - fLeft);
		m4fResult[2][1] = (fTop + fBottom) / (fTop - fBottom);
		m4fResult[2][2] = -(fFarVal + fNearVal) / (fFarVal - fNearVal);
		m4fResult[2][3] = -1.f;
		m4fResult[3][2] = -(2.f * fFarVal * fNearVal) / (fFarVal - fNearVal);

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f Perspective ( GLfloat const & fFovy, GLfloat const & fAspect, GLfloat const & fZNear, GLfloat const & fZFar ) {
		assert (fAspect != 0.f);
		assert (fZFar != fZNear);

#ifdef DRIMI_MATHEMATICS_FORCE_RADIANS
		GLfloat const fRad = fFovy;
#else
		GLfloat const fRad = drimi::Radians (fFovy);
#endif

		GLfloat fTanHalfFovy = drimi::Tan (fRad / 2.f);
		Mat4x4f m4fResult (0.f);
		m4fResult[0][0] = 1.f / (fAspect * fTanHalfFovy);
		m4fResult[1][1] = 1.f / (fTanHalfFovy);
		m4fResult[2][2] = - (fZFar + fZNear) / (fZFar - fZNear);
		m4fResult[2][3] = - 1.f;
		m4fResult[3][2] = - (2.f * fZFar * fZNear) / (fZFar - fZNear);

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f PerspectiveFov ( GLfloat const & fFov, GLfloat const & fWidth, GLfloat const & fHeight, GLfloat const & fZNear, GLfloat const & fZFar ) {
#ifdef DRIMI_MATHEMATICS_FORCE_RADIANS
		GLfloat fRad = fFov;
#else
		GLfloat fRad = drimi::Radians(fFov);
#endif
		GLfloat fH = drimi::Cos (0.5f * fRad) / drimi::Sin (0.5f * fRad);
		GLfloat fW = fH * fHeight / fWidth; ///todo max(width , Height) / min(width , Height)?

		Mat4x4f m4fResult (0.f);
		m4fResult[0][0] = fW;
		m4fResult[1][1] = fH;
		m4fResult[2][2] = - (fZFar + fZNear) / (fZFar - fZNear);
		m4fResult[2][3] = - 1.f;
		m4fResult[3][2] = - (2.f * fZFar * fZNear) / (fZFar - fZNear);

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f InfinitePerspective ( GLfloat fFovy, GLfloat fAspect, GLfloat fZNear ) {
#ifdef DRIMI_MATHEMATICS_FORCE_RADIANS
		GLfloat const fRange = drimi::Tan (fFovy / 2.f) * fZNear;
#else
		GLfloat const fRange = drimi::Tan (drimi::Radians (fFovy / 2.f)) * fZNear;
#endif
		GLfloat fLeft = -fRange * fAspect;
		GLfloat fRight = fRange * fAspect;
		GLfloat fBottom = -fRange;
		GLfloat fTop = fRange;

		Mat4x4f m4fResult (0.f);
		m4fResult[0][0] = (2.f * fZNear) / (fRight - fLeft);
		m4fResult[1][1] = (2.f * fZNear) / (fTop - fBottom);
		m4fResult[2][2] = -1.f;
		m4fResult[2][3] = -1.f;
		m4fResult[3][2] = -2.f * fZNear;

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f TweakedInfinitePerspective ( GLfloat fFovy, GLfloat fAspect, GLfloat fZNear ) {
#ifdef DRIMI_MATHEMATICS_FORCE_RADIANS
		GLfloat fRange = drimi::Tan (fFovy / 2.f) * fZNear;
#else
		GLfloat fRange = drimi::Tan (drimi::Radians (fFovy / 2.f)) * fZNear;
#endif
		GLfloat fLeft = -fRange * fAspect;
		GLfloat fRight = fRange * fAspect;
		GLfloat fBottom = -fRange;
		GLfloat fTop = fRange;

		Mat4x4f m4fResult (0.f);
		m4fResult[0][0] = (2.f * fZNear) / (fRight - fLeft);
		m4fResult[1][1] = (2.f * fZNear) / (fTop - fBottom);
		m4fResult[2][2] = 0.0001f - 1.f;
		m4fResult[2][3] = -1.f;
		m4fResult[3][2] = -(0.0001f - 2.f) * fZNear;

		return m4fResult;
	}

  ////////////////////////////////////////////////////////////
	Vec3f Project ( Vec3f const & v3fObj, Mat4x4f const & m4fModel, Mat4x4f const & m4fProj, Vec4f const & v4fViewport ) {
		Vec4f v4fTmp = Vec4f (v3fObj, 1.f);
		v4fTmp = m4fModel * v4fTmp;
		v4fTmp = m4fProj * v4fTmp;

		v4fTmp /= v4fTmp.w;
		v4fTmp = v4fTmp * 0.5f + 0.5f;
		v4fTmp[0] = v4fTmp[0] * GLfloat (v4fViewport[2]) + GLfloat (v4fViewport[0]);
		v4fTmp[1] = v4fTmp[1] * GLfloat (v4fViewport[3]) + GLfloat (v4fViewport[1]);

		return Vec3f (v4fTmp);
	}

  ////////////////////////////////////////////////////////////
	Vec3f UnProject ( Vec3f const & v3fWin, Mat4x4f const & m4fModel, Mat4x4f const & m4fProj, Vec4f const & v4fViewport ) {
		Mat4x4f m4fInverse = m4fProj * m4fModel;
		m4fInverse = m4fInverse.Inverse ();

		Vec4f v4fTmp = Vec4f (v3fWin, 1.f);
		v4fTmp.x = (v4fTmp.x - GLfloat (v4fViewport[0])) / GLfloat (v4fViewport[2]);
		v4fTmp.y = (v4fTmp.y - GLfloat (v4fViewport[1])) / GLfloat (v4fViewport[3]);
		v4fTmp = v4fTmp * 2.f - 1.f;

		Vec4f v4fObj = m4fInverse * v4fTmp;
		v4fObj /= v4fObj.w;

		return Vec3f (v4fObj);
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f PickMatrix ( Vec2f const & v2fCenter, Vec2f const & v2fDelta, Vec4f const & v4fViewport ) {
		assert (v2fDelta.x > 0.f && v2fDelta.y > 0.f);
		Mat4x4f m4fResult (1.f);

		if (!(v2fDelta.x > 0.f && v2fDelta.y > 0.f))
			return m4fResult; // Error

		Vec3f v3fTemp (
			(GLfloat (v4fViewport[2]) - 2.f * (v2fCenter.x - GLfloat (v4fViewport[0]))) / v2fDelta.x,
			(GLfloat (v4fViewport[3]) - 2.f * (v2fCenter.y - GLfloat (v4fViewport[1]))) / v2fDelta.y,
			0.f
    );

		// Translate and scale the picked region to the entire window
		m4fResult = drimi::Translate (m4fResult, v3fTemp);
		return drimi::Scale (m4fResult, Vec3f (GLfloat (v4fViewport[2]) / v2fDelta.x, GLfloat (v4fViewport[3]) / v2fDelta.y, 1.f));
	}

  ////////////////////////////////////////////////////////////
	Mat4x4f LookAt ( Vec3f const & v3fEye, Vec3f const & v3fCenter, Vec3f const & v3fUp ) {
		Vec3f v3fF = drimi::Normalize (v3fCenter - v3fEye);
		Vec3f v3fU = drimi::Normalize (v3fUp);
		Vec3f v3fS = drimi::Normalize (drimi::Cross (v3fF, v3fU));
		v3fU = drimi::Cross (v3fS, v3fF);

		Mat4x4f m4fResult (1.f);
		m4fResult[0][0] = v3fS.x;
		m4fResult[1][0] = v3fS.y;
		m4fResult[2][0] = v3fS.z;
		m4fResult[0][1] = v3fU.x;
		m4fResult[1][1] = v3fU.y;
		m4fResult[2][1] = v3fU.z;
		m4fResult[0][2] =-v3fF.x;
		m4fResult[1][2] =-v3fF.y;
		m4fResult[2][2] =-v3fF.z;
		m4fResult[3][0] =-drimi::Dot (v3fS, v3fEye);
		m4fResult[3][1] =-drimi::Dot (v3fU, v3fEye);
		m4fResult[3][2] = drimi::Dot (v3fF, v3fEye);

		return m4fResult;
	}

} // namespace drimi
