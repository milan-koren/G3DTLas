#include "lasfile.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief The implementation of the LasFile class.
 * \remark The class LasPoint is used to access and update data.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


const quint16 LasFile::StandardPointRecordLength[LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS ] =
    { sizeof(LasPoint0), sizeof(LasPoint1), sizeof(LasPoint2),
      sizeof(LasPoint3), sizeof(LasPoint4), sizeof(LasPoint5),
      sizeof(LasPoint6), sizeof(LasPoint7), sizeof(LasPoint8),
      sizeof(LasPoint9), sizeof(LasPoint10)
    };

const LasFile::FPointFromBufferFunction LasFile::PointFromBufferFunctions[LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS ] =
    { LasFile::decodePoint0, LasFile::decodePoint1, LasFile::decodePoint2,
      LasFile::decodePoint3, LasFile::decodePoint4, LasFile::decodePoint5,
      LasFile::decodePoint6, LasFile::decodePoint7, LasFile::decodePoint8,
      LasFile::decodePoint9, LasFile::decodePoint10
    };

const LasFile::FPointToBufferFunction LasFile::PointToBufferFunctions[LAS_NUMBER_OF_POINT_RECORD_DATA_FORMATS ] =
    { LasFile::encodePoint0, LasFile::encodePoint1, LasFile::encodePoint2,
      LasFile::encodePoint3, LasFile::encodePoint4, LasFile::encodePoint5,
      LasFile::encodePoint6, LasFile::encodePoint7, LasFile::encodePoint8,
      LasFile::encodePoint9, LasFile::encodePoint10
    };


/*!
 * \brief Default constructor.
 */
LasFile::LasFile()
{
}


/*!
 * \brief Destructor.
 */
LasFile::~LasFile()
{
    close();
}


/*!
 * \brief Opens las-file for reading.
 * \param fileName Input las-file name.
 * \return If las-file was successfully open, returns true.
 */
bool LasFile::open(QString fileName, qint64 pointcache_number_of_records, qint64 pointcache_offset)
{
    bool error = true;

    close();
    this->dataFile.setFileName(fileName);
    if (this->dataFile.open(QFile::ReadWrite))
        if (this->dataFileHeader.read(dataFile))
        {
            if (this->dataFileHeader.point_format <= 10)
            {
                this->pointToBufFn = PointToBufferFunctions[this->dataFileHeader.point_format];
                this->pointFromBufFn = PointFromBufferFunctions[this->dataFileHeader.point_format];
                error = false;
            }
        }

    if (!error) error = !allocatePointCache(pointcache_number_of_records, pointcache_offset);

    if (error) close();
    return !error;
}


/*!
 * \brief Closes las-file and releases allocated resources.
 * \return If las-file was successfully closed, returns true.
 * \remark Input stream is always closed.
 */
bool LasFile::close()
{
    bool error;

    error = !writePointCache();
    if (!error) error = !updateHeader();
    if (!error) error = !writeHeader();

    if (this->cacheData != nullptr)
    {
        delete [] this->cacheData;
        this->cacheData = nullptr;
    }

    this->cacheFirstRecord = -1;
    this->cacheLastRecord = -1;
    this->cacheNumberOfRecords = 0;
    this->cacheLength = 0;
    this->cacheOffset = 0;

    if (this->dataFile.isOpen()) this->dataFile.close();
    this->dataFileHeader.setNull();

    return !error;
}


/*!
 * \brief Checks if las-file is open.
 * \return True, if las-file is open.
 */
inline bool LasFile::isOpen()
{
    return this->dataFile.isOpen();
}


/*!
 * \brief Creates a new las-file 1.4 compatible with a given template.
 * \param fileName New las-file name.
 * \param lasTemplate Las-file template, open for reading.
 * \return True, if compatible las-file was created successfuly.
 */
bool LasFile::createCompatible(QString fileName, LasFile &lasTemplate, qint64 pointcache_number_of_records, qint64 pointcache_offset)
{
    bool error = true;
    QDate dt;

    close();
    QFile::remove(fileName);
    if (!lasTemplate.isOpen()) return false;

    this->dataFile.setFileName(fileName);
    if (this->dataFile.open(QFile::ReadWrite))
    {
        this->dataFileHeader.setFileSignature();
        this->dataFileHeader.globalEncoding = lasTemplate.dataFileHeader.globalEncoding;
        this->dataFileHeader.versionMajor = 1;
        this->dataFileHeader.versionMinor = 4;
        this->dataFileHeader.setSystemID("OTHER");
        this->dataFileHeader.setGeneratingSoftware("G3DTLas");
        dt = QDate::currentDate();
        this->dataFileHeader.creationDayOfYear = quint16(dt.dayOfYear());
        this->dataFileHeader.creationYear = quint16(dt.year());
        this->dataFileHeader.headerSize = sizeof(LasFileHeader14);
        this->dataFileHeader.offset_to_point_data = sizeof(LasFileHeader14);
        this->dataFileHeader.number_of_evlrs = 0;
        this->dataFileHeader.point_format = lasTemplate.dataFileHeader.point_format;
        if (this->dataFileHeader.point_format <= 10)
        {
            this->pointToBufFn = PointToBufferFunctions[this->dataFileHeader.point_format];
            this->pointFromBufFn = PointFromBufferFunctions[this->dataFileHeader.point_format];
        }
        this->dataFileHeader.point_record_length = lasTemplate.dataFileHeader.point_record_length;
        this->dataFileHeader.scale_x = lasTemplate.dataFileHeader.scale_x;
        this->dataFileHeader.scale_y = lasTemplate.dataFileHeader.scale_y;
        this->dataFileHeader.scale_z = lasTemplate.dataFileHeader.scale_z;
        this->dataFileHeader.offset_x = lasTemplate.dataFileHeader.offset_x;
        this->dataFileHeader.offset_y = lasTemplate.dataFileHeader.offset_y;
        this->dataFileHeader.offset_z = lasTemplate.dataFileHeader.offset_z;

        this->headerChanged = true;
        error = (!writeHeader()); // write partial las-file header
        if (!error) error = (!copyVRLs(lasTemplate));
    }

    if (!error) error = !allocatePointCache(pointcache_number_of_records, pointcache_offset);
    if (error) close();

    return !error;
}


