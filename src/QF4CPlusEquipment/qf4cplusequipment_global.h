#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QF4CPLUSEQUIPMENT_LIB)
#  define QF4CPLUSEQUIPMENT_EXPORT Q_DECL_EXPORT
# else
#  define QF4CPLUSEQUIPMENT_EXPORT Q_DECL_IMPORT
# endif
#else
# define QF4CPLUSEQUIPMENT_EXPORT
#endif
