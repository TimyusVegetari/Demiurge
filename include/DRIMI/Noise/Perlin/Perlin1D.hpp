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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Perlin1D.hpp
 * \brief Class to define the perlin noise generator.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef DRIMI_PERLIN1D_HPP__
#define DRIMI_PERLIN1D_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <DRIMI/Interpolation.hpp>

namespace drimi {
namespace noise {

////////////////////////////////////////////////////////////
/// \brief Class to generate and store a perlin noise 1D.
///
////////////////////////////////////////////////////////////
class Perlin1D {

  public:
    ////////////////////////////////////////////////////////////
    // Enumerations
    ////////////////////////////////////////////////////////////
    enum Mode {
      LINEAR,
      COSINE,
      CUBIC
    };

  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint                  m_uiWidth;
    GLuint                  m_uiSeed;
    GLdouble                m_dWaveLength;
    GLuint                  m_uiOctaves;
    std::vector<GLdouble>   m_dRand;
    std::vector<std::vector<GLdouble>> m_dDatas;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a perlin noise 1D.
    ///
    ////////////////////////////////////////////////////////////
    Perlin1D ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the perlin noise 1D.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Perlin1D ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the perlin noise 1D.
    ///
    /// \param uiWidthPow   Pow of two for the width of the noise
    ///        uiWaveLength Distance between two points
    ///        uiSeed       Seed to generate matrices
    ///        uiOctaves    Octaves number of the perlin noise
    ///        bRepeatable    To make a repeatable texture or not
    ///
    ////////////////////////////////////////////////////////////
    void Initialize ( GLuint uiWidthPow, GLuint uiSeed, GLuint uiWaveLength, GLuint uiNbOctaves, GLboolean bRepeatable = GL_FALSE );

    ////////////////////////////////////////////////////////////
    /// \brief Create 1D matrices and generate values from the seed.
    ///
    ////////////////////////////////////////////////////////////
    void CreateMatrix ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the matrix length of the noise.
    ///
    /// \param uiOctave   Octave of the matrix to get
    ///
    /// \return Number of values in the matrix.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetMatrixLength ( GLuint uiOctave );

    ////////////////////////////////////////////////////////////
    /// \brief Get the matrix of the noise.
    ///
    /// Be careful ! The fonction create a pointer of array and return it.
    /// The deletion of the pointer of array is not performed by PerlinNoise1D.
    ///
    /// \param uiOctave   Octave of the matrix to get
    ///
    /// \return Pointer of array of the matrix values.
    ///
    ////////////////////////////////////////////////////////////
    GLdouble* GetMatrix ( GLuint uiOctave );

    ////////////////////////////////////////////////////////////
    /// \brief Get the matrix of the noise.
    ///
    /// Be careful ! The fonction create a pointer of array and return it.
    /// The deletion of the pointer of array is not performed by PerlinNoise1D.
    ///
    /// \param dX           X position of the interpolation
    ///        dPersistance Persistance of the perlin noise
    ///        eMode        Mode of interpolation
    ///
    /// \return Result of the interpolation.
    ///
    ////////////////////////////////////////////////////////////
    GLdouble GeneratePerlin ( GLdouble dX, GLdouble dPersistance, Perlin1D::Mode eMode );

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get a noise.
    ///
    /// \param dX     X value to interpolate
    ///        eMode  Mode of interpolation
    ///
    /// \return Result of the interpolation.
    ///
    ////////////////////////////////////////////////////////////
    GLdouble GenerateNoise ( GLdouble dX, Perlin1D::Mode eMode );

};

} // namespace noise
} // namespace drimi

#endif // DRIMI_PERLIN1D_HPP__
