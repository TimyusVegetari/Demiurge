cmake_minimum_required(VERSION 2.6)

# For generators with multiple configurations (like C::B, VS, ...), only allow Debug and Release
if(NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES Debug Release)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Limited configurations to what we need" FORCE)
  mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
mark_as_advanced(CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Declaration of the project
project(Demiurge)

set(Demiurge_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/src)
set(Demiurge_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)
set(Demiurge_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/datas)
set(Demiurge_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Specific compiler options
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

	# Mac OS X: clang uses libc++ standard library
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
endif()

# User's settings - General C++ Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -Wconversion -Wsign-conversion -fexceptions -Wno-comment")
### "-Wno-comment" is temporary to by-pass a bug in glm as long as we use a version previous to 0.9.7.0

# Release / Debug flags
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# Definitions flags to compile with dependencies
add_definitions(-DGLEW_STATIC -DSFML_STATIC)

# Inclusion of the dependencies
include_directories(
        ${sfml_include_dir}
				${glew_include_dir}
				${freeimage_include_dir}
				${glm_include_dir}
)
link_directories(
        ${sfml_lib_dir}
				${glew_lib_dir}
				${freeimage_lib_dir}
)

# Inclusion of the headers
include_directories("${Demiurge_INCLUDE_DIR}")

# Generation of the sources files list
file(
        GLOB_RECURSE
				source_files
				src/*
)
# Generation of the header files list
file(
        GLOB_RECURSE
				header_files
				include/*
)

# For FreeImage on Windows
if(WIN32)
	find_library(ws2_32_LIBRARY_PATH ws2_32)
endif()

# Compilation for Debug
# Declaration of the executable
add_executable(
        Debug
        ${source_files}
        ${header_files}
)

# Configuration of the links edition
if(WIN32)
	target_link_libraries(
        Debug
				${ws2_32_LIBRARY_PATH}
				${sfml_graphics_lib_name}-d
				${sfml_window_lib_name}-d
				${gdi32_lib_name}
				${sfml_system_lib_name}-d
				${winmm_lib_name}
				${glew_lib_name}
				${glu32_lib_name}
				${opengl32_lib_name}
				${freetype_lib_name}
				${jpeg_lib_name}
				${m_lib_name}
				${freeimage_lib_name}d
)
else()
	target_link_libraries(
        Debug
				${sfml_graphics_lib_name}-d
				${sfml_window_lib_name}-d
				${gdi32_lib_name}
				${sfml_system_lib_name}-d
				${winmm_lib_name}
				${glew_lib_name}
				${glu32_lib_name}
				${opengl32_lib_name}
				${freetype_lib_name}
				${jpeg_lib_name}
				${m_lib_name}
				${freeimage_lib_name}d
)
endif()

# Configuration of the path of the program
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Demiurge_BINARY_DIR}/Debug/)
set_target_properties( Debug PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Demiurge_BINARY_DIR}/Debug/ )
set_target_properties( Debug PROPERTIES RUNTIME_OUTPUT_NAME demiurge_dbg )
set_target_properties( Debug PROPERTIES COMPILE_FLAGS "-O0 -g3" )

# Compilation for Release
# Declaration of the executable
add_executable(
        Release
        ${source_files}
)

# Configuration of the links edition
target_link_libraries(
        Release
				${sfml_graphics_lib_name}
				${sfml_window_lib_name}
				${gdi32_lib_name}
				${sfml_system_lib_name}
				${winmm_lib_name}
				${glew_lib_name}
				${glu32_lib_name}
				${opengl32_lib_name}
				${freetype_lib_name}
				${jpeg_lib_name}
				${m_lib_name}
				${freeimage_lib_name}
)

# Configuration of the path of the program
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Demiurge_BINARY_DIR}/Release/)
set_target_properties( Release PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Demiurge_BINARY_DIR}/Release/ )
set_target_properties( Release PROPERTIES RUNTIME_OUTPUT_NAME demiurge )
set_target_properties( Release PROPERTIES COMPILE_FLAGS "-O3 -DNDEBUG" )
