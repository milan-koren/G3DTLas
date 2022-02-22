#ifndef LASPOINT3_H
#define LASPOINT3_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Point Data Record Format 3
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

/*!
 * \brief Point Data Record Format 3
 * \remark Point1 + RGB
 * \remark Size = 34
 */
struct LasPoint3
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
    quint16 r;                  // 28
    quint16 g;                  // 30
    quint16 b;                  // 32
};

#pragma pack()

#endif // LASPOINT3_H