/*!
 * \brief Standard file signature.
 * \return Las-file signature string ("LASF").
 */
inline QString LasFile::getFileSignature()
{
    return this->dataFileHeader.getFileSignature();
}


/*!
 * \brief Las-file major version.
 * \return Major verion of las-file.
 * \remark Inline function.
 */
inline quint8 LasFile::getMajorVersion()
{
    return this->dataFileHeader.versionMajor;
}


/*!
 * \brief Las-file minor version.
 * \return Minor verion of las-file.
 * \remark Inline function.
 */
inline quint8 LasFile::getMinorVersion()
{
    return this->dataFileHeader.versionMinor;
}


/*!
 * \brief Reads major and minor version from las-file and combines them into version string.
 * \return Version string (major.minor).
 */
QString LasFile::getFileVersion()
{
    return QString::number(this->dataFileHeader.versionMajor) + "." + QString::number(this->dataFileHeader.versionMinor);
}


/*!
 * \brief System ID.
 * \return Identification of hardware or process used to generate point cloud.
 * \value scanner name; MERGE; MODIFICATION; EXTRACTION; TRANSFORMATION; OTHER
 */
inline QString LasFile::getSystemID()
{
    return this->dataFileHeader.getSystemID();
}


/*!
 * \brief Generating software.
 * \return Name of generating software.
 */
inline QString LasFile::getGeneratingSoftware()
{
    return this->dataFileHeader.getGeneratingSoftware();
}


/*!
 * \brief Day-of-year of file creation.
 * \return LAS-file creation day of the year (DOY).
 */
inline quint16 LasFile::getCreationDOY()
{
    return this->dataFileHeader.creationDayOfYear;
}


/*!
 * \brief Year of file creation.
 * \return Year of the las-file creation.
 */
inline quint16 LasFile::getCreationYear()
{
    return this->dataFileHeader.creationYear;
}


/*!
 * \brief Date of creation.
 * \return File creation date in formast dd.MM.yyy.
 */
QString LasFile::getCreationDate()
{
    QDate dt;

    if (0 < this->dataFileHeader.creationDayOfYear)
    {
        dt.setDate(this->dataFileHeader.creationYear, 1, 1);
        dt = dt.addDays(this->dataFileHeader.creationDayOfYear - 1);
    }
    return dt.toString("dd.MM.yyyy");
}


/*!
 * \brief Header size in bytes.
 * \return Size of the las-file this->header.
 */
inline quint16 LasFile::getHeaderSize()
{
    return this->dataFileHeader.headerSize;
}


/*!
 * \brief Offset to point data in bytes.
 * \return Offset to point data from the las-file beginning.
 */
inline quint32 LasFile::getOffsetToPointData()
{
    return this->dataFileHeader.offset_to_point_data;
}


/*!
 * \brief Number of VLRs.
 * \return Number of variable length records (VLR).
 */
inline quint32 LasFile::getNumberOfVLRs()
{
    return this->dataFileHeader.number_of_vlrs;
}


/*!
 * \brief Number of EVLRs.
 * \return Number of extended variable length records (EVLR).
 */
inline quint32 LasFile::getNumberOfEVLRs()
{
    return this->dataFileHeader.number_of_evlrs;
}


/*!
 * \brief The code of point format.
 * \return Format of points in las-file (0-10 form LAS 1.4).
 */
inline quint8 LasFile::getPointFormat()
{
    return this->dataFileHeader.point_format;
}


/*!
 * \brief The length of point record in bytes.
 * \return Point record length in the file.
 */
inline quint16 LasFile::getPointRecordLength()
{
    return this->dataFileHeader.point_record_length;
}


/*!
 * \brief The standard length of point record in bytes.
 * \return Record length of point defined by standard (may be shorter than actual point record length in the file).
 */
inline quint16 LasFile::getStandardPointRecordLength()
{
    return LasFile::StandardPointRecordLength[this->dataFileHeader.point_format];
}


/*!
 * \brief The number of points in the las-file.
 * \return Number of points stored in the las-file.
 */
inline quint64 LasFile::getNumberOfPoints()
{
    return this->dataFileHeader.number_of_points;
}


/*!
 * \brief The number of point by return fields.
 * \return Number of fields used to store the number of points by returns.
 */
inline quint32 LasFile::getNumberOfPointByReturnFields()
{
    return LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS;
}


/*!
 * \brief Points by return.
 * \param n Return number.
 * \return Number of points by n-th return.
 */
quint64 LasFile::getPointsByReturn(qint64 n)
{
    if (0 <= n && n <= LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS)
        return this->dataFileHeader.number_of_points_by_return[n];
    return 0;
}


/*!
 * \brief Returns minimum x-coordinate.
 * \return Minimum x-coordinate.
 */
inline double LasFile::getX0()
{
    return this->dataFileHeader.x0;
}


/*!
 * \brief Returns minimum y-coordinate.
 * \return Minimum y-coordinate.
 */
inline double LasFile::getY0()
{
    return this->dataFileHeader.y0;
}

/*!
 * \brief Returns minimum z-coordinate.
 * \return Minimum z-coordinate.
 */
inline double LasFile::getZ0()
{
    return this->dataFileHeader.z0;
}

/*!
 * \brief Returns maximum x-coordinate.
 * \return Maximum x-coordinate.
 */
inline double LasFile::getX1()
{
    return this->dataFileHeader.x1;
}

/*!
 * \brief Returns maximum y-coordinate.
 * \return Maximum y-coordinate.
 */
inline double LasFile::getY1()
{
    return this->dataFileHeader.y1;
}

/*!
 * \brief Returns maximum z-coordinate.
 * \return Maximum z-coordinates.
 */
