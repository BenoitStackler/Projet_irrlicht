cmake_minimum_required(VERSION 3.10)

project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
if(NOT ${OPENGL_FOUND})
  message("OpenGL not found")
endif()

include_directories(${CMAKE_SOURCE_DIR}/irrlicht-1.8.4/include)

file(GLOB source_files "src/*.cpp")
file(GLOB header_files "src/*.hpp")

message("Source files")
foreach(line IN LISTS source_files)
  message("${line}")
endforeach()

message("Header files")
foreach(line IN LISTS header_files)
  message("${line}")
endforeach()

if (WIN32)
  set(IRRLICHT_LIBRARY ${CMAKE_SOURCE_DIR}/irrlicht-1.8.4/lib/Win64-VisualStudio/irrlicht.lib)
  set(LINK_FLAGS )
elseif (APPLE)
  set(LINK_FLAGS )
elseif (UNIX)
  link_directories(${CMAKE_SOURCE_DIR}/irrlicht-1.8.4/lib/Linux/)
  set(LINK_FLAGS Irrlicht GL Xxf86vm Xext X11 Xcursor )
  add_definitions(-g)
endif ()

add_executable(game ${source_files} ${header_files})
#target_link_libraries(game  ${LINK_FLAGS} ${IRRLICHT_LIBRARY})
target_link_libraries(game  ${LINK_FLAGS} ${OPENGL_LIBRARIES})

set_target_properties(game PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT game)
