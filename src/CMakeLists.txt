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

cmake_minimum_required(VERSION 2.8)

project(yalib)

Include(FindQt)
find_package(Qt REQUIRED)
if (NOT QT_FOUND)
	MESSAGE(STATUS "Qt5 framework required")
endif (NOT QT_FOUND)
find_library(QT_LIBRARIES qt5)

SET( TARGETLIB "yalib" )

add_definitions(-DVERSION=${VERSION})

include( ${QT_USE_FILE} )

add_library( ${TARGETLIB} SHARED ${TARGETLIB}.cpp )
