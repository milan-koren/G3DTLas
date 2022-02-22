#include "lasvlrgeokeys.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief The implemenation of the LasVLRGeoKeys class.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


/*!
 * \brief Default destructor.
 */
LasVLRGeoKeys::~LasVLRGeoKeys()
{
    destroy();
}


/*!
 * \brief Release key entries and set all properties to zero.
 */
void LasVLRGeoKeys::destroy()
{
    this->keyDirectoryVersion = 0;
    this->keyRevision = 0;
    this->minorRevision = 0;
    if (this->keys != nullptr)
    {
        delete [] this->keys;
        this->keys = nullptr;
    }
    this->numberOfKeys = 0;
}
