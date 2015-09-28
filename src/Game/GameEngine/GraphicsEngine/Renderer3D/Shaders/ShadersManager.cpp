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
#include <Game/GameEngine/GraphicsEngine/Renderer3D/Shaders/ShadersManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
ShadersManager::ShadersManager ( void ) {
}

////////////////////////////////////////////////////////////
ShadersManager::~ShadersManager ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean ShadersManager::Initialize ( void ) {
  std::cout << "Shaders Manager : Initializing..." << std::endl;
  GLboolean bSuccess = GL_TRUE;

  std::string szShadersFileName = "datas/shaders/shaders.xml";
  std::string szError = "Error : Loading of ";

  // Loading of the XML file to open shaders
  tinyxml2::XMLDocument xmlDocument;
  if (xmlDocument.LoadFile (szShadersFileName.c_str ()) != tinyxml2::XML_NO_ERROR) {
    std::cerr << szError << szShadersFileName << std::endl << "  Error #" << xmlDocument.ErrorID () << " : " << xmlDocument.GetErrorStr1 () << std::endl;
    bSuccess = GL_FALSE;
  }

  // Go on the first element of the document
  tinyxml2::XMLHandle xmlHandle (&xmlDocument);
  tinyxml2::XMLElement *xmlElement = xmlHandle.FirstChildElement ().FirstChildElement ().ToElement();
  if (xmlElement == NULL) {
    std::cout << szError << szShadersFileName << std::endl << "  The current node doesn't exist !" << std::endl;
    bSuccess = GL_FALSE;
  }

  // Initialization of the shader programs
  std::string szType = "";
  Shaders::ID eType;
  while (xmlElement != NULL) {
    szType = xmlElement->Attribute ("type");
    if (szType == "skybox")
      eType = Shaders::ID::Skybox;
    else if (szType == "wired")
      eType = Shaders::ID::Wired;
    bSuccess = m_oShaderPrograms[eType].Load (xmlElement->Attribute ("vertex"), xmlElement->Attribute ("fragment"));
    xmlElement = xmlElement->NextSiblingElement ();
  }

  if (bSuccess)
    std::cout << "Shaders Manager : Initialization succeed" << std::endl;
  else
    std::cout << "Shaders Manager : Initialization failed" << std::endl;
  return bSuccess;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
ShaderProgram& ShadersManager::GetShaderProgram ( Shaders::ID eType ) {
  return m_oShaderPrograms[eType];
}