inline double LasFile::getZ1()
{
    return this->dataFileHeader.z1;
}

/*!
 * \brief Waveform flag.
 * \return True, if wafe-form is included in the las-file.
 */
bool LasFile::hasWaveform()
{
    return (this->dataFileHeader.point_format == 10 || this->dataFileHeader.point_format == 9 || this->dataFileHeader.point_format == 5 || this->dataFileHeader.point_format == 4);
}


/*!
 * \brief Reads a VLR record.
 * \param iVLR VLR record index.
 * \param vlr Target CVLR object.
 * \return True, if VLR was successfuly read.
 */
bool LasFile::readVLR(qint64 iVLR, LasVLR &vlr)
{
    bool error = false;
    qint64 vlrOffset;
    qint64 i;

    vlr.destroy();
    if (iVLR < 0 || this->dataFileHeader.number_of_vlrs <= iVLR) return false;

    vlrOffset = this->dataFileHeader.headerSize - sizeof(LasVLRHeader);
    i = -1;
    while (i < iVLR && !error)
    {
        vlrOffset += vlr.header.recordLength + sizeof(LasVLRHeader);
        error = !this->dataFile.seek(vlrOffset);
        if (!error)
            error = (this->dataFile.read(reinterpret_cast<char*>(&vlr), sizeof(LasVLRHeader)) != sizeof(LasVLRHeader));
        i++;
    }

    if (!error && i == iVLR)
    {
        // read VLR data
        vlr.data = new char[vlr.header.recordLength];
        error = (dataFile.read(vlr.data, vlr.header.recordLength) != vlr.header.recordLength);
    }

    return !error;
}

/*!
 * \brief Appends a new VLR. Las-file must be open in read/write mode. VLRs must be written sequentially after the file this->header.
 * \param vlr CLasVLR object to be appended into las-file.
 * \return True, if VLR was successfuly appended to the las-file.
 */
bool LasFile::appendVLR(LasVLR &vlr)
{
    bool error;

    if (!this->dataFile.isWritable()) return false;

    error = (this->dataFile.write(reinterpret_cast<char*>(&vlr.header), sizeof(LasVLRHeader)) != sizeof(LasVLRHeader));
    if (!error)
        error = (this->dataFile.write(vlr.data, vlr.header.recordLength) != vlr.header.recordLength);
    if (!error)
    {
        this->dataFileHeader.number_of_vlrs++;
        this->dataFileHeader.offset_to_point_data += sizeof(LasVLRHeader) + vlr.header.recordLength;
    }

    this->headerChanged = true;
    return !error;
}


/*!
 * \brief Reads point from a las-file and performs coordinates transformation.
 * \param iPoint Index of point.
 * \param lasPoint CLASPoint to fill with data.
 * \return True, if point was read successfully.
 */
bool LasFile::readPoint(qint64 iPoint, LasPoint &lasPoint)
{
    qint64 recordOffset = 0;
    char *buf = nullptr;
    bool error = true;

    lasPoint.destroy();
    if (!this->dataFile.isOpen()) return false;
    if (this->dataFileHeader.number_of_points <= quint64(iPoint)) return false;

    if (this->cacheData == nullptr)
    {
        // there is no cache, direct reading from a file
        buf = new char[this->dataFileHeader.point_record_length]; // temporary cache for one record
        recordOffset = qint64(this->dataFileHeader.offset_to_point_data + quint64(iPoint) * this->dataFileHeader.point_record_length);
        if (this->dataFile.seek(recordOffset))
        {
            if (this->dataFile.read(reinterpret_cast<char*>(buf), this->dataFileHeader.point_record_length) == this->dataFileHeader.point_record_length)
            {
                pointFromBufFn(buf, lasPoint);
                decodeExtraData(buf, lasPoint);
                lasPoint.unscaleCoordinates(this->dataFileHeader.offset_x, this->dataFileHeader.offset_y, this->dataFileHeader.offset_z, this->dataFileHeader.scale_x, this->dataFileHeader.scale_y, this->dataFileHeader.scale_z);
                error = false;
            }
        }

        if (buf != nullptr) delete [] buf;
    }
    else
    {
        // cache is allocated
        if (iPoint < this->cacheFirstRecord || this->cacheLastRecord < iPoint)
            // point not in cache
            error = (!readPointCache(iPoint));
        else
            error = false;
        if (!error)
        {
            // load point from cache
            recordOffset = qint64(iPoint - this->cacheFirstRecord) * this->dataFileHeader.point_record_length;
            pointFromBufFn(this->cacheData + recordOffset, lasPoint);
            lasPoint.unscaleCoordinates(this->dataFileHeader.offset_x, this->dataFileHeader.offset_y, this->dataFileHeader.offset_z, this->dataFileHeader.scale_x, this->dataFileHeader.scale_y, this->dataFileHeader.scale_z);
        }
    }

    return !error;
}

/*!
 * \brief Appends point from a memory.
 * \param lasPoint Pointer to the buffer. The size of the buffer must be greater or equal to the this->header.pointRecordLength.
 * \return True, if point was successfuly written to the las-file.
 */
bool LasFile::appendPoint(char *buf)
{
    bool error = false;

    if (!this->dataFile.isWritable() || this->cacheData == nullptr) return false;

    this->cacheChanged = true;
    if (this->cacheFirstRecord < 0)
    {
        memcpy(this->cacheData, buf, this->dataFileHeader.point_record_length);
        this->cacheFirstRecord = qint64(this->dataFileHeader.number_of_points);
        this->cacheLastRecord = qint64(this->dataFileHeader.number_of_points);
        this->dataFileHeader.number_of_points++;
    }
    else
    {
        this->cacheLastRecord++;
        qint64 cache_offset = (this->cacheLastRecord - this->cacheFirstRecord) * this->dataFileHeader.point_record_length;
        memcpy(this->cacheData + cache_offset, buf, this->dataFileHeader.point_record_length);
        this->dataFileHeader.number_of_points++;
        if (this->cacheNumberOfRecords <= (this->cacheLastRecord - this->cacheFirstRecord + 1))
        {
            // cache full, write to the output las-file
            error = !writePointCache();
            this->cacheFirstRecord = -1;
            this->cacheLastRecord = -1;
            memset(this->cacheData, 0, size_t(this->cacheLength));
        }
    }

    this->pointsChanged = true;
    return !error;
}


