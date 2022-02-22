#ifndef LASPOINT8_H
#define LASPOINT8_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Point Data Record Format 8
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

/*!
 * \brief Point Data Record Format 8
 * \remark Point7 + IR
 * \remark Size = 38
 */
struct LasPoint8
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
    quint16 r;                  // 30
    quint16 g;                  // 32
    quint16 b;                  // 34
    quint16 ir;                 // 36
};

#pragma pack()

#endif // LASPOINT8_H
