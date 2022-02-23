#ifndef LASFILEHEADER14_H
#define LASFILEHEADER14_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasfileheader14.h
 *
 * \brief LAS file headers.
 * \remark Class LasFileHeader11
 *               LasFileHeader12
 *               LasFileHeader13
 *               LasFileHeader14.
 *         Inheritance is not used due to better code readability.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include <QFile>
#include "g3dtlas_global.h"
#include "lasfileheader11.h"
#include "lasfileheader12.h"
#include "lasfileheader13.h"

#define LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS (15)

#pragma pack(1)

/*!
 * \brief LAS 1.4 file header
 * \remark size = 375
 */
class G3DTLAS_EXPORT LasFileHeader14
{
public:
    char fileSignature[LAS11_FILE_SIGNATURE_LENGTH];
    quint16 fileSourceID;
    quint16 globalEncoding; //!< bit field
                            //!< bit 0 = GPS time, since LAS 1.2
                            //!< bits 1:15 = reserved, must be set to 0
    quint32 projectGUID1; //!< project's globally unique identifier
    quint16 projectGUID2;
    quint16 projectGUID3;
    char project_guid4[LAS11_GUID4_LENGTH];
    quint8 versionMajor;
    quint8 versionMinor;
    char systemID[LAS11_SYSTEMID_LENGTH]; //!< scanner name / MERGE / MODIFICATION / EXTRACTION / TRANSFORMATION / OTHER
    char generatingSoftware[LAS11_GENERATING_SOFTWARE_LENGTH];
    quint16 creationDayOfYear; //!< GMT
    quint16 creationYear;
    quint16 headerSize;
    quint32 offset_to_point_data;
    quint32 number_of_vlrs; //!< number of variable length records
    quint8 point_format; //!< 0-1 for LAS 1.1
    quint16 point_record_length;
    quint32 legacy_number_of_points;
    quint32 legacy_number_of_points_by_return[LAS11_NUMBER_OF_POINTS_BY_RETURN_FIELDS];
    double scale_x;
    double scale_y;
    double scale_z;
    double offset_x;
    double offset_y;
    double offset_z;
    double x1; //!< max x
    double x0; //!< min x
    double y1; //!< max y
    double y0; //!< min y
    double z1; //!< max z
    double z0; //!< min z
    quint64 offset_waveform; //!< offset of the first waveform data package record
    quint64 offset_evlrs;    //!< offset of the first extended variable length record
    quint32 number_of_evlrs;
    quint64 number_of_points;
    quint64 number_of_points_by_return[LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS];

public:
    LasFileHeader14();

    void setNull();
    bool read(QFile &file);

    QString getFileSignature();
    QString getSystemID();
    QString getGeneratingSoftware();

    void setFileSignature();
    void setGeneratingSoftware(QString softwareName);
    void setSystemID(QString systemName);

private:
    QString charToQString(char *field, qint16 fieldLength);
    void qstringToChar(QString str, char *field, qint16 fieldLength);
};

#pragma pack()

#endif // LASFILEHEADER14_H
