////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Noise.
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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <DRIMI/Noise/Perlin/Perlin3D.hpp>

#include <iostream>

namespace drimi {
namespace noise {

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Perlin3D::Perlin3D ( void ) :
  m_uiWidth       (0),
  m_uiHeight      (0),
  m_uiSurface     (0),
  m_uiDepth       (0),
  m_uiWidthMax    (0),
  m_uiHeightMax   (0),
  m_uiSurfaceMax  (0),
  m_uiDepthMax    (0),
  m_uiSeed        (0),
  m_dWaveLengthX  (0.0),
  m_dWaveLengthY  (0.0),
  m_dWaveLengthZ  (0.0),
  m_uiOctaves     (0),
  m_dRand         (),
  m_dDatas        ()
{
}

////////////////////////////////////////////////////////////
Perlin3D::~Perlin3D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Perlin3D::Initialize ( GLuint uiWidthPow, GLuint uiHeightPow, GLuint uiDepthPow, GLuint uiSeed, GLuint uiWaveLengthX, GLuint uiWaveLengthY, GLuint uiWaveLengthZ, GLuint uiOctaves, GLboolean bRepeatable ) {
  m_uiWidth       = static_cast<GLuint> (pow (2.0, static_cast<GLdouble>(uiWidthPow)));
  m_uiHeight      = static_cast<GLuint> (pow (2.0, static_cast<GLdouble>(uiHeightPow)));
  m_uiSurface     = m_uiWidth * m_uiHeight;
  m_uiDepth       = static_cast<GLuint> (pow (2.0, static_cast<GLdouble>(uiDepthPow)));
  m_uiWidthMax    = static_cast<GLuint> (ceil (m_uiWidth * pow (2.0, static_cast<GLdouble>(uiOctaves-1)) / uiWaveLengthX)) + 3;
  m_uiHeightMax   = static_cast<GLuint> (ceil (m_uiHeight * pow (2.0, static_cast<GLdouble>(uiOctaves-1)) / uiWaveLengthY)) + 3;
  m_uiSurfaceMax  = m_uiWidthMax * m_uiHeightMax;
  m_uiDepthMax    = static_cast<GLuint> (ceil (m_uiDepth * pow (2.0, static_cast<GLdouble>(uiOctaves-1)) / uiWaveLengthZ)) + 3;
  m_uiSeed        = uiSeed;
  m_dWaveLengthX  = static_cast<GLdouble> (uiWaveLengthX);
  m_dWaveLengthY  = static_cast<GLdouble> (uiWaveLengthY);
  m_dWaveLengthZ  = static_cast<GLdouble> (uiWaveLengthZ);
  m_uiOctaves     = uiOctaves;

  srand (m_uiSeed);
  m_dRand.resize (m_uiSurfaceMax * m_uiDepthMax);

  for (GLuint uiI = 0 ; uiI < m_dRand.size () ; uiI++)
    m_dRand[uiI] = static_cast<GLdouble> (rand ()) / RAND_MAX;
  if (bRepeatable) {
    GLdouble dWidth = static_cast<GLdouble> (m_uiWidth), dHeight = static_cast<GLdouble> (m_uiHeight), dDepth = static_cast<GLdouble> (m_uiDepth);
    GLdouble dFrequency = 1.0;
    for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
      GLdouble  dIncrementX = dFrequency / m_dWaveLengthX,
                dIncrementY = dFrequency / m_dWaveLengthY,
                dIncrementZ = dFrequency / m_dWaveLengthZ,
                dIndexX = dWidth*dIncrementX,
                dIndexY = dHeight*dIncrementY,
                dIndexZ = dDepth*dIncrementZ;
      GLuint  uiIndexX = static_cast<GLuint> (dIndexX),
              uiIndexY = static_cast<GLuint> (dIndexY),
              uiIndexZ = static_cast<GLuint> (dIndexZ),
              uiIndexX1 = uiIndexX+1, uiIndexX2 = uiIndexX+2,
              uiIndexY1 = uiIndexY+1, uiIndexY2 = uiIndexY+2,
              uiIndexZ1 = uiIndexZ+1, uiIndexZ2 = uiIndexZ+2;
      for (GLdouble dZ = 0.0 ; dZ < dIndexZ+3 ; dZ+=dIncrementZ)
        for (GLdouble dY = 0.0 ; dY < dIndexY+3 ; dY+=dIncrementY) {
          GLuint  uiY = static_cast<GLuint> (dY),
                  uiZ = static_cast<GLuint> (dZ);
          SetRand (uiIndexX , uiY, uiZ, GetRand (0, uiY, uiZ));
          SetRand (uiIndexX1, uiY, uiZ, GetRand (1, uiY, uiZ));
          SetRand (uiIndexX2, uiY, uiZ, GetRand (2, uiY, uiZ));
        }
      for (GLdouble dZ = 0.0 ; dZ < dIndexZ+3 ; dZ+=dIncrementZ)
        for (GLdouble dX = 0.0 ; dX < dIndexX+3 ; dX+=dIncrementX) {
          GLuint  uiX = static_cast<GLuint> (dX),
                  uiZ = static_cast<GLuint> (dZ);
          SetRand (uiX, uiIndexY , uiZ, GetRand (uiX, 0, uiZ));
          SetRand (uiX, uiIndexY1, uiZ, GetRand (uiX, 1, uiZ));
          SetRand (uiX, uiIndexY2, uiZ, GetRand (uiX, 2, uiZ));
        }
      for (GLdouble dY = 0.0 ; dY < dIndexY+3 ; dY+=dIncrementY)
        for (GLdouble dX = 0.0 ; dX < dIndexX+3 ; dX+=dIncrementX) {
          GLuint  uiX = static_cast<GLuint> (dX),
                  uiY = static_cast<GLuint> (dY);
          SetRand (uiX, uiY, uiIndexZ , GetRand (uiX, uiY, 0));
          SetRand (uiX, uiY, uiIndexZ1, GetRand (uiX, uiY, 1));
          SetRand (uiX, uiY, uiIndexZ2, GetRand (uiX, uiY, 2));
        }

      dFrequency *= 2.0;
    }
  }
}

////////////////////////////////////////////////////////////
void Perlin3D::CreateMatrix ( void ) {
  m_dDatas.resize (m_uiOctaves);
  GLuint uiLength = m_dRand.size ();
  for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
    m_dDatas[uiOctave].resize (uiLength);
    for (GLuint uiI = 0 ; uiI < uiLength ; uiI++)
      m_dDatas[uiOctave][uiI] = m_dRand[uiI];
    uiLength /= 2;
  }
}

