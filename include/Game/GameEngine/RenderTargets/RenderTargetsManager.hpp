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
 * \file RenderTargetsManager.hpp
 * \brief Class to manage the render targets.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2015-2016
 *
 */

#ifndef RENDERTARGETSMANAGER_HPP__
#define RENDERTARGETSMANAGER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/Includes.hpp>

#include "RenderTargetsIdentifiers.hpp"
#include "RenderTargetsDefinitions.hpp"

////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////
namespace RenderTarget {
  typedef std::unique_ptr<sf::RenderTarget> Ptr;  ///< Unique pointer of render target.
}

////////////////////////////////////////////////////////////
/// \brief Class to manage the render targets.
///
////////////////////////////////////////////////////////////
class RenderTargetsManager : sf::NonCopyable {

  public :
    ////////////////////////////////////////////////////////////
    // Enumeration
    ////////////////////////////////////////////////////////////
    enum Error {
      NONE,
      UNREGISTERED_OBJECT,
      UNCONSTRUCTED_OBJECT
    };

  private :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<RenderTargets::ID, RenderTarget::Ptr>::size_type Size_type;  ///< std::map::size_type of created render target list
    typedef std::pair<RenderTargets::ID, RenderTarget::Ptr>           Pair;       ///< std::pair of created render target.

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<GLuint, RenderTarget::Ptr>       m_mList;        ///< List of created render target.
    std::map<RenderTargets::ID,
        std::function<RenderTarget::Ptr ()>>  m_mFactories;   ///< List of functions to call constructor of the specific render targets.
    GLboolean                                 m_bFullScreen;  ///< Variable to check if fullscreen is activated or not.
    GLuint                                    m_uiError;      ///< Error value if an error arose.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a manager of render targets .
    ///
    ////////////////////////////////////////////////////////////
    RenderTargetsManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the manager of render targets.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderTargetsManager ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Register a render target in the list.
    ///
    /// \tparam T   Type of the specific render target.
    ///
    /// \param eRenderTargetID  ID of the render target to register.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    void RegisterRenderTarget ( RenderTargets::ID eRenderTargetID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a render target in the list.
    ///
    /// \param eRenderTargetID  ID of the registered render target.
    ///
    ////////////////////////////////////////////////////////////
    void AddRenderTarget ( RenderTargets::ID eRenderTargetID );

    ////////////////////////////////////////////////////////////
    /// \brief Remove a render target in the list.
    ///
    /// \param eRenderTargetID  ID of the registered render target.
    ///
    ////////////////////////////////////////////////////////////
    Size_type DeleteRenderTarget ( RenderTargets::ID eRenderTargetID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list is empty.
    ///
    /// \return True if the list is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmpty ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified render target.
    ///
    /// \param eRenderTargetID  ID of the registered render target.
    ///
    /// \return Render target or NULL.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetRenderTargetObject ( RenderTargets::ID eRenderTargetID );

    ////////////////////////////////////////////////////////////
    /// \brief Set the activation of the fullscreen.
    ///
    /// \param bFullScreen  State of the fullscreen.
    ///
    ////////////////////////////////////////////////////////////
    void SetFullScreen ( GLboolean bFullScreen );

    ////////////////////////////////////////////////////////////
    /// \brief Get if the fullscreen is activated or not.
    ///
    /// \return True if the fullscreen is activated, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsFullScreen ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckError ( void );

  private:
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Create a type of specific render target.
    ///
    /// \param eRenderTargetID   ID of the registered render target.
    ///
    /// \return Pointer of constructed render target.
    ///
    ////////////////////////////////////////////////////////////
    Pair CreateRenderTarget ( RenderTargets::ID eRenderTargetID );
};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
void RenderTargetsManager::RegisterRenderTarget ( RenderTargets::ID eRenderTargetID ) {
	m_mFactories[eRenderTargetID] = [this] () {
		return RenderTarget::Ptr (new T ());
	};
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
T& RenderTargetsManager::GetRenderTargetObject ( RenderTargets::ID eRenderTargetID ) {
  auto mFound = m_mList.find (eRenderTargetID);
  if (mFound == m_mList.end ()) {
    m_uiError = Error::UNCONSTRUCTED_OBJECT;

    AddRenderTarget ( eRenderTargetID );
    return static_cast<T&>(*m_mList[eRenderTargetID]);
  }
  return static_cast<T&>(*mFound->second);
}

#endif // RENDERTARGETSMANAGER_HPP__
