#ifndef LASPOINT1_H
#define LASPOINT1_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint1.h
 *
 * \brief Point Data Record Format 1
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
 * \brief Point Data Record Format 1
 * \remark Point0 + GPS time
 * \remark Size = 28
 */
struct LasPoint1
{
    qint32 x;                   // 0
    qint32 y;                   // 4
    qint32 z;                   // 8
    quint16 intensity;          // 12
    quint8 flag;                // 14
    quint8 classification;      // 15
    qint8 scanAngle;            // 16
    quint8 userData;            // 17
    quint16 sourceID;           // 18
    double gpsTime;             // 20
};

#pragma pack()

#endif // LASPOINT1_H