////////////////////////////////////////////////////////////
GLuint Perlin3D::GetMatrixWidth ( GLuint uiOctave ) {
  if (uiOctave == 0)
    return m_uiWidthMax;
  else
    return m_uiWidthMax / (2*uiOctave);
}

////////////////////////////////////////////////////////////
GLuint Perlin3D::GetMatrixHeight ( GLuint uiOctave ) {
  if (uiOctave == 0)
    return m_uiHeightMax;
  else
    return m_uiHeightMax / (2*uiOctave);
}

////////////////////////////////////////////////////////////
GLuint Perlin3D::GetMatrixDepth ( GLuint uiOctave ) {
  if (uiOctave == 0)
    return m_uiDepthMax;
  else
    return m_uiDepthMax / (2*uiOctave);
}

////////////////////////////////////////////////////////////
GLuint Perlin3D::GetMatrixLength ( GLuint uiOctave ) {
  return m_dDatas[uiOctave].size ();
}

////////////////////////////////////////////////////////////
GLdouble* Perlin3D::GetMatrix ( GLuint uiOctave ) {
  GLdouble* dDatas = NULL;

  if (uiOctave < m_uiOctaves && m_dDatas.size () != 0 && m_dDatas[uiOctave].size () != 0) {
    dDatas = new GLdouble[m_dDatas[uiOctave].size ()];
    for (GLuint uiIndex = 0 ; uiIndex < m_dDatas[uiOctave].size () ; uiIndex++)
      dDatas[uiIndex] = m_dDatas[uiOctave][uiIndex];
  }

  return dDatas;
}

