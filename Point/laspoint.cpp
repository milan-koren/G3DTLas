/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspoint.cpp
 *
 * \brief The implemenation of the LasPoint class.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "laspoint.h"


/*!
 * \brief Default constructor.
 */
LasPoint::LasPoint()
{
}


/*!
 * \brief Default copy constructor.
 * \param lasPoint LAS-point to copy from.
 */
LasPoint::LasPoint(LasPoint &lasPoint)
{
    copyFrom(lasPoint);
}


/*!
 * \brief Virtual destructor. Releases allocated resources.
 */
LasPoint::~LasPoint()
{
    destroy();
}


/*!
 * \brief Copy operator. Extra data are copied into allocated memory.
 * \param lasPoint Source las-point.
 * \return Self reference.
 */
LasPoint &LasPoint::operator=(LasPoint &lasPoint)
{
    copyFrom(lasPoint);
    return *this;
}


/*!
 * Releases allocated memory and sets properties to default values.
 */
void LasPoint::destroy()
{
    this->ix = 0;
    this->iy = 0;
    this->iz = 0;

    this->intensity = 0;
    this->classificationFlag = 0;
    this->classification = 0;

    this->userData = 0;
    this->scanAngle = 0;

    this->sourceID = 0;
    this->gpsTime = 0;

    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->ir = 0;

    this->waveformPacketIndex = 0;
    this->waveformDataOffset = 0;
    this->waveformPacketSize = 0;
    this->waveformLocation = 0;
    this->xt = 0;
    this->yt = 0;
    this->zt = 0;

    this->returnNumber = 0;
    this->numberOfReturns = 0;

    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;

    this->extraDataLength = 0;
    if (this->extraData != nullptr)
    {
        delete [] this->extraData;
        this->extraData = nullptr;
    }
}


/*!
 * \brief Scales coordinates from double to integer.
 * \param offsetX Offset of x-coordinate.
 * \param offsetY Offset of y-coordinate.
 * \param offsetZ Offset of z-coordinate.
 */
void LasPoint::scaleCoordinates(double offsetX, double offsetY, double offsetZ, double scaleX, double scaleY, double scaleZ)
{
    this->ix = qint32(scaleX != 0.0 ? round(this->x - offsetX) / scaleX : round(this->x - offsetX));
    this->iy = qint32(scaleY != 0.0 ? round(this->y - offsetY) / scaleY : round(this->y - offsetY));
    this->iz = qint32(scaleZ != 0.0 ? round(this->z - offsetZ) / scaleZ : round(this->z - offsetZ));
}


/*!
 * \brief The reverse scale of coordinates from integer to double.
 * \param offsetX Offset of x-coordinate.
 * \param offsetY Offset of y-coordinate.
 * \param offsetZ Offset of z-coordinate.
 */
void LasPoint::unscaleCoordinates(double offsetX, double offsetY, double offsetZ, double scaleX, double scaleY, double scaleZ)
{
    this->x = scaleX != 0.0 ? offsetX + scaleX * this->ix : offsetX + this->ix;
    this->y = scaleY != 0.0 ? offsetY + scaleY * this->iy : offsetY + this->iy;
    this->z = scaleZ != 0.0 ? offsetZ + scaleZ * this->iz : offsetX + this->iz;
}


/*!
 * \brief Creates the deep copy of a given las-point.
 * \param lasPoint Source las-point.
 */
void LasPoint::copyFrom(LasPoint &lasPoint)
{
    destroy();

    this->ix = lasPoint.ix;
    this->iy = lasPoint.iy;
    this->iz = lasPoint.iz;

    this->intensity = lasPoint.intensity;
    this->classificationFlag = lasPoint.classificationFlag;
    this->classification = lasPoint.classification;

    this->userData = lasPoint.userData;
    this->scanAngle = lasPoint.scanAngle;

    this->sourceID = lasPoint.sourceID;
    this->gpsTime = lasPoint.gpsTime;

    this->r = lasPoint.r;
    this->g = lasPoint.g;
    this->b = lasPoint.b;
    this->ir = lasPoint.ir;

    this->waveformPacketIndex = lasPoint.waveformPacketIndex;
    this->waveformDataOffset = lasPoint.waveformDataOffset;
    this->waveformPacketSize = lasPoint.waveformPacketIndex;
    this->waveformLocation = lasPoint.waveformLocation;
    this->xt = lasPoint.xt;
    this->yt = lasPoint.yt;
    this->zt = lasPoint.zt;

    this->returnNumber = lasPoint.returnNumber;
    this->numberOfReturns = lasPoint.numberOfReturns;

    this->x = lasPoint.x;
    this->y = lasPoint.y;
    this->z = lasPoint.z;

    this->extraDataLength = lasPoint.extraDataLength;
    if (0 < this->extraDataLength)
    {
        this->extraData = new char[this->extraDataLength];
        memcpy(this->extraData, lasPoint.extraData, this->extraDataLength);
    }
}
