#ifndef LASVLRHEADER_H
#define LASVLRHEADER_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasvlrheader.h
 *
 * \brief Header of variable-length record.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"

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
    char reserved[LAS_VLR_RESERVED_LENGTH];         //!< set to zero
    char userID[LAS_VLR_USERID_LENGTH];             //!< registered with the LAS specification authority
    quint16 recordID;                               //!< managed by the owner of user ID
    quint16 recordLength;                           //!< size of data after VLR header
    char description[LAS_VLR_DESCRIPTION_LENGTH];   //!< the optional description of data
};

#pragma pack()

#endif // LASVLRHEADER_H
