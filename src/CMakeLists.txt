###############
# (C) 2012 by Matteo Pasotti <matteo.pasotti@gmail.com>
# License: GPLv3
###############
SET( VERSION_MAJOR "1")
SET( VERSION_MINOR "3" )
SET( VERSION_PATCH "0" )
SET( VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${GIT_SHA1_VERSION}" )

SET( SOVERSION_MAJOR "1" )
SET( SOVERSION_MINOR "1" )
SET( SOVERSION_PATCH "0" )
SET( SOVERSION "${SOVERSION_MAJOR}.${SOVERSION_MINOR}.${SOVERSION_PATCH}" )

cmake_minimum_required(VERSION 2.8.11)

project(yalib)

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

set( TARGETLIB "yalib" )

add_definitions(-DVERSION=${VERSION})

add_library( ${TARGETLIB} SHARED ${TARGETLIB}.cpp )

qt5_use_modules( ${TARGETLIB} Core )

# setup version and soversion
set_target_properties( ${TARGETLIB} PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})

set( HEADERS yalib.h yalib_global.h )

install(TARGETS yalib DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/yalib)
