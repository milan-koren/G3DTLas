#ifndef LASVLRGEOKEYENTRY_H
#define LASVLRGEOKEYENTRY_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Key entry of GeoKeys tag.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


/*!
 * *****************************************************************
 * Coordinate Reference System VLR defined by LAS Specification
 * *****************************************************************
 */

/*!
 * OGC Math transform WKT
 * User ID: LASF_Projection
 * Record ID: 2111
 * null terminated strings, UTF-8, C locale-based numeric strings
*/

/*!
 * OGC Coordinate System WKT
 * User ID: LASF_Projection
 * Record ID: 2112
 * null terminated strings, UTF-8, C locale-based numeric strings
*/

/*!
 * GeoKeyDirectoryTag (GeoTIFF)
 * User ID: LASF_Projection
 * Record ID: 34735
 * null terminated strings, UTF-8, C locale-based numeric strings
*/

/*!
 * GeoDoubleParamsTag (GeoTIFF)
 * User ID: LASF_Projection
 * Record ID: 34736
 * array of doubles
 */

/*!
 * GeoAsciiParamsTag (GeoTIFF)
 * User ID: LASF_Projection
 * Record ID: 34737
 * array of strings separated by null value
 */


#pragma pack(1)

/*!
 * \brief The key entry of geo tags.
 * \sa VLRGeoKeys
 */
struct LasVLRGeoKeyEntry
{
    quint16 keyID;              //!< defined in GeoTIFF specification
    quint16 tiffTagLocation;    //!< valueOffset interpretation
                                //!< 0: unsigned short
                                //!< 34736: valueOffset is the index of the GeoDoubleParamsTag record
                                //!< 34737: valueOffset is the index of the GeoAsciiParamsTag record
    quint16 count;              //!< 1, or number of string characters for values of GeoAsciiParamsTag
    quint16 valueOffset;        //!< interpreted by tiffTagLocation flag
};

#pragma pack()

#endif // LASVLRGEOKEYENTRY_H
