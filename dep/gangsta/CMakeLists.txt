#
# CMake build system file for EVEmu.
#
# Author: Bloody.Rabbit
#

INCLUDE_DIRECTORIES(
  "${CMAKE_CURRENT_SOURCE_DIR}"
  )
ADD_LIBRARY(
  "gangsta"
  # Source:
  "GaMath.cpp"
  "GaTypes.cpp"
  )

SET( GANGSTA_INCLUDE_DIRS
  "${CMAKE_CURRENT_SOURCE_DIR}"
  PARENT_SCOPE )
SET( GANGSTA_LIBRARIES
  "gangsta"
  PARENT_SCOPE )
