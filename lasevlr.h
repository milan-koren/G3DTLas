#ifndef LASEVLR_H
#define LASEVLR_H

#include <QtCore>
#include "g3dtlas_global.h"


/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasevl.h
 *
 * \brief Extended variable-length record.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

/*!
 * \brief Header of EVLR record.
 * \remark size = 60
 */
struct LasEVLRHeader
{
    char reserved[2];       // set to zero
    char userID[16];        // registered with the LAS specification authority
    quint16 recordID;       // managed by the owner of user ID
    quint64 recordLength;   // size of data after VLR header
    char description[32];   // the optional description of data
};



/*!
 * EVLR Waveform Data Packets
 * User ID: LASF_Spec
 * Record ID: 65535
 * Required for point data formats 4, 5, 9, and 10.
*/

#pragma pack()


#endif // LASEVLR_H
