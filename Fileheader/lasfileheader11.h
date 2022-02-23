#ifndef LASFILEHEADER11_H
#define LASFILEHEADER11_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasfileheader11.h
 *
 * \remark Class LasFileHeader11
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"

#define LAS11_FILE_SIGNATURE "LASF"
#define LAS11_FILE_SIGNATURE_LENGTH (4)
#define LAS11_NUMBER_OF_POINTS_BY_RETURN_FIELDS (5)
#define LAS11_SYSTEMID_LENGTH (32)
#define LAS11_GENERATING_SOFTWARE_LENGTH (32)
#define LAS11_GUID4_LENGTH (8)

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

#pragma pack()

#endif // LASFILEHEADER11_H
