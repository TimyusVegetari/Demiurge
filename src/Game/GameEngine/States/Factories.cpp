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
// The code in this file is inspired by the book "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/States/Factories.hpp>

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
States::Factories::ST_Factory::ST_Factory ( void ) :
  m_fpConstructor (nullptr),
  m_pInitializer  (nullptr),
  m_bLocked       (GL_FALSE),
  m_bInitializing (GL_FALSE),
  m_szName        ("")
{
}

////////////////////////////////////////////////////////////
void States::Factories::ST_Factory::SetConstructor ( const std::string& szName, std::function<State::Ptr ()> fpConstructor ) {
  m_fpConstructor = fpConstructor;
  m_szName = szName;
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
States::Factories::Factories ( StateStack& oStateStack, GameObject::ST_Context& stContext ) :
  m_oStateStack             (oStateStack),
  m_stContext               (stContext),
  m_mFactories              (),
  m_bReplacement            (GL_FALSE),
  m_uiActivatedInitializers (0)
{
}

////////////////////////////////////////////////////////////
States::Factories::~Factories ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void States::Factories::Construct ( States::ID eStateID ) {
  if (m_mFactories[eStateID].m_pInitializer == nullptr) {
    m_mFactories[eStateID].m_pInitializer = m_mFactories[eStateID].m_fpConstructor ();
    m_mFactories[eStateID].m_bLocked = GL_TRUE;
    m_uiActivatedInitializers++;
  }
}

////////////////////////////////////////////////////////////
OutSignal States::Factories::InitializeStates ( std::vector<State::Ptr>& vStack ) {
  // For each state factory which has an initializer ready to work...
  for (auto mit = m_mFactories.begin () ; mit != m_mFactories.end () ; ++mit) {
    if ((mit->second).m_pInitializer != nullptr) {
      States::Factories::ST_Factory& stFactory = (mit->second);
      // If state's initializer isn't working, run it.
      if (!stFactory.m_bInitializing) {
        std::cout << " >> Initialization of the state '" << stFactory.m_szName << "'..." << std::endl;
        stFactory.m_bInitializing = stFactory.m_pInitializer->Initialize ();
      // Else, process to the initialisation of the game objects of the state
      } else {
        std::cout << " >> Initialization of the game objects of the state '" << stFactory.m_szName << "'..." << std::endl;
        OutSignal eOutSignal = GameObjectsInitializer (stFactory.m_pInitializer->GetInitializerID ());
        if (eOutSignal == OutSignal::Element_Failed)  ///< An error in a game object initialisation ?
          return OutSignal::Element_Failed;
        else if (eOutSignal == OutSignal::List_End) { ///< Initialization of the state is finished and succeed ?
          // The state stack order was "Replace" ?
          if (m_bReplacement) {
            vStack.pop_back ();
            m_bReplacement = GL_FALSE;
          }
          // Pass the state from initializer to the state stack.
          vStack.push_back (std::move(stFactory.m_pInitializer));
          stFactory.m_bInitializing = GL_FALSE;
          m_uiActivatedInitializers--;
          return OutSignal::List_End;
        }
      }
    }
  }
  return OutSignal::Element_Succeed;
}

////////////////////////////////////////////////////////////
void States::Factories::EnableReplacement ( void ) {
  m_bReplacement = GL_TRUE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean States::Factories::IsRegistered ( States::ID eStateID ) {
  // Check if the state identifier is legal.
  auto mFound = m_mFactories.find (eStateID);
  if (mFound == m_mFactories.end ())
    return GL_FALSE;
  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean States::Factories::IsConstructed ( States::ID eStateID ) {
  return m_mFactories[eStateID].m_bLocked;
}

////////////////////////////////////////////////////////////
GLuint States::Factories::GetInitializingCount ( void ) {
  return m_uiActivatedInitializers;
}

////////////////////////////////////////////////////////////
std::string States::Factories::GetName ( States::ID eStateID ) {
  return m_mFactories[eStateID].m_szName;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
OutSignal States::Factories::GameObjectsInitializer ( GameObjects::Initializer uiInitializer ) {
  return m_stContext.GetGameObjectsManager ().Initializer (uiInitializer);
}
