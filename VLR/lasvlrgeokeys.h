#ifndef LASVLRGEOKEYS_H
#define LASVLRGEOKEYS_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasvlrgeokeys.h
 *
 * \brief The directory of geo keys.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"
#include "lasvlrgeokeyentry.h"

/*!
 * \brief The LasGeoKeys class.
 * \sa VLRGeoKeyEntry
 */
class LasVLRGeoKeys
{
public:
    quint16 keyDirectoryVersion = 0;
    quint16 keyRevision = 0;
    quint16 minorRevision = 0;
    quint16 numberOfKeys = 0;
    LasVLRGeoKeyEntry *keys = nullptr;

public:
    ~LasVLRGeoKeys();
    void destroy();
};

#endif // LASVLRGEOKEYS_H