////////////////////////////////////////////////////////////
GLdouble* Perlin3D::GetInterpolation ( GLuint uiOctave, GLdouble dPersistance, Perlin3D::Mode eMode ) {
  GLdouble* dDatas = new GLdouble[m_uiSurface*m_uiDepth];
  GLdouble  dSum = 0.0,
            dAmplitude,
            dFrequency;

  if (uiOctave == 0) {
    dAmplitude = 1.0;
    dFrequency = 1.0;
  } else {
    dAmplitude = pow (dPersistance, static_cast<GLdouble> (uiOctave));
    dFrequency = pow (2.0, static_cast<GLdouble>(uiOctave));
  }
  for (GLuint uiZ = 0 ; uiZ < m_uiDepth ; uiZ++)
    for (GLuint uiY = 0 ; uiY < m_uiHeight ; uiY++)
      for (GLuint uiX = 0 ; uiX < m_uiWidth ; uiX++) {
        dSum = dAmplitude * GenerateNoise (static_cast<GLdouble> (uiX)*dFrequency, static_cast<GLdouble> (uiY)*dFrequency, static_cast<GLdouble> (uiZ)*dFrequency, eMode);
        if (dAmplitude == 1.0)
          dDatas[uiZ * m_uiSurface + uiY * m_uiWidth + uiX] = dSum;
        else
          dDatas[uiZ * m_uiSurface + uiY * m_uiWidth + uiX] = dSum * (1.0 - dPersistance) / (1.0 - dAmplitude);
      }

  return dDatas;
}

////////////////////////////////////////////////////////////
GLdouble Perlin3D::GeneratePerlin ( GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dPersistance, Perlin3D::Mode eMode ) {
  GLdouble  dSum = 0.0,
            dAmplitude = 1.0,
            dFrequency = 1.0;

  for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
    dSum += dAmplitude * GenerateNoise (dX*dFrequency, dY*dFrequency, dZ*dFrequency, eMode);
    dAmplitude *= dPersistance;
    dFrequency += dFrequency;
  }

  if (dAmplitude == 1.0)
    return dSum / m_uiOctaves;
  return dSum * (1.0 - dPersistance) / (1.0 - dAmplitude);
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Perlin3D::SetRand ( GLuint uiX, GLuint uiY, GLuint uiZ, GLdouble dValue ) {
  m_dRand[uiZ * m_uiSurfaceMax + uiY * m_uiWidthMax + uiX] = dValue;
}

////////////////////////////////////////////////////////////
GLdouble Perlin3D::GetRand ( GLuint uiX, GLuint uiY, GLuint uiZ ) {
  return m_dRand[uiZ * m_uiSurfaceMax + uiY * m_uiWidthMax + uiX];
}

