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
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file MeshesIdentifiers.hpp
 * \brief Identifiers of different type of meshes.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2012-2016
 *
 */

#ifndef MESHESIDENTIFIERS_HPP__
#define MESHESIDENTIFIERS_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Primitive3D.hpp"
#include "TerrainSkin.hpp"
#include "OrganicForm.hpp"
#include "NonOrganicForm.hpp"
#include "MeshesList.hpp"

////////////////////////////////////////////////////////////
/// \brief Enumeration of type for the meshes of the game.
///
////////////////////////////////////////////////////////////
namespace Meshes {

enum Type {
  Primitive3D,
  TerrainSkin,
  OrganicForm,
  NonOrganicForm,
  Count
};

struct Identifier {
  Meshes::Type  eType;
  GLuint      uiIndex;

  Identifier ( void ) {
    eType = Meshes::Type::Primitive3D;
    uiIndex = 0;
  }
};

}

#endif // MESHESIDENTIFIERS_HPP__
