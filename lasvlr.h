#ifndef LASVLR_H
#define LASVLR_H

#include <QtCore>
#include "g3dtlas_global.h"


/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasvlr.h
 *
 * \brief Variable-length record.
 * \remark Main class LasVLR.
 *         Structure LasVLRHeader
 *                   LasGeoKeyEntry
 *                   LasClassificationLookupEntry
 *                   LasPointExtraBytes
 *                   LasPointWaveformPacketDescriptor
 *         Class LasGeoKeys
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#define LAS_VLR_RESERVED_LENGTH (2)
#define LAS_VLR_USERID_LENGTH (16)
#define LAS_VLR_DESCRIPTION_LENGTH (32)


#pragma pack(1)

/*!
 * \brief Header of variable-length record.
 * \remark size = 54
 */
struct LasVLRHeader
{
    char reserved[LAS_VLR_RESERVED_LENGTH];//!< set to zero
    char userID[LAS_VLR_USERID_LENGTH];    //!< registered with the LAS specification authority
    quint16 recordID;                      //!< managed by the owner of user ID
    quint16 recordLength;                  //!< size of data after VLR header
    char description[LAS_VLR_DESCRIPTION_LENGTH]; //!< the optional description of data
};



/*!
 * *****************************************************************
 * Coordinate Reference System VLR defined by LAS Specification
 * *****************************************************************
 */

/*
 * OGC Math transform WKT
 * User ID: LASF_Projection
 * Record ID: 2111
 * null terminated strings, UTF-8, C locale-based numeric strings
*/

/*
 * OGC Coordinate System WKT
 * User ID: LASF_Projection
 * Record ID: 2112
 * null terminated strings, UTF-8, C locale-based numeric strings
*/

/*
 * GeoKeyDirectoryTag (GeoTIFF)
 * User ID: LASF_Projection
 * Record ID: 34735
 * null terminated strings, UTF-8, C locale-based numeric strings
*/


/*!
 * \brief Key entry of GeoKeys tag.
 */
struct LasGeoKeyEntry
{
    quint16 keyID;              //!< defined in GeoTIFF specification
    quint16 tiffTagLocation;    //!< valueOffset interpretation
                                //!< 0: unsigned short
                                //!< 34736: valueOffset is the index of the GeoDoubleParamsTag record
                                //!< 34737: valueOffset is the index of the GeoAsciiParamsTag record
    quint16 count;              //!< 1, or number of string characters for values of GeoAsciiParamsTag
    quint16 valueOffset;        //!< interpreted by tiffTagLocation flag
};


/*!
 * \brief Container of GeoKey entries.
 */
class LasGeoKeys
{
public:
    quint16 keyDirectoryVersion = 0;
    quint16 keyRevision = 0;
    quint16 minorRevision = 0;
    quint16 numberOfKeys = 0;
    LasGeoKeyEntry *keys = nullptr;

public:
    ~LasGeoKeys();
    void destroy();
};


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



/*!
 * *****************************************************************
 * Optional VLRs defined by LAS Specification
 * *****************************************************************
 */

/*!
 * Classification Lookup
 * User ID: LASF_Spec
 * Record ID: 0
 * size = 256 records * 16 bytes per record
 */


/*!
 * \brief Classification entry of the classification lookup VLR.
 */
struct LasClassificationLookupEntry
{
    quint8 classNumber;
    char Description[15];
};


/*!
 * Text Area
 * User ID: LASF_Spec
 * Record ID: 3
 * Null terminated strings.
 */


/*!
 * Extra Bytes
 * User ID: LASF_Spec
 * Record ID: 4
 */


/*!
 * \brief Extra Bytes struct.
 * \remark size = 192
 */
struct LasPointExtraBytes
{
    uchar reserved[2];
    uchar dataType;         //!< defined by enum LasDataTypes
    uchar options;          //!< bit 0: nodata field is relevant
                            //!< bit 1: minValue is relevant
                            //!< bit 2: maxValue is relevant
                            //!< bit 3: scale is relevant
                            //!< bit 4: offset Value is relevant
    char name[32];
    uchar unused[4];
    char nodata[8];
    uchar deprecated1[16];
    uchar minValue[8];
    uchar deprecated2[16];
    char maxValue[8];
    uchar deprecated3[16];
    double scale;
    uchar deprecated4[16];
    double offset;
    uchar deprecated5[16];
    char description[32];
};


/*!
 * Superseded
 * User ID: LASF_Spec
 * Record ID: 7
 * Negating the existing VLR.
 * The existing VLR is identified by Superseded Record ID.
*/


/*!
 * Waveform Packet Descriptor
 * User ID: LASF_Spec
 * Record ID: 100 <= n <= 354 (i.e. 255 waveform packet descriptions)
 * Reguired for point data formats 4, 5, 9, and 10.
*/


/*!
 * \brief Waveform Packet Descriptor VLR.
 * \remark size = 26
 */
struct LasPointWaveformPacketDescriptor
{
    quint8 bitsPerSample;               //!< 2-32 bits
    quint8 compressionType;             //!< 0: no compression, reserved for future use
    quint32 numberOfSamples;            //!< number of samples
    quint32 temporalSamplesSpacing;     //!< picoseconds (MHz); 500 = 500 MHz
    double digitizerGain;               //!< volts = digitizingOffset + digitizingGain * waveformAmplitude
    double digitizerOffset;
};

#pragma pack()



/*!
 * \brief The LasVLR class.
 * \sa LasVLRHeader, LasGeoKeyEntry, LasClassificationLookupEntry, LasPointExtraBytes, LasPointWaveformPacketDescriptor
 * \sa LasGeoKeys
 */
class LasVLR
{
public:
    LasVLRHeader header;
    char *data = nullptr;

public:
    LasVLR();
    LasVLR(LasVLR &vlr);
    ~LasVLR();
    LasVLR &operator=(LasVLR &vlr);

    void destroy();

protected:
    void copyFrom(LasVLR &vlr);
};

#endif // LASVLR_H
