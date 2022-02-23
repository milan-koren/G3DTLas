#ifndef LASPOINT5_H
#define LASPOINT5_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint5.h
 *
 * \brief Point Data Record Format 5
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
 * \brief Point Data Record Format 5
 * \remark Point3 + waveform
 * \remark Size = 63
 */
struct LasPoint5
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
    quint8 waveformPacketIndex; // 34
    quint64 waveformDataOffset; // 35
    quint32 waveformPacketSize; // 43
    float waveformLocation;     // 47
    float xT;                   // 51
    float yT;                   // 55
    float zT;                   // 59
};

#pragma pack()

#endif // LASPOINT5_H
