#ifndef LASEVLR_H
#define LASEVLR_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasevlr.h
 *
 * \brief Extended variable-length record.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"

#define LAS_EVLR_RESERVED_LENGTH (2)
#define LAS_EVLR_USERID_LENGTH (16)
#define LAS_EVLR_DESCRIPTION_LENGTH (32)

#pragma pack(1)

/*!
 * \brief Header of EVLR record.
 * \remark size = 60
 */
struct LasEVLRHeader
{
    char reserved[LAS_EVLR_RESERVED_LENGTH];        //!< set to zero
    char userID[LAS_EVLR_USERID_LENGTH];            //!< registered with the LAS specification authority
    quint16 recordID;                               //!< managed by the owner of user ID
    quint64 recordLength;                           //!< size of data after VLR header
    char description[LAS_EVLR_DESCRIPTION_LENGTH];  //!< the optional description of data
};

/*!
 * EVLR Waveform Data Packets
 * User ID: LASF_Spec
 * Record ID: 65535
 * Required for point data formats 4, 5, 9, and 10.
*/

#pragma pack()


#endif // LASEVLR_H
