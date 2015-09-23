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
 * \file RenderList3D.hpp
 * \brief Class for the list of 3D objects to render.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2015
 *
 */

#ifndef RENDERLIST3D_HPP
#define RENDERLIST3D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/GameObjects/GameObject3D.hpp>
#include <list>

////////////////////////////////////////////////////////////
/// \brief Class to make a list of render for the 2D objects.
///
////////////////////////////////////////////////////////////
class RenderList3D {

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
    typedef std::list<GameObject3D::Ptr>::size_type Size_type;  ///< std::map::size_type of the list of 3d objects pointers
    typedef std::pair<GLuint,
        std::list<GameObject3D::Ptr>::iterator> Pair;           ///< std::pair of listed 3d objects pointers.
  public :
    typedef std::unique_ptr<RenderList3D>       Ptr;            ///< Unique pointer of render list 2D.

    ////////////////////////////////////////////////////////////
    // Structure
    ////////////////////////////////////////////////////////////
    struct ST_Datas {
      std::list<GameObject3D::Ptr>                m_lList;            ///< List of 3d objects pointers.
      std::map<GLuint,
          std::list<GameObject3D::Ptr>::iterator> m_mIndex;           ///< Index of listed 3d objects pointers.
      std::list<GameObject3D::Ptr>::iterator      m_lListIter;        ///< Internal iterator to path the list of 3d objects pointers.
      GLuint                                      m_uiIdAccumulator;  ///< Greater identifier generated since the begin
      GLuint                                      m_uiError;          ///< Error value if an error arose.

      ST_Datas    ( void );
      ~ST_Datas   ( void );
    };

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ST_Datas    m_stDatas[GameObjects3D::Type::Count];   ///< Array of datas of the system.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the render list 3D.
    ///
    ////////////////////////////////////////////////////////////
    RenderList3D          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the render list 3D.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderList3D ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3d object at the end of the list.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return Identifier of the 3d object.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint PushBack ( GameObjects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3d object at the begin of the list.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return Identifier of the 3d object.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint PushFront ( GameObjects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Add a 3d object after another 3d object in the list.
    ///
    /// \param eTypeID      Identifier of the type of the 3d object.
    ///        uiObjectID   Identifier of the preview 3d object.
    ///
    /// \return Identifier of the 3d object.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    GLuint Insert ( GameObjects3D::Type eTypeID, const GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Erase a 3d object in the list.
    ///
    /// \param eTypeID      Identifier of the type of the 3d object.
    ///        uiObjectID   Identifier of the 3d object to erase.
    ///
    /// \return New size of the list.
    ///
    ////////////////////////////////////////////////////////////
    Size_type Erase ( GameObjects3D::Type eTypeID, const GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Reset the internal iterator.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return True if the internal iterator isn't at the end of the list, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Reset ( GameObjects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Increment the internal iterator.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return True if the internal iterator isn't at the end of the list, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Advance ( GameObjects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get if the list is empty.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return True if the list is empty, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsEmpty ( GameObjects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the identified 3d object.
    ///
    /// \param eTypeID      Identifier of the type of the 3d object.
    ///        uiObjectID   Identifier of the listed 3d object.
    ///
    /// \return The 3d object found or a created 3d object and an internal error state.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetObject ( GameObjects3D::Type eTypeID, const GLuint uiObjectID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the current 3d object in the internal iterator.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return The 3d object in the internal iterator.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& GetObject ( GameObjects3D::Type eTypeID );

    ////////////////////////////////////////////////////////////
    /// \brief Get the value of an error.
    ///
    /// \param eTypeID    Identifier of the type of the 3d object.
    ///
    /// \return Value of an error.
    ///
    ////////////////////////////////////////////////////////////
    GLuint CheckError ( GameObjects3D::Type eTypeID );

  private :
    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Check what type of error arose.
    ///
    /// \param eTypeID      Identifier of the type of the 3d object.
    ///        uiObjectID   Identifier which make an error.
    ///
    ////////////////////////////////////////////////////////////
    void CheckIDError ( GameObjects3D::Type eTypeID, const GLuint uiObjectID );
};

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
GLuint RenderList3D::PushBack ( GameObjects3D::Type eTypeID ) {
  m_stDatas[eTypeID].m_lList.push_back (GameObject3D::Ptr (new T ()));
  m_stDatas[eTypeID].m_uiIdAccumulator++;
  std::list<GameObject3D::Ptr>::iterator lListLast = --m_stDatas[eTypeID].m_lList.end ();
  m_stDatas[eTypeID].m_mIndex.insert (RenderList3D::Pair (m_stDatas[eTypeID].m_uiIdAccumulator, lListLast));

  return m_stDatas[eTypeID].m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
template <typename T>
GLuint RenderList3D::PushFront ( GameObjects3D::Type eTypeID ) {
  m_stDatas[eTypeID].m_lList.push_front (GameObject3D::Ptr (new T ()));
  m_stDatas[eTypeID].m_uiIdAccumulator++;
  m_stDatas[eTypeID].m_mIndex.insert (RenderList3D::Pair (m_stDatas[eTypeID].m_uiIdAccumulator, m_stDatas[eTypeID].m_lList.begin ()));

  return m_stDatas[eTypeID].m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
template <typename T>
GLuint RenderList3D::Insert ( GameObjects3D::Type eTypeID, const GLuint uiObjectID ) {
  auto mFound = m_stDatas[eTypeID].m_mIndex.find (uiObjectID);
  if (mFound == m_stDatas[eTypeID].m_mIndex.end ()) {
    CheckIDError (eTypeID, uiObjectID);

    return 0;
  }
  m_stDatas[eTypeID].m_uiIdAccumulator++;
  m_stDatas[eTypeID].m_mIndex.insert (RenderList3D::Pair (m_stDatas[eTypeID].m_uiIdAccumulator, m_stDatas[eTypeID].m_lList.insert (m_stDatas[eTypeID].m_mIndex[uiObjectID], GameObject3D::Ptr (new T ()))));

  return m_stDatas[eTypeID].m_uiIdAccumulator;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template <typename T>
T& RenderList3D::GetObject ( GameObjects3D::Type eTypeID ) {
  return static_cast<T&> (**m_stDatas[eTypeID].m_lListIter);
}

////////////////////////////////////////////////////////////
template <typename T>
T& RenderList3D::GetObject ( GameObjects3D::Type eTypeID, const GLuint uiObjectID ) {
  auto mFound = m_stDatas[eTypeID].m_mIndex.find (uiObjectID);
  if (mFound == m_stDatas[eTypeID].m_mIndex.end ()) {
    CheckIDError (eTypeID, uiObjectID);

    m_stDatas[eTypeID].m_lList.push_back (GameObject3D::Ptr (new T ()));
    std::list<GameObject3D::Ptr>::iterator lListLast = --m_stDatas[eTypeID].m_lList.end ();
    m_stDatas[eTypeID].m_mIndex.insert (RenderList3D::Pair (uiObjectID, lListLast));
    return static_cast<T&> (**m_stDatas[eTypeID].m_mIndex[uiObjectID]);
  }
  return static_cast<T&> (**mFound->second);
}

#endif // RENDERLIST3D_HPP