/*!
 * \brief Appends las-point from an object.
 * \param lasPoint Source object.
 * \param scaleCoordinates If true, point's coordinates will be scaled.
 * \return True, if point was successfully written to the output las-file.
 */
bool LasFile::appendPoint(LasPoint &lasPoint, bool scaleCoordinates)
{
    bool error = false;

    if (!this->dataFile.isWritable() || this->cacheData == nullptr) return false;

    if (scaleCoordinates) lasPoint.scaleCoordinates(this->dataFileHeader.offset_x, this->dataFileHeader.offset_y, this->dataFileHeader.offset_z, this->dataFileHeader.scale_x, this->dataFileHeader.scale_y, this->dataFileHeader.scale_z);

    this->cacheChanged = true;
    if (this->cacheFirstRecord < 0)
    {
        this->cacheFirstRecord = qint64(this->dataFileHeader.number_of_points);
        this->cacheLastRecord = qint64(this->dataFileHeader.number_of_points);
        pointToBufFn(lasPoint, this->cacheData);
        encodeExtraData(lasPoint, this->cacheData);
        this->dataFileHeader.number_of_points++;
    }
    else
    {
        this->cacheLastRecord++;
        qint64 cache_offset = (this->cacheLastRecord - this->cacheFirstRecord) * this->dataFileHeader.point_record_length;
        pointToBufFn(lasPoint, this->cacheData + cache_offset);
        encodeExtraData(lasPoint, this->cacheData + cache_offset);
        this->dataFileHeader.number_of_points++;
        if (this->cacheNumberOfRecords <= (this->cacheLastRecord - this->cacheFirstRecord + 1))
        {
            // cache full, write to the output las-file
            error = !writePointCache();
            this->cacheFirstRecord = -1;
            this->cacheLastRecord = -1;
            memset(this->cacheData, 0, size_t(this->cacheLength));
        }
    }

    this->pointsChanged = true;
    return !error;
}


/*!
 * \brief Appends all points from a source las-file.
 * \param las Source las-file.
 * \return True, if points were succussfully appended the the las-file.
 */
bool LasFile::appendPoints(LasFile &las)
{
    bool error = false;
    qint64 iPoint;
    qint64 nPoints;
    LasPoint lasPoint;

    if (0 < this->dataFileHeader.number_of_evlrs) return false;
    if (las.dataFileHeader.point_format != this->dataFileHeader.point_format || las.dataFileHeader.point_record_length != this->dataFileHeader.point_record_length) return false;

    nPoints = qint64(las.getNumberOfPoints());
    for(iPoint=0; iPoint<nPoints && !error; iPoint++)
    {
        error = !las.readPoint(iPoint, lasPoint);
        if (!error) error = !appendPoint(lasPoint, false);
    }

    return !error;
}


/*!
 * \brief Reads and appends points from a compatible las-file. Point format, point record length and VRLs must be the same.
 * param lasFileName Las-file name.
 * return True, if points were added successfully.
 */
bool LasFile::appendPoints(QString lasFileName)
{
    bool error = false;
    LasFile las;

    error = !las.open(lasFileName);
    if (!error) error = !appendPoints(las);
    las.close();

    return !error;
}


/*!
 * \brief Merges two las-files.
 * \param fileName1 File name of the first las-file.
 * \param fileName2 File name of the second las-file.
 * \param outputFileName Outpu las-file name.
 * \return True, if las-files were sucessfully merged.
 */
bool LasFile::merge(QString fileName1, QString fileName2, QString outputFileName)
{
    bool error;
    LasFile inLas1, inLas2;
    LasFile outLas;

    if (!QFile::exists(fileName1)) return false;
    if (!QFile::exists(fileName2)) return false;
    QFile::remove(outputFileName);

    error = !inLas1.open(fileName1);
    if (!error) error = !outLas.createCompatible(outputFileName, inLas1);
    if (!error) error = !outLas.appendPoints(inLas1);
    if (!error) error = !inLas2.open(fileName2);
    if (!error) error = !outLas.appendPoints(inLas2);

    if (!error)
        error = !outLas.close();
    else
    {
        outLas.close();
        QFile::remove(outputFileName);
    }
    inLas2.close();
    inLas1.close();

    return !error;
}

/*!
 * \brief Append points from source las-file into target las-file. Las-files must be compatible.
 * \param targetLasFileName Target las-file name.
 * \param sourceLasFileName Source las-file name.
 * \return True, if points from the source las-file were successfuly appended to the target las-file.
 */
bool LasFile::append(QString targetLasFileName, QString sourceLasFileName)
{
    bool error = false;
    LasFile las;

    error = !las.open(targetLasFileName);
    if (!error) error = las.hasWaveform();

    if (!error) error = !las.appendPoints(sourceLasFileName);
    if (!error) error = !las.writePointCache();
    if (!error) error = !las.updateHeader();
    if (!error) error = !las.writeHeader();

    las.close();

    return !error;
}





/*!
 * *****************************************************************
 * Point decoders
 * *****************************************************************
 */

/*!
 * \brief Dummy decoder, does nothing.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 */
void LasFile::decodePointNull(char *, LasPoint &)
{
}


/*!
 * \brief Decodes Point0 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark x, y, z, intensity, flag, classification, userData, sourceId
 * \remark size = 20
 */
