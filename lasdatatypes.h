#ifndef LASDATATYPES_H
#define LASDATATYPES_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasdatatypes.h
 *
 * \brief Standard LAS data types.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"


/*!
 * \brief The LasDataTypes enumeration by LAS standard.
 */
enum LasDataTypes
{
    UNKNOWN = 0,
    UINT8 = 1,
    INT8 = 2,
    UINT16 = 3,
    INT16 = 4,
    UINT32 = 5,
    INT32 = 6,
    UINT64 = 7,
    INT64 = 8,
    FLOAT = 9,
    DOUBLE = 10
};

#endif // LASDATATYPES_H
