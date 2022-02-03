#ifndef LASPOINT_H
#define LASPOINT_H

#include <QtCore>
#include "g3dtlas_global.h"


/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint.h
 *
 * \brief LAS point records.
 * \remark Main class LasPoint.
 *         Structures LasPoint0, LasPoint1, ... LasPoint10.
 *         Enumeration LasDataTypes.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#define LAS_CLASS_NEVER_CLASSIFIED (0)
#define LAS_CLASS_UNCLASSIFIED (1)
#define LAS_CLASS_GROUND (2)
#define LAS_CLASS_LOW_VEGETATION (3)
#define LAS_CLASS_MEDIUM_VEGETATION (4)
#define LAS_CLASS_HIGH_VEGETATION (5)
#define LAS_CLASS_BUILDING (6)
#define LAS_CLASS_LOW_NOISE (7)
#define LAS_CLASS_WATER (9)
#define LAS_CLASS_BRIDGE (17)
#define LAS_CLASS_HIGH_NOISE (18)

#define LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS (11)
#define LAS_NUMBER_OF_DATA_TYPES (11)


/*!
 * \brief The LasDataTypes enumeration by LAS standard.
 */
enum LasDataTypes
{
    UNKNOWN = 0,
    UINT8 = 1,
    INT8 = 2,
    UINT16 = 3,
    INT16 = 4,
    UINT32 = 5,
    INT32 = 6,
    UINT64 = 7,
    INT64 = 8,
    FLOAT = 9,
    DOUBLE = 10
};


/*!
 * \brief The LasPoint class.
 * Main class used to read and write points from/to las-file.
 */
class G3DTLAS_EXPORT LasPoint
{
public:
    qint32 ix = 0;  //!< scaled coordinates, stored in las-file
    qint32 iy = 0;
    qint32 iz = 0;

    quint16 intensity = 0;
    quint8 classificationFlag = 0;
    quint8 classification = 0;

    quint8 userData = 0;
    qint16 scanAngle = 0;

    quint16 sourceID = 0;
    double gpsTime = 0;

    quint16 r = 0;
    quint16 g = 0;
    quint16 b = 0;
    quint16 ir = 0;

    quint8 waveformPacketIndex = 0;
    quint64 waveformDataOffset = 0;
    quint32 waveformPacketSize = 0;
    float waveformLocation = 0;
    float xt = 0;
    float yt = 0;
    float zt = 0;

    quint8 returnNumber = 0;
    quint8 numberOfReturns = 0;

    double x = 0.0; //!< not-scaled coordinates, ready to use
    double y = 0.0; //!< must be scaled before writting to las-file!
    double z = 0.0;

    quint32 extraDataLength = 0;
    char *extraData = nullptr;

public:
    LasPoint();
    LasPoint(LasPoint &lasPoint);
    virtual ~LasPoint();
    LasPoint &operator=(LasPoint &lasPoint);

    void destroy();

    void scaleCoordinates(double offsetX, double offsetY, double offsetZ, double scaleX, double scaleY, double scaleZ);
    void unscaleCoordinates(double offsetX, double offsetY, double offsetZ, double scaleX, double scaleY, double scaleZ);

protected:
    void copyFrom(LasPoint &lasPoint);
};


#pragma pack(1)

/*!
 * \remark Point Data Record Format 0
 * \remark size = 20
 */
struct LasPoint0
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
};


/*!
 * \remark Point Data Record Format 1
 * \remark Point0 + GPS time
 * \remark size = 28
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


/*!
 * \remark Point Data Record Format 2
 * \remark Point0 + RGB
 * \remark size = 26
 */
struct LasPoint2
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
    quint16 r;                  // 20
    quint16 g;                  // 22
    quint16 b;                  // 24
};

/*!
 * \remark Point Data Record Format 3
 * \remark Point1 + RGB
 * \remark size = 34
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


/*!
 * \remark Point Data Record Format 4
 * \remark Point1 + waveform
 * \remark size = 57
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


/*!
 * \remark Point Data Record Format 5
 * \remark Point3 + waveform
 * \remark size = 63
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


/*!
 * \remark Point Data Record Format 6
 * \remark x, y, z, intensity, flag, classificationFlag, classification, userData, scanAngle, sourceID, gpsTime
 * \remark flag interpretation is different from Point0-Point5
 * \remark size = 30
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


/*!
 * \remark Point Data Record Format 7
 * \remark Point6 + RGB
 * \remark size = 36
 */
struct LasPoint7
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
};


/*!
 * \remark Point Data Record Format 8
 * \remark Point7 + IR
 * \remark size = 38
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


/*!
 * \remark Point Data Record Format 9
 * \remark Point6 + waveform
 * \remark size = 59
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


/*!
 * \remark Point Data Record Format 10
 * \remark Point8 + waveform
 * \remark size = 67
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

#endif // LASPOINT_H
