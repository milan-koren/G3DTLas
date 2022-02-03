#ifndef LASFILEHEADER_H
#define LASFILEHEADER_H

#include <QtCore>
#include <QFile>
#include "g3dtlas_global.h"


/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasfile.h
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


#define LAS11_FILE_SIGNATURE "LASF"
#define LAS11_FILE_SIGNATURE_LENGTH (4)
#define LAS11_NUMBER_OF_POINTS_BY_RETURN_FIELDS (5)
#define LAS11_SYSTEMID_LENGTH (32)
#define LAS11_GENERATING_SOFTWARE_LENGTH (32)
#define LAS11_GUID4_LENGTH (8)
#define LAS14_NUMBER_OF_POINTS_BY_RETURN_FIELDS (15)


#pragma pack(1)

/*!
 * \brief LAS 1.1 file header
 * \remark size = 227
 */
struct LasFileHeader11
{
    char file_signature[LAS11_FILE_SIGNATURE_LENGTH];
    quint16 file_source_id;
    quint16 reserved; //!< bit field
    quint32 projectGUID1; //!< project's globally unique identifier
    quint16 projectGUID2;
    quint16 project_guid3;
    char project_guid4[LAS11_GUID4_LENGTH];
    quint8 version_major;
    quint8 version_minor;
    char system_id[LAS11_SYSTEMID_LENGTH];  //!< scanner name / MERGE / MODIFICATION / EXTRACTION / TRANSFORMATION / OTHER
    char generating_software[LAS11_GENERATING_SOFTWARE_LENGTH];
    quint16 creation_day_of_year; //!< GMT
    quint16 creation_year;
    quint16 header_size;
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
};


/*!
 * \brief LAS 1.2 file header
 * \remark size = 227
 * \remark same as LAS 1.1
 * \remark globalEncoding bit field used
 */
struct LasFileHeader12
{
    char file_signature[LAS11_FILE_SIGNATURE_LENGTH];
    quint16 file_source_id;
    quint16 global_encoding; //!< bit field
                             //!< bit 0 = GPS time, since LAS 1.2
                             //!< bits 1:15 = reserved, must be set to 0
    quint32 project_guid1;   //!< project's globally unique identifier
    quint16 project_guid2;
    quint16 project_guid3;
    char project_guid4[LAS11_GUID4_LENGTH];
    quint8 version_major;
    quint8 version_minor;
    char system_id[LAS11_SYSTEMID_LENGTH]; //!< scanner name / MERGE / MODIFICATION / EXTRACTION / TRANSFORMATION / OTHER
    char generating_software[LAS11_GENERATING_SOFTWARE_LENGTH];
    quint16 creation_day_of_year; //!< GMT
    quint16 creation_year;
    quint16 header_size;
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
};


/*!
 * \brief LAS 1.3 file header
 * \remark size = 235
 */
struct LasFileHeader13
{
    char file_signature[LAS11_FILE_SIGNATURE_LENGTH];
    quint16 file_source_id;
    quint16 global_encoding; //!< bit field
                             //!< bit 0 = GPS time, since LAS 1.2
                             //!< bits 1:15 = reserved, must be set to 0
    quint32 project_guid1; //!< project's globally unique identifier
    quint16 project_guid2;
    quint16 project_guid3;
    char project_guid4[LAS11_GUID4_LENGTH];
    quint8 version_major;
    quint8 version_minor;
    char system_id[LAS11_SYSTEMID_LENGTH]; //!< scanner name / MERGE / MODIFICATION / EXTRACTION / TRANSFORMATION / OTHER
    char generating_software[LAS11_GENERATING_SOFTWARE_LENGTH];
    quint16 creation_day_of_year; //!< GMT
    quint16 creation_year;
    quint16 header_size;
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
};


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
    quint64 offset_evlrs; //!< offset of the first extended variable length records
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

#endif // LASFILEHEADER_H
