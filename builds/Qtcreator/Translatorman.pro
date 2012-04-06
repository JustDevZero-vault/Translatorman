#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T15:10:14
#
#-------------------------------------------------

QT       += core gui

TARGET = Translatorman
TEMPLATE = app


SOURCES +=\
        ../../qt4/main.cxx \
    ../../qt4/translatorman.cpp \
    ../../core/libs/tlfunctions.cpp \
    ../../qt4/tmpreference.cpp \
    ../../qt4/lineedit.cpp \

HEADERS  += ../../qt4/translatorman.h \
    ../../core/libs/tldefs.h \
    ../../core/libs/tlfunctions.h \
    ../../qt4/tmpreference.h \
    ../../qt4/lineedit.h \


FORMS    += \
    ../../qt4/translatormanbase.ui \
    ../../qt4/tmpreferencebase.ui

RESOURCES += \
    ../../resources.qrc \

OTHER_FILES += \
    ../CMake/CMakeLists.txt \
    ../CMake/ModulesCMake/FindSqlite3.cmake \
    ../CMake/ModulesCMake/FindPCHSupport.cmake \
    ../../qt4/CMakeLists.txt \
    ../../core/CMakeLists.txt \
    ../../core/libs/CMakeLists.txt \



















