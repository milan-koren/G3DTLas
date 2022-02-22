#ifndef LASPOINT9_H
#define LASPOINT9_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Point Data Record Format 9
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

/*!
 * \brief Point Data Record Format 9
 * \remark Point6 + waveform
 * \remark Size = 59
 */
struct LasPoint9
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
    quint8 waveformPacketIndex; // 30
    quint64 waveformDataOffset; // 31
    quint32 waveformPacketSize; // 39
    float waveformLocation;     // 43
    float xT;                   // 47
    float yT;                   // 51
    float zT;                   // 55
};

#pragma pack()

#endif // LASPOINT9_H
