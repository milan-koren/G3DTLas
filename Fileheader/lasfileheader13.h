#ifndef LASFILEHEADER13_H
#define LASFILEHEADER13_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasfileheader13.h
 *
 * \remark Class LasFileHeader13
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"
#include "lasfileheader11.h"
#include "lasfileheader12.h"

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

#endif // LASFILEHEADER13_H
