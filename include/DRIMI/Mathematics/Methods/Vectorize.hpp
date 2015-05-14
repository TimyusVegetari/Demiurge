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
 * \file Vectorize.hpp
 * \brief Macros to adapt mathematics functions for the vectors.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2014
 *
 */

#define DRIMI_VECTORIZE2_VEC(func) \
	Vec2f func ( Vec2f const & v2fV ) { \
		return Vec2f ( \
			func (v2fV.x), \
			func (v2fV.y) \
    ); \
	}

#define DRIMI_VECTORIZE3_VEC(func) \
	Vec3f func ( Vec3f const & v3fV ) { \
		return Vec3f ( \
			func(v3fV.x), \
			func(v3fV.y), \
			func(v3fV.z) \
    ); \
	}

#define DRIMI_VECTORIZE4_VEC(func) \
	Vec4f func ( Vec4f const & v4fV ) { \
		return Vec4f ( \
			func(v4fV.x), \
			func(v4fV.y), \
			func(v4fV.z), \
			func(v4fV.w) \
    ); \
	}

#define DRIMI_VECTORIZE_VEC(func) \
	DRIMI_VECTORIZE2_VEC(func) \
	DRIMI_VECTORIZE3_VEC(func) \
	DRIMI_VECTORIZE4_VEC(func)

#define DRIMI_VECTORIZE2_VEC_VEC(func) \
	Vec2f func ( Vec2f const & v2fV1, Vec2f const & v2fV2 ) { \
		return Vec2f ( \
			func (v2fV1.x, v2fV2.x), \
			func (v2fV1.y, v2fV2.y) \
    ); \
	}

#define DRIMI_VECTORIZE3_VEC_VEC(func) \
	Vec3f func ( Vec3f const & v3fV1, Vec3f const & v3fV2 ) { \
		return Vec3f ( \
			func(v3fV1.x, v3fV2.x), \
			func(v3fV1.y, v3fV2.y), \
			func(v3fV1.z, v3fV2.z) \
    ); \
	}

#define DRIMI_VECTORIZE4_VEC_VEC(func) \
	Vec4f func ( Vec4f const & v4fV1, Vec4f const & v4fV2 ) { \
		return Vec4f ( \
			func(v4fV1.x, v4fV2.x), \
			func(v4fV1.y, v4fV2.y), \
			func(v4fV1.z, v4fV2.z), \
			func(v4fV1.w, v4fV2.w) \
    ); \
	}

#define DRIMI_VECTORIZE_VEC_VEC(func) \
	DRIMI_VECTORIZE2_VEC_VEC(func) \
	DRIMI_VECTORIZE3_VEC_VEC(func) \
	DRIMI_VECTORIZE4_VEC_VEC(func)
