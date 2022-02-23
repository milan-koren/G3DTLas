#ifndef LASPOINTCLASSIFICATION_H
#define LASPOINTCLASSIFICATION_H

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file laspointclassification.h
 *
 * \brief Standard LAS point classification.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtlas_global.h"


/*!
 * \brief The LasDataTypes enumeration by LAS standard.
 */
enum LasPointClassification
{
    NEVER_CLASSIFIED = 0,
    UNCLASSIFIED = 1,
    GROUND = 2,
    LOW_VEGETATION = 3,
    MEDIUM_VEGETATION = 4,
    HIGH_VEGETATION = 5,
    BUILDING = 6,
    LOW_NOISE = 7,
    MODEL_KEY = 8,
    WATER = 9,
    RAIL = 10,
    ROAD_SURFACE = 11,
    OVERLAP = 12,
    WIRE_GUARD = 13,
    WIRE_CONDUCTOR = 14,
    TRANSMISSION_TOWER = 15,
    WIRE_CONNECTOR = 16,
    BRIDGE_DECK = 17,
    HIGH_NOISE = 18,
};

#endif // LASPOINTCLASSIFICATION_H
