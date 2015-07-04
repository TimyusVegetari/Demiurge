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
#include <DRIMI/Noise/Perlin/Perlin1D.hpp>

namespace drimi {
namespace noise {

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Perlin1D::Perlin1D ( void ) :
  m_uiWidth       (0),
  m_uiSeed        (0),
  m_dWaveLength   (0.0),
  m_uiOctaves     (0),
  m_dRand         (),
  m_dDatas        ()
{
}

////////////////////////////////////////////////////////////
Perlin1D::~Perlin1D ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Perlin1D::Initialize ( GLuint uiWidthPow, GLuint uiSeed, GLuint uiWaveLength, GLuint uiOctaves, GLboolean bRepeatable ) {
  m_uiWidth       = static_cast<GLuint> (pow (2, uiWidthPow));
  m_uiSeed        = uiSeed;
  m_dWaveLength   = static_cast<GLdouble> (uiWaveLength);
  m_uiOctaves     = uiOctaves;

  srand (m_uiSeed);
  m_dRand.resize (static_cast<GLuint> (ceil (m_uiWidth * pow (2.0, static_cast<GLdouble> (uiOctaves-1)) / m_dWaveLength))+3);
  for (GLuint uiI = 0 ; uiI < m_dRand.size () ; uiI++)
    m_dRand[uiI] = static_cast<GLdouble> (rand ()) / RAND_MAX;
  if (bRepeatable) {
    GLdouble dWidth = static_cast<GLdouble> (m_uiWidth);
    GLdouble dFrequency = 1.0;
    for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
      GLuint  uiIndexX = static_cast<GLuint> (dWidth*dFrequency / m_dWaveLength);
      m_dRand[uiIndexX  ] = m_dRand[0];
      m_dRand[uiIndexX+1] = m_dRand[1];
      m_dRand[uiIndexX+2] = m_dRand[2];

      dFrequency *= 2.0;
    }
  }
}

////////////////////////////////////////////////////////////
void Perlin1D::CreateMatrix ( void ) {
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
GLuint Perlin1D::GetMatrixLength ( GLuint uiOctave ) {
  return m_dDatas[uiOctave].size ();
}

////////////////////////////////////////////////////////////
GLdouble* Perlin1D::GetMatrix ( GLuint uiOctave ) {
  GLdouble* dDatas = NULL;

  if (uiOctave < m_uiOctaves && m_dDatas.size () != 0 && m_dDatas[uiOctave].size () != 0) {
    dDatas = new GLdouble[m_dDatas[uiOctave].size ()];
    for (GLuint uiIndex = 0 ; uiIndex < m_dDatas[uiOctave].size () ; uiIndex++)
      dDatas[uiIndex] = m_dDatas[uiOctave][uiIndex];
  }

  return dDatas;
}

////////////////////////////////////////////////////////////
GLdouble Perlin1D::GeneratePerlin ( GLdouble dX, GLdouble dPersistance, Perlin1D::Mode eMode ) {
  GLdouble  dSum = 0.0,
            dAmplitude = 1.0,
            dFrequency = 1.0;

  for (GLuint uiOctave = 0 ; uiOctave < m_uiOctaves ; uiOctave++) {
    dSum += dAmplitude * GenerateNoise (dX*dFrequency, eMode);
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
GLdouble Perlin1D::GenerateNoise ( GLdouble dX, Perlin1D::Mode eMode ) {
  GLdouble dIndex = dX / m_dWaveLength;
  GLuint uiIndex = static_cast<GLuint> (dIndex)+1;
	GLdouble dInterpolation = 0.0;

  if (eMode == Perlin1D::Mode::LINEAR ) {
    dInterpolation = interpolation::Linear1D (m_dRand[uiIndex], m_dRand[uiIndex+1], fmod (dIndex, 1.0));
  } else if (eMode == Perlin1D::Mode::COSINE ) {
    dInterpolation = interpolation::Cosine1D (m_dRand[uiIndex], m_dRand[uiIndex+1], fmod (dIndex, 1.0));
  } else if (eMode == Perlin1D::Mode::CUBIC ) {
    dInterpolation = interpolation::Cubic1D (m_dRand[uiIndex-1], m_dRand[uiIndex], m_dRand[uiIndex+1], m_dRand[uiIndex+2], fmod (dIndex, 1.0));
    if (dInterpolation < 0.0) dInterpolation = 0.0;
    else if (dInterpolation > 1.0) dInterpolation = 1.0;
  }

  return dInterpolation;
}

} // namespace noise
} // namespace drimi
