#include "lasvlr.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasvlr.cpp
 *
 * \brief The implemenation of the LasVLR and support classes.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */



/*!
 * *****************************************************************
 * LasGeoKeys
 * *****************************************************************
*/

/*!
 * \brief Default destructor.
 */
LasGeoKeys::~LasGeoKeys()
{
    destroy();
}

/*!
 * \brief Release key entries and set all properties to zero.
 */
void LasGeoKeys::destroy()
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


/*!
 * *****************************************************************
 * LasVLR
 * *****************************************************************
*/

/*!
 * \brief Default class constructor.
 */
LasVLR::LasVLR()
{
}

/*!
 * \brief Copy constructor.
 * \param vlr Source CVLR object.
 */
LasVLR::LasVLR(LasVLR &vlr)
{
    copyFrom(vlr);
}

/*!
 * \brief Virtual destructor. Calls destroy() to realise allocated resources.
 */
LasVLR::~LasVLR()
{
    destroy();
}

/*!
 * \brief Copy operator.
 * \param vrl Source VRL object.
 * \return
 */
LasVLR &LasVLR::operator=(LasVLR &vlr)
{
    copyFrom(vlr);
    return *this;
}

/*!
 * \brief Releases allocated memory.
 */
void LasVLR::destroy()
{
    if (this->data != nullptr)
    {
        delete [] this->data;
        this->data = nullptr;
    }
    memset(&this->header, 0, sizeof (LasVLRHeader));
}

/*!
 * \brief Creates the deep copy of a source VLR.
 * \param vrl Source VRL object.
 */
void LasVLR::copyFrom(LasVLR &vlr)
{
    destroy();
    memcpy(reinterpret_cast<char*>(&this->header), reinterpret_cast<char*>(&vlr.header), sizeof (LasVLRHeader));
    this->data = new char[this->header.recordLength];
    memcpy(this->data, vlr.data, this->header.recordLength);
}
