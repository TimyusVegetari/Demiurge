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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file RenderWindow.hpp
 * \brief Class to upgrade a sf::RenderWindow.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015
 *
 */

#ifndef GAME_RENDERWINDOW_HPP__
#define GAME_RENDERWINDOW_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to upgrade a sf::RenderWindow.
///
////////////////////////////////////////////////////////////
namespace gm {  ///< Corresponds to the word "game".

class RenderWindow : public sf::RenderWindow {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////

    sf::Image   m_sfScreenCapture;
    GLboolean   m_bSFMLEnabled;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a render window.
    ///
    ////////////////////////////////////////////////////////////
    RenderWindow ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the render window.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderWindow ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window
    ///
    /// If the window was already created, it closes it first.
    /// If \a style contains Style::Fullscreen, then \a mode
    /// must be a valid video mode.
    ///
    /// The fourth parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param sfMode     Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param sfTitle    Title of the window
    /// \param sfStyle    %Window style, a bitwise OR combination of sf::Style enumerators
    /// \param sfSettings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    inline void Create ( sf::VideoMode sfMode, const sf::String& sfTitle, sf::Uint32 sfStyle = sf::Style::Default, const sf::ContextSettings& sfSettings = sf::ContextSettings () ) {
      create (sfMode, sfTitle, sfStyle, sfSettings);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window from an existing control
    ///
    /// Use this function if you want to create an OpenGL
    /// rendering area into an already existing control.
    /// If the window was already created, it closes it first.
    ///
    /// The second parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param sfHandle   Platform-specific handle of the control (\a HWND on
    ///                   Windows, \a %Window on Linux/FreeBSD, \a NSWindow on OS X)
    /// \param sfSettings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    inline void Create ( sf::WindowHandle sfHandle, const sf::ContextSettings& sfSettings = sf::ContextSettings () );

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
    inline GLboolean PollEvent ( sf::Event& sfEvent ) { return pollEvent (sfEvent); }

