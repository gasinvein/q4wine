#ifndef LIBQ4WINE_GLOBAL_H
#define LIBQ4WINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBQ4WINE_LIBRARY)
#  define LIBQ4WINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBQ4WINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBQ4WINE_GLOBAL_H
