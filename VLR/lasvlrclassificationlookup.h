#ifndef LASVLRCLASSIFICATIONLOOKUP_H
#define LASVLRCLASSIFICATIONLOOKUP_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief LASF classification lookup. Optional VLR defined by LAS Specification.
 *
 * Classification Lookup
 * User ID: LASF_Spec
 * Record ID: 0
 * size = 256 records * 16 bytes per record
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

/*!
 * \brief Classification entry of the classification lookup VLR.
 * \remark size = 16
 * \sa LasVLR
 */
struct LasVLRClassificationLookupEntry
{
    quint8 classNumber;
    char Description[15];
};

#pragma pack()

#endif // LASVLRCLASSIFICATIONLOOKUP_H