    ////////////////////////////////////////////////////////////
    /// \brief Close the window.
    ///
    ////////////////////////////////////////////////////////////
    inline void Close ( void ) { close (); }

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
    /// \brief Set the title of the window.
    ///
    /// \param szTitle  Title of the window
    ///
    /// \see SetIcon
    ///
    ////////////////////////////////////////////////////////////
    inline void SetTitle ( const std::string szTitle ) { setTitle (szTitle); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the icon of the window.
    ///
    /// \a pixels must be an array of \a width x \a height pixels
    /// in 32-bits RGBA format.
    ///
    /// The OS default icon is used by default.
    ///
    /// \param uiWidth    Icon's width, in pixels
    /// \param uiHeight   Icon's height, in pixels
    /// \param puiPixels  Pointer to the array of pixels in memory. The
    ///                   pixels are copied, so you need not keep the
    ///                   source alive after calling this function.
    ///
    /// \see SetTitle
    ///
    ////////////////////////////////////////////////////////////
    inline void SetIcon ( GLuint uiWidth, GLuint uiHeight, const sf::Uint8* puiPixels ) { setIcon (uiWidth, uiHeight, puiPixels); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the rendering region of the window.
    ///
    /// \param sfSize   New size, in pixels.
    ///
    ////////////////////////////////////////////////////////////
    inline void SetSize ( sf::Vector2u sfSize ) { setSize (sfSize); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the width of the rendering region of the window.
    ///
    /// \param uiWidth  New width, in pixels.
    ///
    /// \see GetWidth
    ///
    ////////////////////////////////////////////////////////////
    inline void SetWidth ( GLuint uiWidth ) { setSize (sf::Vector2u (uiWidth, getSize ().y)); }

    ////////////////////////////////////////////////////////////
    /// \brief Get the width of the rendering region of the window.
    ///
    /// The width doesn't include the titlebar and borders
    /// of the window.
    ///
    /// \return Width in pixels.
    ///
    /// \see SetWidth
    ///
    ////////////////////////////////////////////////////////////
    inline GLuint GetWidth ( void ) { return getSize ().x; }

    ////////////////////////////////////////////////////////////
    /// \brief Set the height of the rendering region of the window.
    ///
    /// \param uiHeight New height, in pixels.
    ///
    /// \see GetHeight
    ///
    ////////////////////////////////////////////////////////////
    inline void SetHeight ( GLuint uiHeight ) { setSize (sf::Vector2u (getSize ().x, uiHeight)); }

    ////////////////////////////////////////////////////////////
    /// \brief Get the height of the rendering region of the window.
    ///
    /// The height doesn't include the titlebar and borders
    /// of the window.
    ///
    /// \return Height in pixels.
    ///
    /// \see SetHeight
    ///
    ////////////////////////////////////////////////////////////
    inline GLuint GetHeight ( void ) { return getSize ().y; }

    ////////////////////////////////////////////////////////////
    /// \brief Clear the entire target with a single color.
    ///
    /// This function is usually called once every frame,
    /// to clear the previous contents of the target.
    ///
    /// \param sfColor  Fill color to use to clear the render target.
    ///
    ////////////////////////////////////////////////////////////
    void Clear ( const sf::Color& sfColor = sf::Color(0, 0, 0, 255) ) { clear (sfColor); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the current active view.
    ///
    /// The view is like a 2D camera, it controls which part of
    /// the 2D scene is visible, and how it is viewed in the
    /// render target.
    /// The new view will affect everything that is drawn, until
    /// another view is set.
    /// The render target keeps its own copy of the view object,
    /// so it is not necessary to keep the original one alive
    /// after calling this function.
    /// To restore the original view of the target, you can pass
    /// the result of getDefaultView() to this function.
    ///
    /// \param sfView New view to use.
    ///
    /// \see GetView, getDefaultView
    ///
    ////////////////////////////////////////////////////////////
    inline void SetView ( const sf::View& sfView ) { setView (sfView); }

    ////////////////////////////////////////////////////////////
    /// \brief Get the view currently in use in the render target.
    ///
    /// \return The view object that is currently used.
    ///
    /// \see SetViewHeight, getDefaultView
    ///
    ////////////////////////////////////////////////////////////
    inline sf::View GetView ( void ) { return getView (); }

    ////////////////////////////////////////////////////////////
    /// \brief Get if the window is open.
    ///
    /// \return True if the window is open, false else.
    ///
    ////////////////////////////////////////////////////////////
    inline GLboolean IsOpen ( void ) { return isOpen (); }

    ////////////////////////////////////////////////////////////
    /// \brief Get the internal image of the capture of the screen.
    ///
    /// \return The internal image of the capture of the screen.
    ///
    /// \see CaptureScreen
    ///
    ////////////////////////////////////////////////////////////
    sf::Image& GetScreenCapture ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable vertical synchronization.
    ///
    /// Activating vertical synchronization will limit the number
    /// of frames displayed to the refresh rate of the monitor.
    /// This can avoid some visual artifacts, and limit the framerate
    /// to a good value (but not constant across different computers).
    ///
    /// Vertical synchronization is disabled by default.
    ///
    /// \param bEnabled True to enable v-sync, false to deactivate it.
    ///
    ////////////////////////////////////////////////////////////
    inline void SetVerticalSyncEnabled ( GLboolean bEnabled ) { setVerticalSyncEnabled (bEnabled); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the mouse visibility.
    ///
    /// \param bVisibility  Boolean value to indicate if the mouse is visible or not.
    ///
    ////////////////////////////////////////////////////////////
    inline void SetMouseVisibility ( GLboolean bVisibility ) { setMouseCursorVisible (bVisibility); }

    ////////////////////////////////////////////////////////////
    /// \brief Draw a drawable object to the render target
    ///
    /// \param sfDrawable Object to draw
    /// \param sfStates   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    inline void Draw ( const sf::Drawable& sfDrawable, const sf::RenderStates& sfStates = sf::RenderStates::Default ) {
      draw (sfDrawable, sfStates);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Display on screen what has been rendered to the window so far.
    ///
    /// This function is typically called after all OpenGL rendering
    /// has been done for the current frame, in order to show
    /// it on screen.
    ///
    ////////////////////////////////////////////////////////////
    inline void Display ( void ) { display (); };

    ////////////////////////////////////////////////////////////
    /// \brief Push and reset OpenGL state for SFML.
    ///
    /// This function is typically called before use SFML, after OpenGL.
    ///
    ////////////////////////////////////////////////////////////
    inline void EnableSFML ( void ) {
      if (!m_bSFMLEnabled) {
        pushGLStates ();
        resetGLStates ();
        m_bSFMLEnabled = GL_TRUE;
      }
    };

    ////////////////////////////////////////////////////////////
    /// \brief Pop OpenGL state for SFML.
    ///
    /// This function is typically called after use SFML, before OpenGL.
    ///
    ////////////////////////////////////////////////////////////
    inline void DisableSFML ( void ) {
      if (m_bSFMLEnabled) {
        popGLStates ();
        m_bSFMLEnabled = GL_FALSE;
      }
    };
};

}

#endif // GAME_RENDERWINDOW_HPP__
