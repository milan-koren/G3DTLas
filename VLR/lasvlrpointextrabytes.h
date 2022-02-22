#ifndef LASVLRPOINTEXTRABYTES_H
#define LASVLRPOINTEXTRABYTES_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Point extra bytes. Optional VLR defined by LAS Specification.
 *
 * Extra Bytes
 * User ID: LASF_Spec
 * Record ID: 4
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#pragma pack(1)

/*!
 * \brief Extra bytes struct.
 * \remark size = 192
 */
struct LasVLRPointExtraBytes
{
    uchar reserved[2];
    uchar dataType;         //!< defined by enum LasDataTypes
    uchar options;          //!< bit 0: nodata field is relevant
                            //!< bit 1: minValue is relevant
                            //!< bit 2: maxValue is relevant
                            //!< bit 3: scale is relevant
                            //!< bit 4: offset Value is relevant
    char name[32];
    uchar unused[4];
    char nodata[8];
    uchar deprecated1[16];
    uchar minValue[8];
    uchar deprecated2[16];
    char maxValue[8];
    uchar deprecated3[16];
    double scale;
    uchar deprecated4[16];
    double offset;
    uchar deprecated5[16];
    char description[32];
};

#pragma pack()

#endif // LASVLRPOINTEXTRABYTES_H
