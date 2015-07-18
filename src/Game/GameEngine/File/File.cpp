////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/File/File.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
File::File ( void ) :
  m_fsFileStream  (),
  m_szBuffer      ("")
{
}

////////////////////////////////////////////////////////////
File::~File ( void ) {
  if (m_fsFileStream.is_open ())
    m_fsFileStream.close ();
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean File::Open ( const std::string szFileName ) {
  // Opening of a file in read mode
  m_fsFileStream.open (szFileName, std::ios::in);
  if (m_fsFileStream.is_open ())
    return GL_TRUE;
  std::cout << "Error : The file '" << szFileName << "' not found !" << std::endl;
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void File::Read ( void ) {
  if (m_fsFileStream.is_open ()) {
    // Filling of the buffer line by line.
    std::string szLineBuffer;
    while (std::getline (m_fsFileStream, szLineBuffer))
      m_szBuffer += szLineBuffer + '\n';
  }
}

////////////////////////////////////////////////////////////
void File::Close ( void ) {
  m_fsFileStream.close ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
std::string& File::GetBuffer ( void ) {
  return m_szBuffer;
}

////////////////////////////////////////////////////////////
GLuint File::GetBufferSize ( void ) {
  return m_szBuffer.size ();
}
