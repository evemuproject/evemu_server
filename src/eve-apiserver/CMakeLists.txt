#
# CMake build system file for EVEmu.
#
# Author: Bloody.Rabbit
#

##############
# Initialize #
##############
SET( TARGET_NAME        "eve-apiserver" )
SET( TARGET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )
SET( TARGET_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )
SET( TARGET_UTILS_DIR   "${PROJECT_SOURCE_DIR}/utils" )

#########
# Files #
#########
SET( INCLUDE
     "${TARGET_INCLUDE_DIR}/eve-apiserver.h"
)
SET( SOURCE
     "${TARGET_SOURCE_DIR}/eve-apiserver.cpp"
)

SET( apiserver_INCLUDE
     "${TARGET_INCLUDE_DIR}/apiserver/APIAccountDB.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIAccountManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIActiveObjectManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIAdminManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APICacheManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APICharacterDB.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APICharacterManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APICorporationManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIEveSystemManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIMapManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIServer.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIServerConnection.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIServerListener.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIServerManager.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIServiceDB.h"
     "${TARGET_INCLUDE_DIR}/apiserver/APIServiceManager.h" )
SET( apiserver_SOURCE
     "${TARGET_SOURCE_DIR}/apiserver/APIAccountDB.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIAccountManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIActiveObjectManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIAdminManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APICacheManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APICharacterDB.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APICharacterManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APICorporationManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIEveSystemManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIMapManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIServer.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIServerConnection.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIServerListener.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIServerManager.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIServiceDB.cpp"
     "${TARGET_SOURCE_DIR}/apiserver/APIServiceManager.cpp" )

########################
# Setup the executable #
########################
SOURCE_GROUP( "src"                FILES ${SOURCE} )
SOURCE_GROUP( "src\\apiserver"     FILES ${apiserver_SOURCE} )

ADD_EXECUTABLE( "${TARGET_NAME}"
${SOURCE}
${apiserver_SOURCE}
)

TARGET_INCLUDE_DIRECTORIES( "${TARGET_NAME}"
                            ${eve-common_INCLUDE_DIRS}
                            ${eve-static_INCLUDE_DIRS}
                            "${TARGET_INCLUDE_DIR}" )
TARGET_LINK_LIBRARIES( "${TARGET_NAME}"
                       "eve-common" 
                       "eve-static"
)
TARGET_BUILD_PCH( "${TARGET_NAME}"
                  "${TARGET_INCLUDE_DIR}/eve-apiserver.h"
                  "${TARGET_SOURCE_DIR}/eve-apiserver.cpp" )