////////////////////////////////////////////////////////////
GLdouble Perlin3D::GenerateNoise ( GLdouble dX, GLdouble dY, GLdouble dZ, Perlin3D::Mode eMode ) {
  GLdouble  dIndexX = dX / m_dWaveLengthX,
            dIndexY = dY / m_dWaveLengthY,
            dIndexZ = dZ / m_dWaveLengthZ;
  GLuint uiIndexX = static_cast<GLuint> (dIndexX)+1,
         uiIndexY = static_cast<GLuint> (dIndexY)+1,
         uiIndexZ = static_cast<GLuint> (dIndexZ)+1,
         uiIndexX_1 = uiIndexX-1, uiIndexX1 = uiIndexX+1, uiIndexX2 = uiIndexX+2,
         uiIndexY_1 = uiIndexY-1, uiIndexY1 = uiIndexY+1, uiIndexY2 = uiIndexY+2,
         uiIndexZ_1 = uiIndexZ-1, uiIndexZ1 = uiIndexZ+1, uiIndexZ2 = uiIndexZ+2;
	GLdouble dInterpolation = 0.0;

  if (eMode == Perlin3D::Mode::LINEAR ) {
    dInterpolation = interpolation::Linear3D (GetRand (uiIndexX, uiIndexY , uiIndexZ ), GetRand (uiIndexX1, uiIndexY , uiIndexZ ),
																							GetRand (uiIndexX, uiIndexY1, uiIndexZ ), GetRand (uiIndexX1, uiIndexY1, uiIndexZ ),
																							GetRand (uiIndexX, uiIndexY , uiIndexZ1), GetRand (uiIndexX1, uiIndexY , uiIndexZ1),
																							GetRand (uiIndexX, uiIndexY1, uiIndexZ1), GetRand (uiIndexX1, uiIndexY1, uiIndexZ1),
																							fmod (dIndexX, 1.0), fmod (dIndexY, 1.0), fmod (dIndexZ, 1.0));
  } else if (eMode == Perlin3D::Mode::COSINE ) {
    dInterpolation = interpolation::Cosine3D (GetRand (uiIndexX, uiIndexY , uiIndexZ ), GetRand (uiIndexX1, uiIndexY , uiIndexZ ),
																							GetRand (uiIndexX, uiIndexY1, uiIndexZ ), GetRand (uiIndexX1, uiIndexY1, uiIndexZ ),
																							GetRand (uiIndexX, uiIndexY , uiIndexZ1), GetRand (uiIndexX1, uiIndexY , uiIndexZ1),
																							GetRand (uiIndexX, uiIndexY1, uiIndexZ1), GetRand (uiIndexX1, uiIndexY1, uiIndexZ1),
																							fmod (dIndexX, 1.0), fmod (dIndexY, 1.0), fmod (dIndexZ, 1.0));
  } else if (eMode == Perlin3D::Mode::CUBIC ) {
    dInterpolation = interpolation::Cubic3D (GetRand (uiIndexX_1, uiIndexY_1, uiIndexZ_1), GetRand (uiIndexX  , uiIndexY_1, uiIndexZ_1), GetRand (uiIndexX1, uiIndexY_1, uiIndexZ_1), GetRand (uiIndexX2, uiIndexY_1, uiIndexZ_1),
																						 GetRand (uiIndexX_1, uiIndexY  , uiIndexZ_1), GetRand (uiIndexX  , uiIndexY  , uiIndexZ_1), GetRand (uiIndexX1, uiIndexY  , uiIndexZ_1), GetRand (uiIndexX2, uiIndexY  , uiIndexZ_1),
																						 GetRand (uiIndexX_1, uiIndexY1 , uiIndexZ_1), GetRand (uiIndexX  , uiIndexY1 , uiIndexZ_1), GetRand (uiIndexX1, uiIndexY1 , uiIndexZ_1), GetRand (uiIndexX2, uiIndexY1 , uiIndexZ_1),
																						 GetRand (uiIndexX_1, uiIndexY2 , uiIndexZ_1), GetRand (uiIndexX  , uiIndexY2 , uiIndexZ_1), GetRand (uiIndexX1, uiIndexY2 , uiIndexZ_1), GetRand (uiIndexX2, uiIndexY2 , uiIndexZ_1),
																						 GetRand (uiIndexX_1, uiIndexY_1, uiIndexZ  ), GetRand (uiIndexX  , uiIndexY_1, uiIndexZ  ), GetRand (uiIndexX1, uiIndexY_1, uiIndexZ  ), GetRand (uiIndexX2, uiIndexY_1, uiIndexZ  ),
																						 GetRand (uiIndexX_1, uiIndexY  , uiIndexZ  ), GetRand (uiIndexX  , uiIndexY  , uiIndexZ  ), GetRand (uiIndexX1, uiIndexY  , uiIndexZ  ), GetRand (uiIndexX2, uiIndexY  , uiIndexZ  ),
																						 GetRand (uiIndexX_1, uiIndexY1 , uiIndexZ  ), GetRand (uiIndexX  , uiIndexY1 , uiIndexZ  ), GetRand (uiIndexX1, uiIndexY1 , uiIndexZ  ), GetRand (uiIndexX2, uiIndexY1 , uiIndexZ  ),
																						 GetRand (uiIndexX_1, uiIndexY2 , uiIndexZ  ), GetRand (uiIndexX  , uiIndexY2 , uiIndexZ  ), GetRand (uiIndexX1, uiIndexY2 , uiIndexZ  ), GetRand (uiIndexX2, uiIndexY2 , uiIndexZ  ),
																						 GetRand (uiIndexX_1, uiIndexY_1, uiIndexZ1 ), GetRand (uiIndexX  , uiIndexY_1, uiIndexZ1 ), GetRand (uiIndexX1, uiIndexY_1, uiIndexZ1 ), GetRand (uiIndexX2, uiIndexY_1, uiIndexZ1 ),
																						 GetRand (uiIndexX_1, uiIndexY  , uiIndexZ1 ), GetRand (uiIndexX  , uiIndexY  , uiIndexZ1 ), GetRand (uiIndexX1, uiIndexY  , uiIndexZ1 ), GetRand (uiIndexX2, uiIndexY  , uiIndexZ1 ),
																						 GetRand (uiIndexX_1, uiIndexY1 , uiIndexZ1 ), GetRand (uiIndexX  , uiIndexY1 , uiIndexZ1 ), GetRand (uiIndexX1, uiIndexY1 , uiIndexZ1 ), GetRand (uiIndexX2, uiIndexY1 , uiIndexZ1 ),
																						 GetRand (uiIndexX_1, uiIndexY2 , uiIndexZ1 ), GetRand (uiIndexX  , uiIndexY2 , uiIndexZ1 ), GetRand (uiIndexX1, uiIndexY2 , uiIndexZ1 ), GetRand (uiIndexX2, uiIndexY2 , uiIndexZ1 ),
																						 GetRand (uiIndexX_1, uiIndexY_1, uiIndexZ2 ), GetRand (uiIndexX  , uiIndexY_1, uiIndexZ2 ), GetRand (uiIndexX1, uiIndexY_1, uiIndexZ2 ), GetRand (uiIndexX2, uiIndexY_1, uiIndexZ2 ),
																						 GetRand (uiIndexX_1, uiIndexY  , uiIndexZ2 ), GetRand (uiIndexX  , uiIndexY  , uiIndexZ2 ), GetRand (uiIndexX1, uiIndexY  , uiIndexZ2 ), GetRand (uiIndexX2, uiIndexY  , uiIndexZ2 ),
																						 GetRand (uiIndexX_1, uiIndexY1 , uiIndexZ2 ), GetRand (uiIndexX  , uiIndexY1 , uiIndexZ2 ), GetRand (uiIndexX1, uiIndexY1 , uiIndexZ2 ), GetRand (uiIndexX2, uiIndexY1 , uiIndexZ2 ),
																						 GetRand (uiIndexX_1, uiIndexY2 , uiIndexZ2 ), GetRand (uiIndexX  , uiIndexY2 , uiIndexZ2 ), GetRand (uiIndexX1, uiIndexY2 , uiIndexZ2 ), GetRand (uiIndexX2, uiIndexY2 , uiIndexZ2 ),
																						 fmod (dIndexX, 1.0), fmod (dIndexY, 1.0), fmod (dIndexZ, 1.0));
    if (dInterpolation < 0.0) dInterpolation = 0.0;
    else if (dInterpolation > 1.0) dInterpolation = 1.0;
  }
	
	return dInterpolation;
}

} // namespace noise
} // namespace drimi
