########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

# We use the lower case name
# on UNIX systems other than Mac OS X
if ( WIN32 OR APPLE )
    project( Translatorman )
else()
    project( translatorman )
endif()

set( PACKNAME "translatorman" )

message(STATUS "Compiling for "${PROJECT_NAME})

cmake_minimum_required( VERSION 2.4.8 )

SET( TRANSLATORMAN_VERSION 0.1.0 )
STRING( REGEX MATCHALL "[0-9]+" TRANSLATORMAN_VERSIONS ${TRANSLATORMAN_VERSION} )
LIST( GET TRANSLATORMAN_VERSIONS 0 TRANSLATORMAN_VERSION_MAJOR)
LIST( GET TRANSLATORMAN_VERSIONS 1 TRANSLATORMAN_VERSION_MINOR)
LIST( GET TRANSLATORMAN_VERSIONS 2 TRANSLATORMAN_VERSION_PATCH)

message(STATUS "-DQT_QMAKE_EXECUTABLE="${QT_QMAKE_EXECUTABLE})
message(STATUS "-DQT_MOC_EXECUTABLE="${QT_MOC_EXECUTABLE})
message(STATUS "-DQT_RCC_EXECUTABLE="${QT_RCC_EXECUTABLE})
message(STATUS "-DQT_UIC_EXECUTABLE="${QT_UIC_EXECUTABLE})
message(STATUS "-DQT_LIBRARY_DIR="${QT_LIBRARY_DIR})
message(STATUS "-DQT_QTCORE_LIBRARY="${QT_QTCORE_LIBRARY})


# Check if platform is 64 bit
if( NOT APPLE )
   if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
     set( 64_BIT_PLATFORM 0 )
   else()
     set( 64_BIT_PLATFORM 1 )
   endif()
endif()


if( APPLE )
    # We need this to make sure g++ and the linker
# create exes that can run on 10.6+
    set( CMAKE_OSX_DEPLOYMENT_TARGET "10.6" )

    # 10.6 is the required minimum OS X version.
    set( CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.6.sdk" )

    # Universal builds for mac
    set( CMAKE_OSX_ARCHITECTURES "i386;x86_64" )
endif( APPLE )

# Differences between CMake 2.4 and 2.6
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.4)
   message(STATUS "Using cmake version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" )
   # some developers may be using an cmake cvs version which didn't have set_property() yet
   # Tell them that a more recent version is required.
   if(NOT COMMAND SET_PROPERTY)
      message(FATAL_ERROR "You are using an old version of CMake from cvs, please update to CMake >= 2.6.0 or cvs at least from Feb 20th, 2008")
   endif(NOT COMMAND SET_PROPERTY)


   # CMake 2.6 gives errors if there are multiple targets with the same name
   # we use this for the target "buildtests", which is created for the unit tests
   # and which depends on the tests, so building "buildtests" builds all the tests
   # enabling this property disables this check in CMake
   set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS 1)
   
   # CMP0002: in KDE4 we have multiple targets with the same name for the unit tests
   cmake_policy(SET CMP0002 OLD)
   # CMP0003: add the link paths to the link command as with cmake 2.4
   cmake_policy(SET CMP0003 OLD)
   # CMake 2.6 uses the full file names of the libraries when linking and so 
   # doesn't use -L anymore to list the link dirs. Now the dependencies created
   # export_library_dependencies() lists the in-project libraries without 
   # path, i.e. with only the logical name ("kdecore"), so they don't link
   # Setting this variable to true has the effect that the link dirs are
   # listed nevertheless also with CMake 2.6.
   set(CMAKE_LINK_OLD_PATHS TRUE)

   # list command no longer ignores empty elements.
   cmake_policy(SET CMP0007 OLD)