void LasFile::decodePoint0(char *buf, LasPoint &lasPoint)
{
    quint8 flag;

    lasPoint.ix = *reinterpret_cast<qint32*>(buf);
    lasPoint.iy = *reinterpret_cast<qint32*>(buf + 4);
    lasPoint.iz = *reinterpret_cast<qint32*>(buf + 8);
    lasPoint.intensity = *reinterpret_cast<quint16*>(buf + 12);
    flag = quint8(buf[14]);
    lasPoint.returnNumber = (flag & 7);
    lasPoint.numberOfReturns = ((flag >> 3) & 7);
    lasPoint.classification = quint8(buf[15]);
    lasPoint.scanAngle = buf[16];
    lasPoint.userData = quint8(buf[17]);
    lasPoint.sourceID = *reinterpret_cast<quint16*>(buf + 18);
}


/*!
 * \brief Decodes Point1 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point0 + gpsTime
 * \remark size = 28
 */
void LasFile::decodePoint1(char *buf, LasPoint &lasPoint)
{
    decodePoint0(buf, lasPoint);
    lasPoint.gpsTime = *reinterpret_cast<double*>(buf + 20);
}


/*!
 * \brief Decodes Point2 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point0 + r, g, b
 * \remark size = 26
 */
void LasFile::decodePoint2(char *buf, LasPoint &lasPoint)
{
    decodePoint0(buf, lasPoint);
    lasPoint.r = *reinterpret_cast<quint16*>(buf + 20);
    lasPoint.g = *reinterpret_cast<quint16*>(buf + 22);
    lasPoint.b = *reinterpret_cast<quint16*>(buf + 24);
}


/*!
 * \brief Decodes Point3 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point1 + r, g, b
 * \remark size = 34
 */
void LasFile::decodePoint3(char *buf, LasPoint &lasPoint)
{
    decodePoint1(buf, lasPoint);
    lasPoint.r = *reinterpret_cast<quint16*>(buf + 28);
    lasPoint.g = *reinterpret_cast<quint16*>(buf + 30);
    lasPoint.b = *reinterpret_cast<quint16*>(buf + 32);
}


/*!
 * \brief Decodes Point4 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point1 + waveform
 * \remark size = 57
 */
void LasFile::decodePoint4(char *buf, LasPoint &lasPoint)
{
    decodePoint1(buf, lasPoint);
    lasPoint.waveformPacketIndex = quint8(buf[28]);
    lasPoint.waveformDataOffset = *reinterpret_cast<quint64*>(buf + 29);
    lasPoint.waveformPacketSize = *reinterpret_cast<quint32*>(buf + 37);
    lasPoint.waveformLocation = *reinterpret_cast<float*>(buf + 41);
    lasPoint.xt = *reinterpret_cast<float*>(buf + 45);
    lasPoint.yt = *reinterpret_cast<float*>(buf + 49);
    lasPoint.zt = *reinterpret_cast<float*>(buf + 53);
}


/*!
 * \brief Decodes Point5 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point3 + waveform
 * \remark size = 63
 */
void LasFile::decodePoint5(char *buf, LasPoint &lasPoint)
{
    decodePoint3(buf, lasPoint);
    lasPoint.waveformPacketIndex = quint8(buf[34]);
    lasPoint.waveformDataOffset = *reinterpret_cast<quint64*>(buf + 35);
    lasPoint.waveformPacketSize = *reinterpret_cast<quint32*>(buf + 43);
    lasPoint.waveformLocation = *reinterpret_cast<float*>(buf + 47);
    lasPoint.xt = *reinterpret_cast<float*>(buf + 51);
    lasPoint.yt = *reinterpret_cast<float*>(buf + 55);
    lasPoint.zt = *reinterpret_cast<float*>(buf + 59);
}


/*!
 * \brief Decodes Point6 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark x, y, z, intensity, flag, classificationFlag, classification, userData, scanAngle, sourceId, gpsTime
 * \remark size = 30
 */
void LasFile::decodePoint6(char *buf, LasPoint &lasPoint)
{
    quint8 flag;

    lasPoint.ix = *reinterpret_cast<qint32*>(buf);
    lasPoint.iy = *reinterpret_cast<qint32*>(buf + 4);
    lasPoint.iz = *reinterpret_cast<qint32*>(buf + 8);
    lasPoint.intensity = *reinterpret_cast<quint16*>(buf + 12);
    flag = quint8(buf[14]);
    lasPoint.returnNumber = (flag & 15);
    lasPoint.numberOfReturns = ((flag >> 4) & 15);
    lasPoint.classificationFlag = quint8(buf[15]);
    lasPoint.classification = quint8(buf[16]);
    lasPoint.userData = quint8(buf[17]);
    lasPoint.scanAngle = *reinterpret_cast<qint16*>(buf + 18);
    lasPoint.sourceID = *reinterpret_cast<quint16*>(buf + 20);
    lasPoint.gpsTime = *reinterpret_cast<double*>(buf + 22);
}


/*!
 * \brief Decodes Point7 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point6 + r, g, b
 * \remark size = 36
 */
void LasFile::decodePoint7(char *buf, LasPoint &lasPoint)
{
    decodePoint6(buf, lasPoint);
    lasPoint.r = *reinterpret_cast<quint16*>(buf + 30);
    lasPoint.g = *reinterpret_cast<quint16*>(buf + 32);
    lasPoint.b = *reinterpret_cast<quint16*>(buf + 34);
}


/*!
 * \brief Decodes Point8 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point7 + ir
 * \remark size = 38
 */
void LasFile::decodePoint8(char *buf, LasPoint &lasPoint)
{
    decodePoint7(buf, lasPoint);
    lasPoint.ir = *reinterpret_cast<quint16*>(buf + 36);
}


/*!
 * \brief Decodes Point9 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point6 + waveform
 * \remark size = 59
 */
void LasFile::decodePoint9(char *buf, LasPoint &lasPoint)
{
    decodePoint6(buf, lasPoint);
    lasPoint.waveformPacketIndex = quint8(buf[30]);
    lasPoint.waveformDataOffset = *reinterpret_cast<quint64*>(buf + 31);
    lasPoint.waveformPacketSize = *reinterpret_cast<quint32*>(buf + 39);
    lasPoint.waveformLocation = *reinterpret_cast<float*>(buf + 43);
    lasPoint.xt = *reinterpret_cast<float*>(buf + 47);
    lasPoint.yt = *reinterpret_cast<float*>(buf + 51);
    lasPoint.zt = *reinterpret_cast<float*>(buf + 55);
}


