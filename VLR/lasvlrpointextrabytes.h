#ifndef LASVLRPOINTEXTRABYTES_H
#define LASVLRPOINTEXTRABYTES_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasvlrpointextrabytes.h
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

#include "g3dtlas_global.h"

#pragma pack(1)

/*!
 * \brief Extra bytes struct.
 * \remark size = 192
 */
struct LasVLRPointExtraBytes
{
    quint8 reserved[2];
    quint8 dataType;        //!< defined by enum LasDataTypes
    quint8 options;         //!< bit 0: nodata field is relevant
                            //!< bit 1: minValue is relevant
                            //!< bit 2: maxValue is relevant
                            //!< bit 3: scale is relevant
                            //!< bit 4: offset Value is relevant
    char name[32];
    quint8 unused[4];
    char nodata[8];
    quint8 deprecated1[16];
    char minValue[8];
    quint8 deprecated2[16];
    char maxValue[8];
    quint8 deprecated3[16];
    double scale;
    quint8 deprecated4[16];
    double offset;
    quint8 deprecated5[16];
    char description[32];
};

#pragma pack()

#endif // LASVLRPOINTEXTRABYTES_H
