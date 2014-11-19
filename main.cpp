/*
  This file is part of Demiurge.
  Copyright (C) 2014 Anthony Acroute aka Timyus Vegetari

  Demiurge is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Demiurge is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with Demiurge; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <iostream>
#include <cstdlib>

int main ( void ) {
  std::cout << "Demiurge by Timyus Vegetari" << std::endl;
  std::cout << "Game under GNU General Public License version 2" << std::endl;
  std::cout << "Program in C++, using OpenGL and SFML" << std::endl << std::endl;

  std::cout << "Press 'Enter' to quit..." << std::endl;
  std::cin.get ();
  return EXIT_SUCCESS;
}
