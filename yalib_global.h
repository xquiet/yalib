#ifndef YALIB_GLOBAL_H
#define YALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(YALIB_LIBRARY)
#  define YALIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define YALIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // YALIB_GLOBAL_H
