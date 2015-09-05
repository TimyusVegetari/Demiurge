////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2015 Acroute Anthony (ant110283@hotmail.fr)
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
#include <Game/GameObjects/WorldState/GOSimpleInformations.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOSimpleInformations::GOSimpleInformations ( ST_Context& stContext ) :
  GameObject                (stContext),
  GameObject2D              (),
  m_uiSimpleInformations_ID (0)
{
}

////////////////////////////////////////////////////////////
GOSimpleInformations::~GOSimpleInformations ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOSimpleInformations::Initialize ( void ) {
  std::cout << " >> GOSimpleInformations initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  gmMainWindow.EnableSFML ();

	// Simple informations for debug
  m_uiSimpleInformations_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oSimpleInformations = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiSimpleInformations_ID);
  oSimpleInformations.SetFont         (m_stContext.m_oBmpFont);
  oSimpleInformations.SetColor        (sf::Color::Green);
	oSimpleInformations.SetOrigin       (0.f, 0.f);
	oSimpleInformations.setPosition     (0.f, 0.f);

  gmMainWindow.DisableSFML ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean GOSimpleInformations::Update ( GLuint uiCameraID ) {
  // Camera 3D
  CameraManager& oCameraManager = m_stContext.m_oGraphicsEngine.GetRenderer3D ().GetCameraManager ();
  Camera& oCamera = oCameraManager.GetCamera (uiCameraID);
  // Update simple informations for debug
  RenderList2D& oRenderList2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ().GetRenderList (m_uiRenderList2D_ID);
  drimi::BmpText& oSimpleInformations = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiSimpleInformations_ID);
  oSimpleInformations.SetString       (std::string ("Fps : ")+m_stContext.m_oGraphicsEngine.GetFrameRate ()
                                      +std::string ("\nPlayer position : ")+oCamera.ToStringPosition ()
                                      +std::string ("\n       orientation : ")+oCamera.ToStringOrientation ()
                                      +std::string ("\n       focalisation : ")+oCamera.ToStringGlobalFocalisation ()
                                      +std::string (" (")+oCamera.ToStringLocalFocalisation ()+std::string (")"));

	return GL_FALSE;
}
