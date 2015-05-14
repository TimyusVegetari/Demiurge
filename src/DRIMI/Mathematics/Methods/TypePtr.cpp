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
	GLfloat const * ValuePtr ( Vec2f const & v2fVec ) {
		return &(v2fVec.x);
	}

	GLfloat * ValuePtr ( Vec2f & v2fVec ) {
		return &(v2fVec.x);
	}

  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr ( Vec3f const & v3fVec ) {
		return &(v3fVec.x);
	}

	GLfloat * ValuePtr ( Vec3f & v3fVec ) {
		return &(v3fVec.x);
	}

  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr (	Vec4f const & v4fVec ) {
		return &(v4fVec.x);
	}

	GLfloat * ValuePtr (	Vec4f & v4fVec ) {
		return &(v4fVec.x);
	}

  ////////////////////////////////////////////////////////////
	GLfloat const * ValuePtr ( Mat4x4f const & m4fMat ) {
		return &(m4fMat[0].x);
	}

	GLfloat * ValuePtr ( Mat4x4f & m4fMat ) {
		return &(m4fMat[0].x);
	}

} // namespace drimi
