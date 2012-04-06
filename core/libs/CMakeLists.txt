#set(core_SRCS
#    main.cxx
#    core.cpp
#    tspreference.cpp
#)


set(QT_USE_QTASSISTANT false)
set(QT_USE_QTXML false)
set(QT_USE_QTSCRIPT false)
set(QT_USE_QTWEBKIT false)

#~ set (bulmalib_HDRS	blmaincompanypointer.h ..........)
file(GLOB core_SOURCES "*.c" "*.cpp")
file(GLOB core_HEADERS "*.hpp" "*.h")

set(core_RESOURCES ../../resources.qrc)
include_directories(
    ${QT_INCLUDE_DIR}
    ${QT_QTXML_INCLUDE_DIR}
    ${QT_QTSCRIPT_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/../../core/libs/
    ${CMAKE_SOURCE_DIR}/../../core/libs/
)



# generate rules for building source files from the resources
QT4_WRAP_CPP(core_MOC_SOURCES ${core_HEADERS})
QT4_ADD_RESOURCES(core_RESOURCES_SOURCES ${core_RESOURCES})


IF(WIN32)
    add_definitions(-DQWT_DLL -DQT_DLL -DQWT_MAKEDLL -DBL_BULMALIB)
ENDIF(WIN32)

# build sources, moc'd sources, and rcc'd sources

add_library(core SHARED
	${core_SOURCES} ${core_HEADERS} ${core_RESOURCES_SOURCES})

set_target_properties( core PROPERTIES 
  SOVERSION "${TRANSLATORMAN_VERSION_MAJOR}.${TRANSLATORMAN_VERSION_MINOR}"
  VERSION "${TRANSLATORMAN_VERSION}")

target_link_libraries( core ${QT_LIBRARIES} )



install_targets(/lib core)
install (FILES ${core_HEADERS} DESTINATION include)



if(USE_PCH)
   add_dependencies( core core_pch )
endif(USE_PCH)

