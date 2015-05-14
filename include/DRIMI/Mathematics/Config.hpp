////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Mathematics.
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
////////////////////////////////////////////////////////////

#ifndef DRIMI_MATHEMATICS
#define DRIMI_MATHEMATICS

#include <SFML/OpenGL.hpp>

#include <cmath>
#include <assert.h>

#if (defined(DRIMI_MATHEMATICS_MESSAGES) && !defined(DRIMI_MATHEMATICS_MESSAGE_CORE_INCLUDED_DISPLAYED))
#	define DRIMI_MATHEMATICS_MESSAGE_CORE_INCLUDED_DISPLAYED
#	pragma message("DRIMI_MATHEMATICS: Core library included")
#endif // DRIMI_MATHEMATICS_MESSAGE

#define DRIMI_fPI 3.141592f

#include "./Core/Vectors/Vec2f.hpp"
#include "./Core/Vectors/Vec3f.hpp"
#include "./Core/Vectors/Vec4f.hpp"
#include "./Core/Vectors/Vec6f.hpp"
#include "./Core/Matrix/Mat4x4f.hpp"

#include "./Methods/TypePtr.hpp"

#include "./Methods/Vectorize.hpp"
#include "./Methods/Exponential.hpp"
#include "./Methods/Trigonometric.hpp"
#include "./Methods/Geometric.hpp"
#include "./Methods/ToString.hpp"
#include "./Methods/Matrix_transform.hpp"

#ifdef DEBUG
  #define DRIMI_MATHEMATICS_DEBUG
#endif

#endif // DRIMI_MATHEMATICS