/*!
 * \brief Decodes Point10 from byte array.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 * \remark Point8 + waveform
 * \remark size = 67
 */
void LasFile::decodePoint10(char *buf, LasPoint &lasPoint)
{
    decodePoint8(buf, lasPoint);
    lasPoint.waveformPacketIndex = quint8(buf[38]);
    lasPoint.waveformDataOffset = *reinterpret_cast<quint64*>(buf + 39);
    lasPoint.waveformPacketSize = *reinterpret_cast<quint32*>(buf + 47);
    lasPoint.waveformLocation = *reinterpret_cast<float*>(buf + 51);
    lasPoint.xt = *reinterpret_cast<float*>(buf + 55);
    lasPoint.yt = *reinterpret_cast<float*>(buf + 59);
    lasPoint.zt = *reinterpret_cast<float*>(buf + 63);
}


/*!
 * \brief Allocates memory and copy extra user data.
 * \param buf Input byte array.
 * \param lasPoint Target las-point.
 */
void LasFile::decodeExtraData(char *buf, LasPoint &lasPoint)
{
    quint32 standardRecordLength;

    standardRecordLength = getStandardPointRecordLength();
    if (standardRecordLength < this->dataFileHeader.point_record_length)
    {
        lasPoint.extraDataLength = standardRecordLength - this->dataFileHeader.point_record_length;
        lasPoint.extraData= new char[lasPoint.extraDataLength];
        memcpy(lasPoint.extraData, buf + standardRecordLength, lasPoint.extraDataLength);
    }
}





/*!
 * *****************************************************************
 * Point encoders
 * *****************************************************************
 */

/*!
 * \brief Dummy encoder, does nothing.
 * \param buf Buffer.
 * \param lasPoint LAS point to be loaded with data.
 */
void LasFile::encodePointNull(LasPoint &, char *)
{
}


/*!
 * \brief Encode Point0 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark x, y, z, intensity, flag, classification, userData, sourceId
 * \remark size = 20
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint0(LasPoint &lasPoint, char *buf)
{
    quint8 flag;

    *reinterpret_cast<qint32*>(buf) = lasPoint.ix;
    *reinterpret_cast<qint32*>(buf + 4) = lasPoint.iy;
    *reinterpret_cast<qint32*>(buf + 8) = lasPoint.iz;

    *reinterpret_cast<quint16*>(buf + 12) = lasPoint.intensity;

    flag = (lasPoint.returnNumber & 7) | ((lasPoint.numberOfReturns << 3) & 7);
    buf[14] = char(flag);

    buf[15] = char(lasPoint.classification);
    buf[16] = char(lasPoint.scanAngle & 255);
    buf[17] = char(lasPoint.userData);
    *reinterpret_cast<quint16*>(buf + 18) = lasPoint.sourceID;
}


/*!
 * \brief Encodes Point1 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point0 + gpsTime
 * \remark size = 28
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint1(LasPoint &lasPoint, char *buf)
{
    encodePoint0(lasPoint, buf);
    *reinterpret_cast<double*>(buf + 20) = lasPoint.gpsTime;
}


/*!
 * \brief Encodes Point2 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point0 + r, g, b
 * \remark size = 26
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint2(LasPoint &lasPoint, char *buf)
{
    encodePoint0(lasPoint, buf);
    *reinterpret_cast<quint16*>(buf + 20) = lasPoint.r;
    *reinterpret_cast<quint16*>(buf + 22) = lasPoint.g;
    *reinterpret_cast<quint16*>(buf + 24) = lasPoint.b;
}


/*!
 * \brief Encodes Point3 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point1 + r, g, b
 * \remark size = 34
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint3(LasPoint &lasPoint, char *buf)
{
    encodePoint1(lasPoint, buf);
    *reinterpret_cast<quint16*>(buf + 28) = lasPoint.r;
    *reinterpret_cast<quint16*>(buf + 30) = lasPoint.g;
    *reinterpret_cast<quint16*>(buf + 32) = lasPoint.b;
}


/*!
 * \brief Encodes Point4 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point1 + waveform
 * \remark size = 57
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint4(LasPoint &lasPoint, char *buf)
{
    encodePoint1(lasPoint, buf);
    buf[28] = char(lasPoint.waveformPacketIndex);
    *reinterpret_cast<quint64*>(buf + 29) = lasPoint.waveformDataOffset;
    *reinterpret_cast<quint32*>(buf + 37) = lasPoint.waveformPacketSize;
    *reinterpret_cast<float*>(buf + 41) = lasPoint.waveformLocation;
    *reinterpret_cast<float*>(buf + 45) = lasPoint.xt;
    *reinterpret_cast<float*>(buf + 49) = lasPoint.yt;
    *reinterpret_cast<float*>(buf + 53) = lasPoint.zt;
}


/*!
 * \brief Encodes Point5 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point3 + waveform
 * \remark size = 63
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint5(LasPoint &lasPoint, char *buf)
{
    encodePoint3(lasPoint, buf);
    buf[34] = char(lasPoint.waveformPacketIndex);
    *reinterpret_cast<quint64*>(buf + 35) = lasPoint.waveformDataOffset;
    *reinterpret_cast<quint32*>(buf + 43) = lasPoint.waveformPacketSize;
    *reinterpret_cast<float*>(buf + 47) = lasPoint.waveformLocation;
    *reinterpret_cast<float*>(buf + 51) = lasPoint.xt;
    *reinterpret_cast<float*>(buf + 55) = lasPoint.yt;
    *reinterpret_cast<float*>(buf + 59) = lasPoint.zt;
}


/*!
 * \brief Encodes Point6 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark x, y, z, intensity, flag, classificationFlag, classification, userData, scanAngle, sourceId, gpsTime
 * \remark size = 30
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint6(LasPoint &lasPoint, char *buf)
{
    quint8 flag;

    *reinterpret_cast<qint32*>(buf) = lasPoint.ix;
    *reinterpret_cast<qint32*>(buf + 4) = lasPoint.iy;
    *reinterpret_cast<qint32*>(buf + 8) = lasPoint.iz;

    *reinterpret_cast<quint16*>(buf + 12) = lasPoint.intensity;

    flag = (lasPoint.returnNumber & 15) | ((lasPoint.numberOfReturns << 4) & 15);
    buf[14] = char(flag);

    buf[15] = char(lasPoint.classificationFlag);
    buf[16] = char(lasPoint.classification);
    buf[17] = char(lasPoint.userData);
    *reinterpret_cast<qint16*>(buf + 18) = lasPoint.scanAngle;
    *reinterpret_cast<quint16*>(buf + 20) = lasPoint.sourceID;
    *reinterpret_cast<double*>(buf + 22) = lasPoint.gpsTime;
}


/*!
 * \brief Encodes Point7 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point6 + r, g, b
 * \remark size = 36
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint7(LasPoint &lasPoint, char *buf)
{
    encodePoint6(lasPoint, buf);
    *reinterpret_cast<quint16*>(buf + 30) = lasPoint.r;
    *reinterpret_cast<quint16*>(buf + 32) = lasPoint.g;
    *reinterpret_cast<quint16*>(buf + 34) = lasPoint.b;
}


/*!
 * \brief Encodes Point8 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point7 + ir
 * \remark size = 38
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint8(LasPoint &lasPoint, char *buf)
{
    encodePoint7(lasPoint, buf);
    *reinterpret_cast<quint16*>(buf + 36) = lasPoint.ir;
}


/*!
 * \brief Encodes Point9 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point6 + waveform
 * \remark size = 59
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint9(LasPoint &lasPoint, char *buf)
{
    encodePoint6(lasPoint, buf);
    buf[30] = char(lasPoint.waveformPacketIndex);
    *reinterpret_cast<quint64*>(buf + 31) = lasPoint.waveformDataOffset;
    *reinterpret_cast<quint32*>(buf + 39) = lasPoint.waveformPacketSize;
    *reinterpret_cast<float*>(buf + 43) = lasPoint.waveformLocation;
    *reinterpret_cast<float*>(buf + 47) = lasPoint.xt;
    *reinterpret_cast<float*>(buf + 51) = lasPoint.yt;
    *reinterpret_cast<float*>(buf + 55) = lasPoint.zt;
}


/*!
 * \brief Encodes Point10 to byte array.
 * \param lasPoint LAS point to be loaded with data.
 * \param buf Buffer.
 * \remark Point8 + waveform
 * \remark size = 67
 * \remark Coordinates must be scaled!
 */
