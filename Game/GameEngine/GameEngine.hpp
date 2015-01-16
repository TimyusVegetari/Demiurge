////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2013-2014 Acroute Anthony (ant110283@hotmail.fr)
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
 * \file GameEngine.hpp
 * \brief Class for the game engine of Demiurge.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2013-2014
 *
 */

#ifndef GAMEENGINE_HPP__
#define GAMEENGINE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#if defined (INCLUDE_SFML__) && defined (INCLUDE_DRIMI__)
#include <string>
#include "RenderTargetsManager/RenderTargetsManager.hpp"
#include "States/StateStack.hpp"

////////////////////////////////////////////////////////////
/// \brief Class for elementary game system
///
////////////////////////////////////////////////////////////
class GameEngine {

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////

    RenderTargetsManager  m_oRenderTargetsManager;
    sf::Vector2u          m_v2uWindowCenter;
    sf::Vector2u          m_v2uSize;
    std::string           m_szTitle;
    std::string           m_szAuthor;
    std::string           m_szVersion;
    std::string           m_szCopyright;
    std::string           m_szDate;
    sf::Image             m_sfIcon;

    // Universal clock of the game
		sf::Clock             m_sfClock;
    GLuint                m_uiElapsedTime;

    // Elemetary ressources of the game
    drimi::BmpFont        m_oBmpFont;         ///< Bitmap font of the game.
    StateStack            m_oStateStack;

		GLboolean             m_bSleep;
		sf::Image             m_sfScreenCapture;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a game engine.
    ///
    ////////////////////////////////////////////////////////////
    GameEngine ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game engine.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GameEngine ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the main window of the game.
    ///
    /// \return True if initializing succeeded, false if it failed
    ///
    ////////////////////////////////////////////////////////////
    GLboolean InitWinMain ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Transmit the elapsed time from the universal clock to internal variable.
    ///
    ////////////////////////////////////////////////////////////
    void ElapsedTime ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Compute the center of the screen in the main window, or fullscreen.
    ///
    ////////////////////////////////////////////////////////////
    void ComputeWindowCenter ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Close the main window of the game.
    ///
    ////////////////////////////////////////////////////////////
    void CloseWindow ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Copy the current contents of the window to an image.
    ///
    /// This is a slow operation, whose main purpose is to make screenshots of
    /// the application. This method update an internal image with the contents of the main
    /// window. (see the capture method in the SFML render window)
    ///
    /// \see GetScreenCapture
    ///
    ////////////////////////////////////////////////////////////
    void CaptureScreen ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the title of the game.
    ///
    /// \return The title of the game
    ///
    ////////////////////////////////////////////////////////////
    std::string GetTitle ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the author of the game.
    ///
    /// \return The author of the game
    ///
    ////////////////////////////////////////////////////////////
    std::string GetAuthor ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the version of the game.
    ///
    /// \return The version of the game
    ///
    ////////////////////////////////////////////////////////////
    std::string GetVersion ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the copyright of the game.
    ///
    /// \return The copyright of the game
    ///
    ////////////////////////////////////////////////////////////
    std::string GetCopyright ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the date of development of the game.
    ///
    /// \return The date of development of the game
    ///
    ////////////////////////////////////////////////////////////
    std::string GetDate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the icon of the game.
    ///
    /// \return The icon of the game
    ///
    ////////////////////////////////////////////////////////////
    sf::Image& GetIcon ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the width of the screen in the main window, or fullscreen.
    ///
    /// \return The width of the screen
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetWidth ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the height of the screen in the main window, or fullscreen.
    ///
    /// \return The height of the screen
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetHeight ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get a render window of the game.
    ///
    /// \param eRenderTargetID  ID of the render window.
    ///
    /// \return A render window of the game
    ///
    ////////////////////////////////////////////////////////////
    sf::RenderWindow& GetWindow ( RenderTargets::ID eRenderTargetID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the width of the main window.
    ///
    /// \return The width of the main window
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetWindowWidth ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the height of the main window.
    ///
    /// \return The height of the main window
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetWindowHeight ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the X of the center of the main window.
    ///
    /// \return The X of the center of the main window
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetWindowCenterX ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the Y of the center of the main window.
    ///
    /// \return The Y of the center of the main window
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetWindowCenterY ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get if the main window is open.
    ///
    /// \return True if the main window is open, false else
    ///
    ////////////////////////////////////////////////////////////
    GLboolean WindowIsOpen ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Set the pause of the game.
    ///
    /// \param bSleep   Boolean value to indicate if the pause is activated or not
    ///
    /// \see GetSleep
    ///
    ////////////////////////////////////////////////////////////
    void SetSleep ( GLboolean bSleep );

    ////////////////////////////////////////////////////////////
    /// \brief Get the pause state of the game.
    ///
    /// \return True if the game is paused, False else
    ///
    /// \see SetSleep
    ///
    ////////////////////////////////////////////////////////////
    GLboolean GetSleep ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Pop the event on top of the event queue, if any, and return it.
    ///
    /// This function is not blocking: if there's no pending event then it will
    /// return false and leave event unmodified. Note that more than one event
    /// may be present in the event queue, thus you should always call this function
    /// in a loop to make sure that you process every pending event. (see the pollevent
    /// method in the SFML render window)
    ///
    /// \param sfEvent  Event to be returned
    ///
    /// \return True if an event was returned, or false if the event queue was empty
    ///
    ////////////////////////////////////////////////////////////
    GLboolean PollEvent ( sf::Event& sfEvent );

    ////////////////////////////////////////////////////////////
    /// \brief Get the internal image of the capture of the screen.
    ///
    /// \return The internal image of the capture of the screen
    ///
    /// \see CaptureScreen
    ///
    ////////////////////////////////////////////////////////////
    sf::Image& GetScreenCapture ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Set the mouse visibility.
    ///
    /// \param bVisibility  Boolean value to indicate if the mouse is visible or not
    ///
    ////////////////////////////////////////////////////////////
    void SetMouseVisibility ( GLboolean bVisibility );

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Contains the registration of the render targets of the game.
    ///
    ////////////////////////////////////////////////////////////
    void RegisterRenderTargets ( void );
};

#endif // INCLUDE_SFML__ && INCLUDE_DRIMI__
#endif // GAMEENGINE_HPP__
