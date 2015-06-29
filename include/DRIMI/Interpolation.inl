////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2013-2015 Acroute Anthony (ant110283@hotmail.fr)
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
// Headers
////////////////////////////////////////////////////////////
#include <DRIMI/Interpolation.hpp>

namespace drimi {
namespace interpolation {

////////////////////////////////////////////////////////////
GLdouble Linear1D ( GLdouble dA, GLdouble dB, GLdouble dX ) {
  return dA*(1.0-dX)+dB*dX;
}

////////////////////////////////////////////////////////////
GLdouble Linear2D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dX, GLdouble dY ) {
  GLdouble  dI1 = Linear1D (dA, dB, dX),
            dI2 = Linear1D (dC, dD, dX);

  return Linear1D (dI1, dI2, dY);
}

////////////////////////////////////////////////////////////
GLdouble Linear3D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dE, GLdouble dF, GLdouble dG, GLdouble dH, GLdouble dX, GLdouble dY, GLdouble dZ ) {
  GLdouble  dI1 = Linear2D (dA, dB, dC, dD, dX, dY),
            dI2 = Linear2D (dE, dF, dG, dH, dX, dY);

  return Linear1D (dI1, dI2, dZ);
}

////////////////////////////////////////////////////////////
GLdouble Cosine1D ( GLdouble dA, GLdouble dB, GLdouble dX ) {
  GLdouble dK = (1.0-cos(dX*PI))/2.0;
  return Linear1D (dA, dB, dK);
}

////////////////////////////////////////////////////////////
GLdouble Cosine2D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dX, GLdouble dY ) {
  GLdouble  dI1 = Cosine1D (dA, dB, dX),
            dI2 = Cosine1D (dC, dD, dX);

  return Cosine1D (dI1, dI2, dY);
}

////////////////////////////////////////////////////////////
GLdouble Cosine3D ( GLdouble dA, GLdouble dB, GLdouble dC, GLdouble dD, GLdouble dE, GLdouble dF, GLdouble dG, GLdouble dH, GLdouble dX, GLdouble dY, GLdouble dZ ) {
  GLdouble  dI1 = Cosine2D (dA, dB, dC, dD, dX, dY),
            dI2 = Cosine2D (dE, dF, dG, dH, dX, dY);

  return Cosine1D (dI1, dI2, dZ);
}

////////////////////////////////////////////////////////////
GLdouble Cubic1D ( GLdouble dY0, GLdouble dY1, GLdouble dY2, GLdouble dY3, GLdouble dX ) {
  GLdouble  dA = dY3-dY2-dY0+dY1,
            dB = dY0-dY1-dA,
            dC = dY2-dY0,
            dD = dY1;

  return dA*dX*dX*dX + dB*dX*dX + dC*dX + dD;
}

////////////////////////////////////////////////////////////
GLdouble Cubic2D ( GLdouble dA00, GLdouble dA01, GLdouble dA02, GLdouble dA03,
                   GLdouble dB10, GLdouble dB11, GLdouble dB12, GLdouble dB13,
                   GLdouble dC20, GLdouble dC21, GLdouble dC22, GLdouble dC23,
                   GLdouble dD30, GLdouble dD31, GLdouble dD32, GLdouble dD33,
                   GLdouble dX, GLdouble dY ) {
  GLdouble  dA = Cubic1D (dA00, dA01, dA02, dA03, dX),
            dB = Cubic1D (dB10, dB11, dB12, dB13, dX),
            dC = Cubic1D (dC20, dC21, dC22, dC23, dX),
            dD = Cubic1D (dD30, dD31, dD32, dD33, dX);

  return Cubic1D (dA, dB, dC, dD, dY);
}

////////////////////////////////////////////////////////////
GLdouble Cubic3D ( GLdouble dA000, GLdouble dA001, GLdouble dA002, GLdouble dA003,
                   GLdouble dA010, GLdouble dA011, GLdouble dA012, GLdouble dA013,
                   GLdouble dA020, GLdouble dA021, GLdouble dA022, GLdouble dA023,
                   GLdouble dA030, GLdouble dA031, GLdouble dA032, GLdouble dA033,
                   GLdouble dB100, GLdouble dB101, GLdouble dB102, GLdouble dB103,
                   GLdouble dB110, GLdouble dB111, GLdouble dB112, GLdouble dB113,
                   GLdouble dB120, GLdouble dB121, GLdouble dB122, GLdouble dB123,
                   GLdouble dB130, GLdouble dB131, GLdouble dB132, GLdouble dB133,
                   GLdouble dC200, GLdouble dC201, GLdouble dC202, GLdouble dC203,
                   GLdouble dC210, GLdouble dC211, GLdouble dC212, GLdouble dC213,
                   GLdouble dC220, GLdouble dC221, GLdouble dC222, GLdouble dC223,
                   GLdouble dC230, GLdouble dC231, GLdouble dC232, GLdouble dC233,
                   GLdouble dD300, GLdouble dD301, GLdouble dD302, GLdouble dD303,
                   GLdouble dD310, GLdouble dD311, GLdouble dD312, GLdouble dD313,
                   GLdouble dD320, GLdouble dD321, GLdouble dD322, GLdouble dD323,
                   GLdouble dD330, GLdouble dD331, GLdouble dD332, GLdouble dD333,
                   GLdouble dX, GLdouble dY, GLdouble dZ ) {
  GLdouble  dA = Cubic2D (dA000, dA001, dA002, dA003,
                          dA010, dA011, dA012, dA013,
                          dA020, dA021, dA022, dA023,
                          dA030, dA031, dA032, dA033,
                          dX, dY),
            dB = Cubic2D (dB100, dB101, dB102, dB103,
                          dB110, dB111, dB112, dB113,
                          dB120, dB121, dB122, dB123,
                          dB130, dB131, dB132, dB133,
                          dX, dY),
            dC = Cubic2D (dC200, dC201, dC202, dC203,
                          dC210, dC211, dC212, dC213,
                          dC220, dC221, dC222, dC223,
                          dC230, dC231, dC232, dC233,
                          dX, dY),
            dD = Cubic2D (dD300, dD301, dD302, dD303,
                          dD310, dD311, dD312, dD313,
                          dD320, dD321, dD322, dD323,
                          dD330, dD331, dD332, dD333,
                          dX, dY);

  return Cubic1D (dA, dB, dC, dD, dZ);
}

}
}
