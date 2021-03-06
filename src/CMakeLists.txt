###############
# (C) 2012 - 2020 by Matteo Pasotti <matteo.pasotti@gmail.com>
# License: GPLv3
###############
SET( VERSION_MAJOR "1")
SET( VERSION_MINOR "8" )
SET( VERSION_PATCH "0" )
SET( VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${GIT_SHA1_VERSION}" )

SET( SOVERSION_MAJOR "1" )
SET( SOVERSION_MINOR "5" )
SET( SOVERSION_PATCH "0" )
SET( SOVERSION "${SOVERSION_MAJOR}.${SOVERSION_MINOR}.${SOVERSION_PATCH}" )

cmake_minimum_required(VERSION 2.8.11)

project(yalib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message( STATUS "Building on MacOSX" )
    set( MACOSX ON )
else()
    unset( MACOSX )
endif()

# Debug, RelWithDebInfo, Release
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Core REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
# include_directories(${Qt5Widgets_INCLUDE_DIRS})
# include_directories(${Qt5Core_INCLUDE_DIRS})

set(LIB_INSTALL_DIR lib CACHE PATH "Installation directory for libraries")
set(INC_INSTALL_DIR include CACHE PATH "Installation directory for headers")

set( TARGETLIB "yalib" )

add_definitions(-DVERSION=${VERSION})

if( MACOSX )
    add_library( ${TARGETLIB}
                 SHARED
                 ${TARGETLIB}.cpp
                 ${TARGETLIB}_global.h
                 ${TARGETLIB}.h )

else( MACOSX )
    add_library( ${TARGETLIB} SHARED ${TARGETLIB}.cpp )
endif( MACOSX )

# qt5_use_modules( ${TARGETLIB} Core )
target_link_libraries( ${TARGETLIB} Qt5::Core )

# setup version and soversion
set_target_properties( ${TARGETLIB} PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})

set( HEADERS yalib.h yalib_global.h )

install(TARGETS ${TARGETLIB} DESTINATION ${LIB_INSTALL_DIR})
install(FILES ${HEADERS} DESTINATION ${INC_INSTALL_DIR}/${TARGETLIB})
