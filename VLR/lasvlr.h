#ifndef LASVLR_H
#define LASVLR_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasvlr.h
 *
 * \brief Variable-length record.
 * \remark Main LasVLR class.
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

#include "g3dtlas_global.h"
#include "lasvlrheader.h"
#include "lasvlrgeokeyentry.h"
#include "lasvlrgeokeys.h"
#include "lasvlrclassificationlookup.h"
#include "lasvlrtextarea.h"
#include "lasvlrpointextrabytes.h"
#include "lasvlrsuperseded.h"
#include "lasvlrwaveformpacketdescriptor.h"


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
