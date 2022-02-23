#ifndef LASPOINT10_H
#define LASPOINT10_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint10.h
 *
 * \brief Point Data Record Format 10
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
 * \brief Point Data Record Format 10
 * \remark Point8 + waveform
 * \remark Size = 67
 */
struct LasPoint10
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
    quint8 waveformPacketIndex; // 38
    quint64 waveformDataOffset; // 39
    quint32 waveformPacketSize; // 47
    float waveformLocation;     // 51
    float xT;                   // 55
    float yT;                   // 59
    float zT;                   // 63
};

#pragma pack()

#endif // LASPOINT10_H
