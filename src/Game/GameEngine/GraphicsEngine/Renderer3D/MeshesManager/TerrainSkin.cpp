////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2016 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file TerrainSkin.hpp
 * \brief Class for the terrain skin meshes.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2016
 *
 */

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/Renderer3D/MeshesManager/TerrainSkin.hpp>

////////////////////////////////////////////////////////////
TerrainSkin::TerrainSkin ( void ) :
  Mesh ()
{
}

////////////////////////////////////////////////////////////
TerrainSkin::TerrainSkin ( std::string szTypeName,
                           GLfloat* fVertexDatasArray, GLsizei iVertexDatasArraySize,
                           GLuint* uiIndexDatasArray, GLsizei iIndexDatasArraySize,
                           GLfloat* fNormalDatasArray, GLsizei iNormalDatasArraySize ) :
  Mesh  (szTypeName,
         fVertexDatasArray, iVertexDatasArraySize,
         uiIndexDatasArray, iIndexDatasArraySize,
         fNormalDatasArray, iNormalDatasArraySize)
{
  std::cout << "Construction of the terrain skin : " << szTypeName << std::endl;
}

////////////////////////////////////////////////////////////
TerrainSkin::~TerrainSkin ( void ) {
}
