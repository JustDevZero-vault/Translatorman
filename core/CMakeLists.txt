# We use the lower case name
# on UNIX systems other than Mac OS X
if ( WIN32 OR APPLE )
    project( core )
else()
    project( core )
endif()

set( PACKNAME "translatorman" )

message(STATUS "Compiling for "${PROJECT_NAME})

cmake_minimum_required( VERSION 2.4.8 )


find_package(Qt4 REQUIRED)

if(NOT QT4_FOUND)
  message(FATAL_ERROR "Translatorman needs QT4 to compile")
endif(NOT QT4_FOUND)



# and now the version string given by qmake
STRING(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" QT_MAJOR_VERSION "${QTVERSION}")
STRING(REGEX REPLACE "^[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" QT_MINOR_VERSION "${QTVERSION}")
STRING(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" QT_PATCH_VERSION "${QTVERSION}")

if (${QT_MAJOR_VERSION}.${QT_MINOR_VERSION} LESS 4.7)
    message(FATAL_ERROR " Translatorman needs >= QT4.7 to compile")
endif (${QT_MAJOR_VERSION}.${QT_MINOR_VERSION} LESS 4.7)


INCLUDE(${QT_USE_FILE})

include_directories(
    ${QT_INCLUDE_DIR}
    ${QT_QTXML_INCLUDE_DIR}
    ${QT_QTSCRIPT_INCLUDE_DIR}
)

ADD_DEFINITIONS(-DQT_SHARED -DQT_PLUGIN)
ADD_DEFINITIONS(-DQWT_DLL -DQT_DLL -DQWT_MAKEDLL)
ADD_DEFINITIONS(-DBL_BULMALIB)

#~ IF(WIN32)
#~ ADD_DEFINITIONS(-DQWT_DLL -DQT_DLL -DQWT_MAKEDLL -DTM_TRANSLATORLIB)
#~ ENDIF(WIN32)



# Use, i.e. don't skip the full RPATH for the build tree
#~ set(CMAKE_SKIP_BUILD_RPATH  FALSE)
#~ 
#~ # When building, don't use the install RPATH already
#~ # (but later on when installing)
#~ set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
#~ 
#~ # The RPATH to be used when installing
#~ set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#~ 
#~ # Add the automatically determined parts of the RPATH
#~ # which point to directories outside the build tree to the install RPATH
#~ set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#~ 
#~ add_definitions(${QT_DEFINITIONS})
#~ include_directories(${QT_INCLUDES})

IF(USE_PCH)
    ADD_PRECOMPILED_HEADER( translatorman_pch pch/stableheaders.hpp )
ENDIF(USE_PCH)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs" "${CMAKE_CURRENT_BINARY_DIR}/libs")


#~ SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Translatorman Project")
#~ SET(CPACK_PACKAGE_VENDOR "DanielRipoll.es for Pamcli")
#~ SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}")
#~ IF(WIN32 AND NOT UNIX)
#~ SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/../../images/icons\\\\icontranslatorman.xpm")
#~ SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\translatorman")
#~ SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} The Translatorman Project")
#~ SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.danielripoll.es/projects/translatorman")
#~ SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.danielripoll.es/projects/translatorman")
#~ SET(CPACK_NSIS_CONTACT "translatorman@danielripoll.es")
#~ SET(CPACK_NSIS_MODIFY_PATH ON)
#~ ELSE(WIN32 AND NOT UNIX)
#~ SET(CPACK_STRIP_FILES "bin/man2html")
#~ SET(CPACK_SOURCE_STRIP_FILES "")
#~ ENDIF(WIN32 AND NOT UNIX)
#~ SET(CPACK_PACKAGE_EXECUTABLES "man2html")
#~ 
#~ 
#~ INCLUDE(CPack)
#~ 
#~ MARK_AS_ADVANCED(
    #~ CORE_VERSION
#~ )