void LasFile::encodePoint10(LasPoint &lasPoint, char *buf)
{
    encodePoint8(lasPoint, buf);
    buf[38] = char(lasPoint.waveformPacketIndex);
    *reinterpret_cast<quint64*>(buf + 39) = lasPoint.waveformDataOffset;
    *reinterpret_cast<quint32*>(buf + 47) = lasPoint.waveformPacketSize;
    *reinterpret_cast<float*>(buf + 51) = lasPoint.waveformLocation;
    *reinterpret_cast<float*>(buf + 55) = lasPoint.xt;
    *reinterpret_cast<float*>(buf + 59) = lasPoint.yt;
    *reinterpret_cast<float*>(buf + 63) = lasPoint.zt;
}


/*!
 * \brief Encodes extra data.
 * \param lasPoint Input las-point.
 * \param buf Pointer to the output buffer.
 */
void LasFile::encodeExtraData(LasPoint &lasPoint, char *buf)
{
    if (0 < lasPoint.extraDataLength)
    {
        memcpy(buf + getStandardPointRecordLength(), lasPoint.extraData, lasPoint.extraDataLength);
    }
}





/*!
 * *****************************************************************
 * LasFile I/O
 * *****************************************************************
 */

/*!
 * \brief Writes LAS 1.4 this->header.
 * \return True, if las-file header was written successfully.
 */
bool LasFile::writeHeader()
{
    bool error = false;

    if (this->dataFile.isOpen() && this->dataFile.isWritable() && this->headerChanged)
    {
        error = !this->dataFile.seek(0);
        if (!error) error = (this->dataFile.write(reinterpret_cast<char*>(&this->dataFileHeader), this->dataFileHeader.headerSize) != this->dataFileHeader.headerSize);
        this->headerChanged = error;
    }

    return !error;
}


/*!
 * \brief Updates minimum and maximum of coordinates (x0, x1, y0, y1, z0, z1), points by return values.
 * \return True, if header was updated successfully.
 */
bool LasFile::updateHeader()
{
    bool error = false;
    LasPoint p;

    if (!this->pointsChanged) return true;

    this->dataFileHeader.x0 = DBL_MAX;
    this->dataFileHeader.x1 = -DBL_MAX;
    this->dataFileHeader.y0 = DBL_MAX;
    this->dataFileHeader.y1 = -DBL_MAX;
    this->dataFileHeader.z0 = DBL_MAX;
    this->dataFileHeader.z1 = -DBL_MAX;

    for(int i = 0; i < LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS; i++)
        this->dataFileHeader.number_of_points_by_return[i] = 0;

    for(qint64 iPoint=0; iPoint<qint64(this->dataFileHeader.number_of_points) && !error; iPoint++)
    {
        error = !readPoint(iPoint, p);
        if (!error)
        {
            if (p.x < this->dataFileHeader.x0) this->dataFileHeader.x0 = p.x;
            if (this->dataFileHeader.x1 < p.x) this->dataFileHeader.x1 = p.x;
            if (p.y < this->dataFileHeader.y0) this->dataFileHeader.y0 = p.y;
            if (this->dataFileHeader.y1 < p.y) this->dataFileHeader.y1 = p.y;
            if (p.z < this->dataFileHeader.z0) this->dataFileHeader.z0 = p.z;
            if (this->dataFileHeader.z1 < p.z) this->dataFileHeader.z1 = p.z;

            if (p.returnNumber <= LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS && 0 < p.returnNumber)
                this->dataFileHeader.number_of_points_by_return[p.returnNumber - 1]++;
            else
                this->dataFileHeader.number_of_points_by_return[LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS-1]++;
        }
    }

    this->headerChanged = true;
    this->pointsChanged = false;
    return !error;
}


