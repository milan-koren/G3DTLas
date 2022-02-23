#ifndef G3DTLAS_GLOBAL_H
#define G3DTLAS_GLOBAL_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file g3dtlas_global.h
 *
 * \brief System generated include file.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include <QtCore/qglobal.h>
#include <QtCore>

#if defined(G3DTLAS_LIBRARY)
#  define G3DTLAS_EXPORT Q_DECL_EXPORT
#else
#  define G3DTLAS_EXPORT Q_DECL_IMPORT
#endif

#endif // G3DTLAS_GLOBAL_H
