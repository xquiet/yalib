###############
# (C) 2012 by Matteo Pasotti <matteo.pasotti@gmail.com>
# License: GPLv3
###############
SET( VERSION_MAJOR "1")
SET( VERSION_MINOR "0" )
SET( VERSION_PATCH "0" )
SET( VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${GIT_SHA1_VERSION}" )

SET( SONAME_MAJOR "2" )
SET( SONAME_MINOR "0" )
SET( SONAME_PATCH "0" )
SET( SONAME "${SONAME_MAJOR}.${SONAME_MINOR}.${SONAME_PATCH}" )

cmake_minimum_required(VERSION 2.8.11)

project(yalib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
# find_package(Qt5Widgets REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})

SET( TARGETLIB "yalib" )

add_definitions(-DVERSION=${VERSION})

add_library( ${TARGETLIB} SHARED ${TARGETLIB}.cpp )
