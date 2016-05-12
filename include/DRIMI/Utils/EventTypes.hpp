////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Utils.
// Copyright (C) 2016 Acroute Anthony (ant110283@hotmail.fr)
//
// DRIMI::Utils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// DRIMI::Utils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DRIMI::Utils.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file EventTypes.hpp
 * \brief Enumeration of event types of the game.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef EVENTTYPES_HPP__
#define EVENTTYPES_HPP__

////////////////////////////////////////////////////////////
/// \brief Enumeration of event types of the game.
///
////////////////////////////////////////////////////////////
namespace drimi {
namespace Event {

enum Type {
  None,
  Closed,
  Resized,
  KeyPressed,
  TextEntered,
  MouseMoved,
  MouseWheelUp,
  MouseWheelDown
};

} // namespace Event
} // namespace drimi

#endif // EVENTTYPES_HPP__
