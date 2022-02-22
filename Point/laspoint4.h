#ifndef LASPOINT4_H
#define LASPOINT4_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Point Data Record Format 4
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

/*!
 * \brief Point Data Record Format 4
 * \remark Point1 + waveform
 * \remark Size = 57
 */
struct LasPoint4
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
    quint8 waveformPacketIndex; // 28
    quint64 waveformDataOffset; // 29
    quint32 waveformPacketSize; // 37
    float waveformLocation;     // 41
    float xT;                   // 45
    float yT;                   // 49
    float zT;                   // 53
};

#pragma pack()

#endif // LASPOINT4_H
