#ifndef LASPOINT6_H
#define LASPOINT6_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint6.h
 *
 * \brief Point Data Record Format 6
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
 * \brief Point Data Record Format 6
 * \remark x, y, z, intensity, flag, classificationFlag, classification, userData, scanAngle, sourceID, gpsTime
 * \remark Flag interpretation is different from Point0-Point5 formats.
 * \remark Size = 30
 */
struct LasPoint6
{
    qint32 x;                   // 0
    qint32 y;                   // 4
    qint32 z;                   // 8
    quint16 intensity;          // 12
    quint8 flag;                // 14
    quint8 classificationFlag;  // 15
    quint8 classification;      // 16
    quint8 userData;            // 17
    qint16 scanAngle;           // 18
    quint16 sourceID;           // 20
    double gpsTime;             // 22
};

#pragma pack()

#endif // LASPOINT6_H