/*!
 * \brief Copy all VRLs from las-file template.
 * \param lasTtemplate Las-file.
 * \return True, if VRLs were copied successfully.
 * \todo Copy only necessary VRLs. Do not copy superseded VRLs.
 */
bool LasFile::copyVRLs(LasFile &lasTemplate)
{
    bool error = false;
    qint64 iVLR;
    LasVLR vlr;

    for(iVLR=0; iVLR < lasTemplate.getNumberOfVLRs() && !error; iVLR++)
    {
        error = !lasTemplate.readVLR(iVLR, vlr);
        if (!error) error = !appendVLR(vlr);
    }

    return !error;
}


/*!
 * \brief Copy all EVRLs from template las-file.
 * \attention NOT IMPLEMENTED YET.
 * \param lasTemplate Source las-file.
 * \return True, if VLRs were copied successfully.
 * \todo implement it!
 */
bool LasFile::copyEVRLs(LasFile &lasTemplate)
{
    return false;
}


/*!
 * \brief Allocates cache memory for points.
 * \param pointCacheNumberOfRecords Maximal number of records in thew cache memory (cache size in records).
 * \param pointCacheOffset
 * \return True, if cache memory was successfuly allocated.
 */
bool LasFile::allocatePointCache(qint64 pointCacheNumberOfRecords, qint64 pointCacheOffset)
{
    if (this->cacheData != nullptr)
    {
        delete [] this->cacheData;
        this->cacheData = nullptr;
    }

    if (0 < pointCacheNumberOfRecords)
    {
        // setup cache
        if (pointCacheOffset < 0) pointCacheOffset = pointCacheNumberOfRecords + pointCacheOffset;
        if (0 < pointCacheOffset && pointCacheNumberOfRecords <= pointCacheOffset) pointCacheOffset = pointCacheNumberOfRecords - 1;
        if (pointCacheOffset < 0) pointCacheOffset = 0;

        this->cacheFirstRecord = -1;
        this->cacheLastRecord = -1;
        this->cacheNumberOfRecords = pointCacheNumberOfRecords;
        this->cacheLength = this->dataFileHeader.point_record_length * pointCacheNumberOfRecords;
        this->cacheData = new char[quint64(this->cacheLength)];
        memset(this->cacheData, 0, size_t(this->cacheLength));
        this->cacheOffset = pointCacheOffset;
    }
    else
    {
        this->cacheFirstRecord = -1;
        this->cacheLastRecord = -1;
        this->cacheNumberOfRecords = 0;
        this->cacheLength = 0;
        this->cacheData = nullptr;
        this->cacheOffset = 0;
    }

    this->cacheChanged = false;
    return true;
}


/*!
 * \brief CLasfile::WritePointCache
 * \return True, if cache was written to las-file successfully.
 * \remark Cache is written only if it was changed.
 */
bool LasFile::writePointCache()
{
    qint64 nRecords, nLength;
    bool error = false;

    if (this->cacheData == nullptr) return true;

    if (this->cacheChanged && 0 <= this->cacheFirstRecord && 0 < this->dataFileHeader.number_of_points)
    {
        if (this->dataFile.seek(this->dataFileHeader.offset_to_point_data + this->cacheFirstRecord * this->dataFileHeader.point_record_length))
        {
            nRecords = this->cacheLastRecord - this->cacheFirstRecord + 1;
            nLength = nRecords * this->dataFileHeader.point_record_length;
            error = (this->dataFile.write(this->cacheData, nLength) != nLength);
            this->cacheChanged = error;
        }
    }

    return !error;
}


/*!
 * \brief CLasfile::ReadPointCache
 * \param iPoint Index of required point.
 * \return True, if cache was loaded successfully.
 * \remark Loads cache_number_of_records points into memory, so that the requested point is within the loaded cache.
 * \remark Changes in the cache are written into the las-file.
 */
bool LasFile::readPointCache(qint64 iPoint)
{
    qint64 nRecords, nLength;
    bool error = true;

    if (!this->dataFile.isReadable() || this->cacheData == nullptr) return false;

    if (0 <= iPoint && quint64(iPoint) < this->dataFileHeader.number_of_points)
    {
        this->cacheFirstRecord = iPoint - this->cacheOffset;
        if (this->cacheFirstRecord < 0) this->cacheFirstRecord = 0;
        this->cacheLastRecord = this->cacheFirstRecord + this->cacheNumberOfRecords - 1;
        if (this->dataFileHeader.number_of_points <= quint64(this->cacheLastRecord))
        {
            this->cacheLastRecord = qint64(this->dataFileHeader.number_of_points) - 1;
            this->cacheFirstRecord = this->cacheLastRecord - this->cacheNumberOfRecords + 1;
            if (this->cacheFirstRecord < 0) this->cacheFirstRecord = 0;
        }
        if (this->cacheFirstRecord <= iPoint && iPoint <= this->cacheLastRecord)
        {
            if (dataFile.seek(this->dataFileHeader.offset_to_point_data + this->cacheFirstRecord * this->dataFileHeader.point_record_length))
            {
                nRecords = this->cacheLastRecord - this->cacheFirstRecord + 1;
                nLength = nRecords * this->dataFileHeader.point_record_length;
                error = (this->dataFile.read(this->cacheData, nLength) != nLength);
                this->cacheChanged = error;
            }
        }
        else
        {
            this->cacheFirstRecord = -1;
            this->cacheLastRecord = -1;
        }
    }

    return !error;
}
