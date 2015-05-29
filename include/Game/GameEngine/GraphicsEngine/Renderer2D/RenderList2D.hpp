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
 * \file RenderList2D.hpp
 * \brief Class for the list of drawable to render.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef RENDERLIST2D_HPP
#define RENDERLIST2D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <list>

////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////
namespace Drawable {
  typedef std::unique_ptr<sf::Drawable> Ptr;  ///< Unique pointer of drawable.
}

////////////////////////////////////////////////////////////
/// \brief Class to make a list of render for the 2D objects.
///
////////////////////////////////////////////////////////////
class RenderList2D {

    ////////////////////////////////////////////////////////////
    // Enumeration
    ////////////////////////////////////////////////////////////
    enum Error {
      NONE,
      UNCONSTRUCTED_OBJECT,
      OVERFLOWED_OBJECT
    };

  private :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::list<Drawable::Ptr>::size_type Size_type;  ///< std::map::size_type of the list of drawables pointers
    typedef std::pair<GLuint,
        std::list<Drawable::Ptr>::iterator>     Pair;       ///< std::pair of listed drawable pointers.
  public :
    typedef std::unique_ptr<RenderList2D>       Ptr;        ///< Unique pointer of render list 2D.

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::list<Drawable::Ptr>                m_lList;      ///< List of drawables pointers.
    std::map<GLuint,
        std::list<Drawable::Ptr>::iterator> m_mIndex;     ///< Index of listed drawables pointers.
    std::list<Drawable::Ptr>::iterator      m_lListIter;  ///< Internal iterator to path the list of drawables pointers.
    GLuint                                  m_uiIdAccumulator;  ///< Greater identifier generated since the begin
    GLuint                                  m_uiError;    ///< Error value if an error arose.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the render list 2D.
    ///
    ////////////////////////////////////////////////////////////
    RenderList2D          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the render list 2D.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderList2D ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Add a drawable at the end of the list.
    ///
    /// \return Identifier of the drawable.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint PushBack ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Add a drawable at the begin of the list.
    ///
    /// \return Identifier of the drawable.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint PushFront ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Add a drawable after another drawable in the list.
    ///
    /// \param uiDrawableID   Identifier of the preview drawable.
    ///
    /// \return Identifier of the drawable.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint Insert ( GLuint uiDrawableID );

    ////////////////////////////////////////////////////////////
    /// \brief Erase a drawable in the list.
    ///
    /// \param uiDrawableID   Identifier of the drawable to erase.
    ///
    /// \return New size of the list.
    ///
    ////////////////////////////////////////////////////////////
    Size_type Erase ( const GLuint uiDrawableID );

    ////////////////////////////////////////////////////////////
    /// \brief Reset the internal iterator.
    ///
    /// \return True if the internal iterator isn't at the end of the list, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Reset ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Increment the internal iterator.
    ///
    /// \return True if the internal iterator isn't at the end of the list, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Advance ( void );

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
    /// \brief Get the identified drawable.
    ///
    /// \param uiDrawableID   Identifier of the listed drawable.
    ///
    /// \return Drawable found or a created drawable and an internal error state.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetDrawable ( GLuint uiDrawableID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the current drawable in the internal iterator.
    ///
    /// \return Drawable in the internal iterator.
    ///
    ////////////////////////////////////////////////////////////
    sf::Drawable& GetDrawable ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckError ( void );

  private :
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Check what type of error arose.
    ///
    /// \param uiDrawableID   Identifier which make an error.
    ///
    ////////////////////////////////////////////////////////////
    void CheckIDError ( GLuint uiDrawableID );
};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
GLuint RenderList2D::PushBack ( void ) {
  m_lList.push_back (Drawable::Ptr (new T ()));
  m_uiIdAccumulator++;
  std::list<Drawable::Ptr>::iterator lListLast = --m_lList.end ();
  m_mIndex.insert (RenderList2D::Pair (m_uiIdAccumulator, lListLast));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
template <typename T>
GLuint RenderList2D::PushFront ( void ) {
  m_lList.push_front (Drawable::Ptr (new T ()));
  m_uiIdAccumulator++;
  m_mIndex.insert (RenderList2D::Pair (m_uiIdAccumulator, m_lList.begin ()));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
template <typename T>
GLuint RenderList2D::Insert ( GLuint uiDrawableID ) {
  auto mFound = m_mIndex.find (uiDrawableID);
  if (mFound == m_mIndex.end ()) {
    CheckIDError (uiDrawableID);

    return 0;
  }
  m_uiIdAccumulator++;
  m_mIndex.insert (RenderList2D::Pair (m_uiIdAccumulator, m_lList.insert (m_mIndex[uiDrawableID], Drawable::Ptr (new T ()))));

  return m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
T& RenderList2D::GetDrawable ( GLuint uiDrawableID ) {
  auto mFound = m_mIndex.find (uiDrawableID);
  if (mFound == m_mIndex.end ()) {
    CheckIDError (uiDrawableID);

    m_lList.push_back (Drawable::Ptr (new T ()));
    std::list<Drawable::Ptr>::iterator lListLast = --m_lList.end ();
    m_mIndex.insert (RenderList2D::Pair (uiDrawableID, lListLast));
    return static_cast<T&> (**m_mIndex[uiDrawableID]);
  }
  return static_cast<T&> (**mFound->second);
}

#endif // RENDERLIST2D_HPP
