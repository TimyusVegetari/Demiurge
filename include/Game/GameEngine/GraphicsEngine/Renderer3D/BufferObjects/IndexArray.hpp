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
 * \file IndexArray.hpp
 * \brief Class to define index array for VBOs.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015-2016
 *
 */

#ifndef INDEXARRAY_HPP__
#define INDEXARRAY_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CGDatas.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to store and manipulate the index of the VBOs.
///
////////////////////////////////////////////////////////////
class IndexArray : public CGDatas<GLuint> {

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a index array.
    ///
    /// \param uiDatasArray     Datas Array.
    ///        iDatasArraySize  Size of the datas array.
    ///
    ////////////////////////////////////////////////////////////
    IndexArray ( GLuint* uiDatasArray, GLsizei iDatasArraySize );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the index array.
    ///
    ////////////////////////////////////////////////////////////
    ~IndexArray ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the VBO index at the data position.
    ///
    /// \param iDataPos   Data position.
    ///
    /// \return Value of the VBO index.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetIndex ( GLsizei iDataPos );
};

#endif // INDEXARRAY_HPP__
