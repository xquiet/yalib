/**
    Copyright (C) 2012-2020  Matteo Pasotti <matteo.pasotti@gmail.com>

    This file is part of yalib

    yalib is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    yalib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#ifndef YALIB_GLOBAL_H
#define YALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(YALIB_LIBRARY)
#  define YALIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define YALIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // YALIB_GLOBAL_H