endif("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.4)


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



if(WIN32)
set( TRANSLATORMAN_CONFIG_DIR $ENV{ProgramFiles}/translatorman/etc CACHE PATH "The translatorman of translatorman configuration dir")
endif(WIN32)

if(NOT WIN32)
set( TRANSLATORMAN_CONFIG_DIR /etc/translatorman CACHE PATH "The location of translatorman configuration dir")
endif(NOT WIN32)

if(WIN32)
set( TRANSLATORMAN_OPTWARE_DIR $ENV{ProgramFiles}/translatorman/opt CACHE PATH "The location of translatorman optware dir")
endif(WIN32)

if(NOT WIN32)
set( TRANSLATORMAN_OPTWARE_DIR /opt/translatorman CACHE PATH "The location of translatorman optware dir")
endif(NOT WIN32)

if(WIN32)
set(HOME_DIR $ENV{USERPROFILE})
endif(WIN32)

if(NOT WIN32)
set(HOME_DIR $ENV{HOME})
endif(NOT WIN32)

#INCLUDE (${CMAKE_CURRENT_SOURCE_DIR}/ModulesCMake/FindSqlite3.cmake)

option(ENABLE_PCH  "Enable precompiled headers" OFF)

SET(USE_PCH FALSE)

IF(ENABLE_PCH)
    IF(NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" STRLESS "2.6")
        FIND_PACKAGE(PCHSupport)
        IF(PCHSupport_FOUND)
            SET(USE_PCH TRUE)
            MESSAGE(STATUS "Enabling precompiled headers for GCC ${gcc_compiler_version}")
        ELSE(PCHSupport_FOUND)
            MESSAGE(STATUS "Sorry, precompiled headers require GCC >= 3.4")
        ENDIF(PCHSupport_FOUND)
    ELSE(NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" STRLESS "2.6")
        MESSAGE(STATUS "Sorry, precompiled headers require CMake >= 2.6")
    ENDIF(NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" STRLESS "2.6")
ENDIF(ENABLE_PCH)

##############################################################################
# Sets the location of nonstandard shared libraries
##############################################################################

# Use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# When building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# The RPATH to be used when installing
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_definitions(${QT_DEFINITIONS})
include_directories(${QT_INCLUDES})


message(STATUS "Working on core")
if(APPLE)
    set( PLATFORM "OSX" )
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)


# Specify platform var for installjammer (we will use it later)
if ( WIN32 )
    set( PLATFORM "Windows" )
else()
    if ( 64_BIT_PLATFORM )
        set( PLATFORM "Linux-x86_64" )
    else()
        set( PLATFORM "Linux-x86" )
    endif()
endif()

message(STATUS "Compiling for "${PLATFORM})

IF(USE_PCH)
    ADD_PRECOMPILED_HEADER( translatorman_pch pch/stableheaders.hpp )
ENDIF(USE_PCH)


########### core library ##########
message(STATUS "Working on core")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../core" "${CMAKE_CURRENT_BINARY_DIR}/core")

########### qt4 library ##########
message(STATUS "Working on qt4-libraries")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../qt4" "${CMAKE_CURRENT_BINARY_DIR}/qt4")

set (r_files README.es license.txt)
install(FILES ${r_files} DESTINATION share/translatorman/)

#install(DIRECTORY images DESTINATION share/translatorman/imagesrc PATTERN ".svn" EXCLUDE)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Translatorman Project")
SET(CPACK_PACKAGE_VENDOR "DanielRipoll.es for Pamcli")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../../license.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${TRANSLATORMAN_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${TRANSLATORMAN_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${TRANSLATORMAN_VERSION_PATCH})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}")
IF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/../../images/icons\\\\icontranslatorman.xpm")
SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\translatorman")
SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} The Translatorman Project")
SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.danielripoll.es/projects/translatorman")
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.danielripoll.es/projects/translatorman")
SET(CPACK_NSIS_CONTACT "translatorman@danielripoll.es")
SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
SET(CPACK_STRIP_FILES "bin/translatorman")
SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "translatormanqt4")


INCLUDE(CPack)

MARK_AS_ADVANCED(
    TRANSLATORMAN_VERSION
)
