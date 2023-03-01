#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QF4CPLUS_LIB)
#  define QF4CPLUS_EXPORT Q_DECL_EXPORT
# else
#  define QF4CPLUS_EXPORT Q_DECL_IMPORT
# endif
#else
# define QF4CPLUS_EXPORT
#endif

