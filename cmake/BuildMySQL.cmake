# - Build config of MySQL
# Defines several variables needed for automatic
# download and build of source archive.
#

# Search for the package
FIND_PACKAGE( "MySQL" 5.7 )
SET( PKG_FOUND "${MYSQL_FOUND}" )

IF( PKG_FOUND )
  MESSAGE ( "MySQL found." )
  RETURN()
ENDIF( PKG_FOUND )

# Choose correct platform-dependent properties
IF( WIN32 )
  IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    # Windows 64-bit
    SET( PKG_NAME "mysql-5.7.11-winx64" )
    SET( PKG_MD5 "9805750100ab3e2411f4887eb5f4cb77" )
  ELSE()
    # Windows 32-bit
    SET( PKG_NAME "mysql-5.7.11-win32" )
    SET( PKG_MD5 "710b588c8df3134c87818f765118329a" )
  ENDIF()

  # Windows
  SET( PKG_ARCHIVE "${PKG_NAME}.zip" )
  SET( PKG_IMPLIB "libmysql.lib")
  SET( PKG_LIBRARY "libmysql.dll" )

ELSEIF( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
#  IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	# MAC OS-X 64-bit
  	SET( PKG_NAME "mysql-5.7.11-osx10.10-x86_64" )
	SET( PKG_MD5 "23af80f1b4b1eaae48b5705bb146ee26")
#  ELSE()
#	# MAC OS-X 32-bit
#	SET( PKG_NAME "mysql-5.5.25a-osx10.6-x86" )
#	SET( PKG_MD5 "e382787cd7307ff68d7cc9a56c60f9d9")
#  ENDIF()
  # MAC OS-X
  SET( PKG-ARCHIVE "${PKG_NAME}.tar.gz" )
  SET( PKG-IMPLIB "libmysqlclient_r.a" )
  SET( PKG-LIBRARY "libmysqlclient_r.dylib" )

ELSE ( WIN32 )
  IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    # Linux 64-bit
    SET( PKG_NAME "mysql-5.7.11-linux-glibc2.5-x86_64" )
    SET( PKG_MD5 "bb06ac299b8bebe50f0e9de970988dcb" )
  ELSE()
    # Linux 32-bit
    SET( PKG_NAME "mysql-test-5.7.11-linux-glibc2.5-i686" )
    SET( PKG_MD5 "955288d336f3daaf3192cbd15cc03ff5" )
  ENDIF()

  # Linux
  SET( PKG_ARCHIVE "${PKG_NAME}.tar.gz" )
  SET( PKG_IMPLIB "libmysqlclient_r.a" )
  SET( PKG_LIBRARY "libmysqlclient_r.so" )
ENDIF( WIN32 )

# Cache entries
SET( MYSQL_URL
#  "http://downloads.mysql.com/archives/mysql-5.1/${PKG_ARCHIVE}"
#  "http://downloads.mysql.com/archives/mysql-5.5/${PKG_ARCHIVE}"
#   "https://downloads.skysql.com/archives/mysql-5.5/${PKG_ARCHIVE}"
   "https://dev.mysql.com/get/Downloads/MySQL-5.7/${PKG_ARCHIVE}"
  CACHE STRING "URL of the MySQL source archive" )
MARK_AS_ADVANCED( MYSQL_URL )

# Setup the needed variables
SET( PKG_URL "${MYSQL_URL}" )
SET( PKG_ARCHIVE_PREFIX "/${PKG_NAME}" )

SET( PKG_CMAKELISTS "
ADD_LIBRARY(
  \"mysql\" SHARED
  IMPORTED GLOBAL
  )
SET_TARGET_PROPERTIES(
  \"mysql\" PROPERTIES
  IMPORTED_IMPLIB \"\${CMAKE_CURRENT_SOURCE_DIR}/lib/${PKG_IMPLIB}\"
  IMPORTED_LOCATION \"\${CMAKE_CURRENT_SOURCE_DIR}/lib/${PKG_LIBRARY}\"
  )

SET( MYSQL_INCLUDE_DIRS
  \"\${CMAKE_CURRENT_SOURCE_DIR}/include\"
  PARENT_SCOPE )
SET( MYSQL_LIBRARIES
  \"mysql\"
  PARENT_SCOPE )
" )
