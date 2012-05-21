PROJECT(translatormanqt4)

file(GLOB translatorman_SOURCES "*.c" "*.cpp")
file(GLOB translatorman_HEADERS "*.hpp" "*.h")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs" "${CMAKE_CURRENT_BINARY_DIR}/libs")

#file(GLOB translatorman_NO_HEADERS tscompany.h tsinforme.h)
#list(REMOVE_ITEM translatorman_HEADERS ${translatorman_NO_MOCS})

file(GLOB translatorman_UI_FILES "*.ui")

set(translatormanEx main.cxx)

set(QT_USE_QTASSISTANT false)
set(QT_USE_QTUITOOLS true)
set(QT_USE_QTXML true)
set(QT_USE_QTSCRIPT true)
set(QT_USE_QTWEBKIT true)


IF(WIN32)
    # En MS-Windows no hay soporte directo de QtDBus.
    #set(QT_USE_QTDBUS true)
ELSE(WIN32)
    set(QT_USE_QTDBUS true)
ENDIF(WIN32)


INCLUDE(${QT_USE_FILE})

include_directories(
    ${QT_INCLUDE_DIR}
    ${QT_QTXML_INCLUDE_DIR}
    ${QT_QTSCRIPT_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/../../qt4/libs/
    ${CMAKE_SOURCE_DIR}/../../qt4/libs/
    #~ ${CMAKE_BINARY_DIR}/qt4/
    #~ ${CMAKE_SOURCE_DIR}/qt4/
    )
    
#~ link_directories ( ${PROJECT_BINARY_DIR}/lib )
# generate rules for building source files that moc generates
QT4_WRAP_UI(translatorman_UI_FILES_H ${translatorman_UI_FILES})
#~ QT4_WRAP_CPP(translatorman_MOC_SOURCES ${translatorman_HEADERS})

# generate rules for building source files that moc generates
#~ QT4_WRAP_UI(translatorman_UI_FILES_H ${translatorman_UI_FILES} OPTIONS -tr N_)
QT4_WRAP_CPP(translatorman_MOC_SOURCES ${translatorman_HEADERS})

set(translatorman_RESOURCES {CMAKE_SOURCE_DIR}../../../resources.qrc)
QT4_ADD_RESOURCES(translatorman_RESOURCES_SOURCES ${translatorman_RESOURCES})

IF(WIN32)
    ADD_DEFINITIONS(-DQWT_DLL -DQT_DLL -DQWT_MAKEDLL -DTM_TRANSLATORMAN)
ENDIF(WIN32)


add_library(libtranslatorman SHARED ${translatorman_HEADERS} ${translatorman_MOC_SOURCES}
        ${translatorman_UI_FILES_H} ${translatorman_SOURCES} ${translatorman_SOURCES} ${translatorman_RESOURCES_SOURCES})


set_target_properties( libtranslatorman PROPERTIES
  SOVERSION "${TRANSLATORMAN_VERSION_MAJOR}.${TRANSLATORMAN_VERSION_MINOR}"
  VERSION "${TRANSLATORMAN_VERSION}"
  OUTPUT_NAME ${PROJECT_NAME} )


#~ add_executable(${PROJECT_NAME} ${translatormanEx} ${translatorman_RESOURCES_SOURCES})

#~ IF(USE_GETTEXT)
    #~ target_link_libraries( bulmalib ${QT_LIBRARIES} ${PGSQL_LIBRARIES} ${GETTEXT_LIBRARIES} )
#~ ELSE(USE_GETTEXT)
    #~ target_link_libraries( bulmalib ${QT_LIBRARIES} ${PGSQL_LIBRARIES} )
#~ ENDIF(USE_GETTEXT)


#~ target_link_libraries(libtranslatorman core ${QT_LIBRARIES})

#~ add_executable(${PROJECT_NAME} ${translatormanEx} ${translatorman_RESOURCES_SOURCES})

#~ target_link_libraries(bulmafact libbulmafact bulmalib ${QT_LIBRARIES} ${PGSQL_LIBRARIES})
#~ target_link_libraries(${PROJECT_NAME} libtranslatorman core ${QT_LIBRARIES})

target_link_libraries(libtranslatorman libs ${QT_LIBRARIES})

add_executable(${PROJECT_NAME} ${translatormanEx} ${bulmafact_RCC_SRCS})

target_link_libraries(${PROJECT_NAME} libtranslatorman libs ${QT_LIBRARIES})

add_dependencies(libtranslatorman libs)
add_dependencies(${PROJECT_NAME} libtranslatorman)

install_targets(/bin ${PROJECT_NAME})
install_targets(/lib libtranslatorman)
