#ifndef LASFILE_H
#define LASFILE_H

#include <QtCore>
#include <QFile>
#include "g3dtlas_global.h"
#include "lasvlr.h"
#include "lasevlr.h"
#include "lasfileheader.h"
#include "laspoint.h"


/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasfile.h
 *
 * \brief LasFile class declaration.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 *
 * LAS Specification 1.4 R15
 * https://www.asprs.org/divisions-committees/lidar-division/laser-las-file-format-exchange-activities
 * https://github.com/ASPRSorg/LAS
 * *****************************************************************
 */


#define LAS_DEFAULT_CACHE_NRECORDS (1024*1024)
#define LAS_DEFAULT_CACHE_OFFSET (0)


/* General LAS-file structure
     * public header block
     * VLRs
     * point data
     * EVLRs
*/


/*!
 * \brief The LasFile class
 */
class G3DTLAS_EXPORT LasFile
{
protected:
    static const quint16 StandardPointRecordLength[LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS ]; //!< array of the standard lenghts of point records

    QFile file;                     //!< data file
    LasFileHeader14 header;         //!< file header
    bool headerChanged = false;     //!< file header change flag

    typedef void (*FPointFromBufferFunction)(char *buf, LasPoint &lasPoint); //!< point record decoder template
    static const FPointFromBufferFunction PointFromBufferFunctions[LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS]; //!< array of point decoders
    FPointFromBufferFunction point_from_buf_fn = LasFile::decodePointNull; //!< pointer to current point record decoder

    typedef void (*FPointToBufferFunction)(LasPoint &lasPoint, char *buf); //!< point record encoder template
    static const FPointToBufferFunction PointToBufferFunctions[LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS]; //!< array of point encoders
    FPointToBufferFunction point_to_buf_fn = LasFile::encodePointNull; //!< pointer to current point record encoder

    qint64 cacheFirstRecord = -1;   //!< index of the first record in cache memory
    qint64 cacheLastRecord = -1;    //!< index of the last record in cache
    qint64 cacheNumberOfRecords = 0; //!< number of records stored in cache
    qint64 cacheLength = 0;         //!< the size of allocated cache in bytes (== cacheNRecords * header.pointRecordLength)
    qint64 cacheOffset = 0;         //!< offset of the first requested record in cache, used in ReadCache
    char *cache = nullptr;          //!< pointer to internal cache
    bool cacheChanged = false;      //!< cache change flag
    bool pointsChanged = false;     //!< file change flag

public:
    LasFile();
    ~LasFile();

    bool open(QString fileName, qint64 pointCacheNRecords = LAS_DEFAULT_CACHE_NRECORDS, qint64 pointCacheOffset = LAS_DEFAULT_CACHE_OFFSET);
    bool close();
    bool isOpen();
    bool createCompatible(QString fileName, LasFile &lasTemplate, qint64 pointCacheNRecords = LAS_DEFAULT_CACHE_NRECORDS, qint64 pointCacheOffset = LAS_DEFAULT_CACHE_OFFSET);

    QString getFileSignature();
    quint8 getMajorVersion();
    quint8 getMinorVersion();
    QString getFileVersion();
    QString getSystemID();
    QString getGeneratingSoftware();
    quint16 getCreationDOY();
    quint16 getCreationYear();
    QString getCreationDate();
    quint16 getHeaderSize();
    quint32 getOffsetToPointData();
    quint32 getNumberOfVLRs();
    quint32 getNumberOfEVLRs();
    quint8 getPointFormat();
    quint16 getPointRecordLength();
    quint16 getStandardPointRecordLength();
    quint64 getNumberOfPoints();
    quint32 getNumberOfPointByReturnFields();
    quint64 getPointsByReturn(qint64 n);
    double getX0();
    double getY0();
    double getZ0();
    double getX1();
    double getY1();
    double getZ1();
    bool hasWaveform();

    bool readVLR(qint64 iVLR, LasVLR &vlr);
    bool appendVLR(LasVLR &vlr);

    bool readPoint(qint64 iPoint, LasPoint &lasPoint);

    bool appendPoint(char *lasPoint);
    bool appendPoint(LasPoint &lasPoint, bool scaleCoordinates = true);
    bool appendPoints(LasFile &las);
    bool appendPoints(QString lasFileName);

public:
    static bool merge(QString fileName1, QString fileName2, QString outputFileName);
    static bool append(QString targetLasFileName, QString sourceLasFileName);

protected:
    static void decodePointNull(char *buf, LasPoint &lasPoint);
    static void decodePoint0(char *buf, LasPoint &lasPoint);
    static void decodePoint1(char *buf, LasPoint &lasPoint);
    static void decodePoint2(char *buf, LasPoint &lasPoint);
    static void decodePoint3(char *buf, LasPoint &lasPoint);
    static void decodePoint4(char *buf, LasPoint &lasPoint);
    static void decodePoint5(char *buf, LasPoint &lasPoint);
    static void decodePoint6(char *buf, LasPoint &lasPoint);
    static void decodePoint7(char *buf, LasPoint &lasPoint);
    static void decodePoint8(char *buf, LasPoint &lasPoint);
    static void decodePoint9(char *buf, LasPoint &lasPoint);
    static void decodePoint10(char *buf, LasPoint &lasPoint);
    void decodeExtraData(char *buf, LasPoint &lasPoint);

    static void encodePointNull(LasPoint &lasPoint, char *buf);
    static void encodePoint0(LasPoint &lasPoint, char *buf);
    static void encodePoint1(LasPoint &lasPoint, char *buf);
    static void encodePoint2(LasPoint &lasPoint, char *buf);
    static void encodePoint3(LasPoint &lasPoint, char *buf);
    static void encodePoint4(LasPoint &lasPoint, char *buf);
    static void encodePoint5(LasPoint &lasPoint, char *buf);
    static void encodePoint6(LasPoint &lasPoint, char *buf);
    static void encodePoint7(LasPoint &lasPoint, char *buf);
    static void encodePoint8(LasPoint &lasPoint, char *buf);
    static void encodePoint9(LasPoint &lasPoint, char *buf);
    static void encodePoint10(LasPoint &lasPoint, char *buf);
    void encodeExtraData(LasPoint &lasPoint, char *buf);

    bool writeHeader();
    bool updateHeader();

    bool copyVRLs(LasFile &lasTemplate);
    bool copyEVRLs(LasFile &lasTemplate);

    bool allocatePointCache(qint64 pointCacheNumberOfRecords, qint64 pointCacheOffset);
    bool writePointCache();
    bool readPointCache(qint64 iPoint);
};

#endif // LASFILE_H
