/////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2011-2015 Acroute Anthony (ant110283@hotmail.fr)
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
// A little part of the code is inspired by the book "SFML Game Development".
//
////////////////////////////////////////////////////////////

#include <Game/includes.hpp>
#include <Game/Game.hpp>

int main ( void ) {
  // Initialize FreeImage
#ifdef FREEIMAGE_LIB
  FreeImage_Initialise ();
#endif

  Game oGame;

  // Initialisation of the game
  if (oGame.GameInit ()) {
    while (oGame.WindowIsOpen ()) {
      oGame.ElapsedTime ();

      // Game running
      oGame.GameCycle ();

      // Render the game
      oGame.GamePaint ();
    }
    // End of the game
    oGame.GameEnd ();

    // Freeing of the ressources...
    // DeInitialize FreeImage
  #ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise ();
  #endif

    std::cout << "Press 'Enter' to quit..." << std::endl;
    std::cin.get();
    return EXIT_SUCCESS;
  }
  // DeInitialize FreeImage
#ifdef FREEIMAGE_LIB
  FreeImage_DeInitialise ();
#endif

  std::cout << "Error : The main window cannot be open !" << std::endl;
  std::cout << "Press 'Enter' to quit..." << std::endl;
  std::cin.get ();
  return EXIT_FAILURE;
}
