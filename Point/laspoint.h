#ifndef LASPOINT_H
#define LASPOINT_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint.h
 *
 * \brief LAS point records.
 * \remark Main class LasPoint.
 *         Structures LasPoint0, LasPoint1, ... LasPoint10.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"
#include "laspointclassification.h"
#include "laspoint0.h"
#include "laspoint1.h"
#include "laspoint2.h"
#include "laspoint3.h"
#include "laspoint4.h"
#include "laspoint5.h"
#include "laspoint6.h"
#include "laspoint7.h"
#include "laspoint8.h"
#include "laspoint9.h"
#include "laspoint10.h"

#define LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS (11)
#define LAS_NUMBER_OF_DATA_TYPES (11)


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

#endif // LASPOINT_H
