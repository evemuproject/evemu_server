#
# CMake build system file for EVEmu.
#
# Author: Bloody.Rabbit
#

##############
# Initialize #
##############
SET( TARGET_NAME        "eve-static" )
SET( TARGET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )
SET( TARGET_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )

#########
# Files #
#########
SET( INCLUDE
     "${TARGET_INCLUDE_DIR}/eveStatic.h"
 )
SET( SOURCE
     "${TARGET_SOURCE_DIR}/eveStatic.cpp"
 )

SET( inv_INCLUDE
     "${TARGET_INCLUDE_DIR}/inv/invTypes.h"
)
SET( inv_SOURCE
     "${TARGET_SOURCE_DIR}/inv/invTypes.cpp"
)


########################
# Setup the executable #
########################
SOURCE_GROUP( "src"                FILES ${SOURCE} )
SOURCE_GROUP( "src\\inv"           FILES ${inv_SOURCE} )

ADD_LIBRARY( "${TARGET_NAME}"
${SOURCE}
${inv_SOURCE}
)

TARGET_BUILD_PCH( "${TARGET_NAME}"
                  "${TARGET_INCLUDE_DIR}/eveStatic.h"
                  "${TARGET_SOURCE_DIR}/eveStatic.cpp" )
TARGET_INCLUDE_DIRECTORIES( "${TARGET_NAME}"
                            ${eve-common_INCLUDE_DIRS}
                            ${eve-core_INCLUDE_DIRS}
                            "${TARGET_INCLUDE_DIR}" )
TARGET_LINK_LIBRARIES( "${TARGET_NAME}"
                       ${UTILS_LIBRARIES}
                       "eve-core" )
