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
#include <DRIMI/Noise/Perlin/Perlin2D.hpp>

#include <iostream>

namespace drimi {
namespace noise {

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Perlin2D::Perlin2D ( void ) :
  m_uiWidth       (0),
  m_uiHeight      (0),
  m_uiSurface     (0),
  m_uiWidthMax    (0),
  m_uiHeightMax   (0),
  m_uiSeed        (0),
  m_dWaveLengthX  (0.0),
  m_dWaveLengthY  (0.0),
  m_uiOctaves     (0),
  m_dRand         (),
  m_dDatas        ()
{
}

////////////////////////////////////////////////////////////
Perlin2D::~Perlin2D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Perlin2D::Initialize ( GLuint uiWidthPow, GLuint uiHeightPow, GLuint uiSeed, GLuint uiWaveLengthX, GLuint uiWaveLengthY, GLuint uiOctaves, GLboolean bRepeatable ) {
  m_uiWidth       = static_cast<GLuint> (pow (2.0, static_cast<GLdouble> (uiWidthPow)));
  m_uiHeight      = static_cast<GLuint> (pow (2.0, static_cast<GLdouble> (uiHeightPow)));
  m_uiSurface     = m_uiWidth * m_uiHeight;
  m_uiWidthMax    = static_cast<GLuint> (ceil (m_uiWidth * pow (2.0, static_cast<GLdouble> (uiOctaves-1)) / uiWaveLengthX)) + 3;
  m_uiHeightMax   = static_cast<GLuint> (ceil (m_uiHeight * pow (2.0, static_cast<GLdouble> (uiOctaves-1)) / uiWaveLengthY)) + 3;
  m_uiSeed        = uiSeed;
  m_dWaveLengthX  = static_cast<GLdouble> (uiWaveLengthX);
  m_dWaveLengthY  = static_cast<GLdouble> (uiWaveLengthY);
  m_uiOctaves     = uiOctaves;

  srand (m_uiSeed);
  m_dRand.resize (m_uiWidthMax * m_uiHeightMax);
  for (GLuint uiI = 0 ; uiI < m_dRand.size () ; uiI++)
    m_dRand[uiI] = static_cast<GLdouble> (rand ()) / RAND_MAX;
  if (bRepeatable) {
    GLdouble dWidth = static_cast<GLdouble> (m_uiWidth), dHeight = static_cast<GLdouble> (m_uiHeight);
    GLdouble dFrequency = 1.0;
    for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
      GLdouble  dIncrementX = dFrequency / m_dWaveLengthX,
                dIncrementY = dFrequency / m_dWaveLengthY,
                dIndexX = dWidth*dIncrementX,
                dIndexY = dHeight*dIncrementY;
      GLuint  uiIndexX = static_cast<GLuint> (dIndexX),
              uiIndexY = static_cast<GLuint> (dIndexY),
              uiIndexX1 = uiIndexX+1, uiIndexX2 = uiIndexX+2,
              uiIndexY1 = uiIndexY+1, uiIndexY2 = uiIndexY+2;
      for (GLdouble dY = 0.0 ; dY < dIndexY+3 ; dY+=dIncrementY) {
        GLuint  uiY = static_cast<GLuint> (dY);
        SetRand (uiIndexX , uiY, GetRand (0, uiY));
        SetRand (uiIndexX1, uiY, GetRand (1, uiY));
        SetRand (uiIndexX2, uiY, GetRand (2, uiY));
      }
      for (GLdouble dX = 0.0 ; dX < dIndexX+3 ; dX+=dIncrementX) {
        GLuint  uiX = static_cast<GLuint> (dX);
        SetRand (uiX, uiIndexY , GetRand (uiX, 0));
        SetRand (uiX, uiIndexY1, GetRand (uiX, 1));
        SetRand (uiX, uiIndexY2, GetRand (uiX, 2));
      }

      dFrequency *= 2.0;
    }
  }
}

////////////////////////////////////////////////////////////
void Perlin2D::CreateMatrix ( void ) {
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
GLuint Perlin2D::GetMatrixWidth ( GLuint uiOctave ) {
  if (uiOctave == 0)
    return m_uiWidthMax;
  else
    return m_uiWidthMax / (2*uiOctave);
}

////////////////////////////////////////////////////////////
GLuint Perlin2D::GetMatrixHeight ( GLuint uiOctave ) {
  if (uiOctave == 0)
    return m_uiHeightMax;
  else
    return m_uiHeightMax / (2*uiOctave);
}

////////////////////////////////////////////////////////////
GLuint Perlin2D::GetMatrixLength ( GLuint uiOctave ) {
  return m_dDatas[uiOctave].size ();
}

////////////////////////////////////////////////////////////
GLdouble* Perlin2D::GetMatrix ( GLuint uiOctave ) {
  GLdouble* dDatas = NULL;

  if (uiOctave < m_uiOctaves && m_dDatas.size () != 0 && m_dDatas[uiOctave].size () != 0) {
    dDatas = new GLdouble[m_dDatas[uiOctave].size ()];
    for (GLuint uiIndex = 0 ; uiIndex < m_dDatas[uiOctave].size () ; uiIndex++)
      dDatas[uiIndex] = m_dDatas[uiOctave][uiIndex];
  }

  return dDatas;
}

////////////////////////////////////////////////////////////
GLdouble* Perlin2D::GetInterpolation ( GLuint uiOctave, GLdouble dPersistance, Perlin2D::Mode eMode ) {
  GLdouble* dDatas = new GLdouble[m_uiSurface];
  GLdouble  dSum = 0.0,
            dAmplitude,
            dFrequency;

  if (uiOctave == 0) {
    dAmplitude = 1.0;
    dFrequency = 1.0;
  } else {
    dAmplitude = pow (dPersistance, static_cast<GLdouble> (uiOctave));
    dFrequency = pow (2.0, static_cast<GLdouble> (uiOctave));
  }
  for (GLuint uiY = 0 ; uiY < m_uiHeight ; uiY++)
    for (GLuint uiX = 0 ; uiX < m_uiWidth ; uiX++) {
      dSum = dAmplitude * GenerateNoise (static_cast<GLdouble> (uiX)*dFrequency, static_cast<GLdouble> (uiY)*dFrequency, eMode);
      if (dAmplitude == 1.0)
        dDatas[uiY * m_uiWidth + uiX] = dSum;
      else
        dDatas[uiY * m_uiWidth + uiX] = dSum * (1.0 - dPersistance) / (1.0 - dAmplitude);
    }

  return dDatas;
}

////////////////////////////////////////////////////////////
GLdouble Perlin2D::GeneratePerlin ( GLdouble dX, GLdouble dY, GLdouble dPersistance, Perlin2D::Mode eMode ) {
  GLdouble  dSum = 0.0,
            dAmplitude = 1.0,
            dFrequency = 1.0;

  for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
    dSum += dAmplitude * GenerateNoise (dX*dFrequency, dY*dFrequency, eMode);
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
void Perlin2D::SetRand ( GLuint uiX, GLuint uiY, GLdouble dValue ) {
  m_dRand[uiY * m_uiWidthMax + uiX] = dValue;
}

////////////////////////////////////////////////////////////
GLdouble Perlin2D::GetRand ( GLuint uiX, GLuint uiY ) {
  return m_dRand[uiY * m_uiWidthMax + uiX];
}

////////////////////////////////////////////////////////////
GLdouble Perlin2D::GenerateNoise ( GLdouble dX, GLdouble dY, Perlin2D::Mode eMode ) {
  GLdouble  dIndexX = dX / m_dWaveLengthX,
            dIndexY = dY / m_dWaveLengthY;
  GLuint uiIndexX = static_cast<GLuint> (dIndexX)+1,
         uiIndexY = static_cast<GLuint> (dIndexY)+1,
         uiIndexX_1 = uiIndexX-1, uiIndexX1 = uiIndexX+1, uiIndexX2 = uiIndexX+2,
         uiIndexY_1 = uiIndexY-1, uiIndexY1 = uiIndexY+1, uiIndexY2 = uiIndexY+2;
	GLdouble dInterpolation = 0.0;

  if (eMode == Perlin2D::Mode::LINEAR ) {
    dInterpolation = interpolation::Linear2D (GetRand (uiIndexX, uiIndexY ), GetRand (uiIndexX1, uiIndexY ),
																							GetRand (uiIndexX, uiIndexY1), GetRand (uiIndexX1, uiIndexY1),
																							fmod (dIndexX, 1.0), fmod (dIndexY, 1.0));
  } else if (eMode == Perlin2D::Mode::COSINE ) {
    dInterpolation = interpolation::Cosine2D (GetRand (uiIndexX, uiIndexY ), GetRand (uiIndexX1, uiIndexY ),
																							GetRand (uiIndexX, uiIndexY1), GetRand (uiIndexX1, uiIndexY1),
																							fmod (dIndexX, 1.0), fmod (dIndexY, 1.0));
  } else if (eMode == Perlin2D::Mode::CUBIC ) {
    dInterpolation = interpolation::Cubic2D (GetRand (uiIndexX_1, uiIndexY_1), GetRand (uiIndexX, uiIndexY_1), GetRand (uiIndexX1, uiIndexY_1), GetRand (uiIndexX2, uiIndexY_1),
																						 GetRand (uiIndexX_1, uiIndexY  ), GetRand (uiIndexX, uiIndexY  ), GetRand (uiIndexX1, uiIndexY  ), GetRand (uiIndexX2, uiIndexY  ),
																						 GetRand (uiIndexX_1, uiIndexY1 ), GetRand (uiIndexX, uiIndexY1 ), GetRand (uiIndexX1, uiIndexY1 ), GetRand (uiIndexX2, uiIndexY1 ),
																						 GetRand (uiIndexX_1, uiIndexY2 ), GetRand (uiIndexX, uiIndexY2 ), GetRand (uiIndexX1, uiIndexY2 ), GetRand (uiIndexX2, uiIndexY2 ),
																						 fmod (dIndexX, 1.0), fmod (dIndexY, 1.0));
    if (dInterpolation < 0.0) dInterpolation = 0.0;
    else if (dInterpolation > 1.0) dInterpolation = 1.0;
  }
	
  return dInterpolation;
}

} // namespace noise
} // namespace drimi
