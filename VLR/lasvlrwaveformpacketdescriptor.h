#ifndef LASVLRWAVEFORMPACKETDESCRIPTOR_H
#define LASVLRWAVEFORMPACKETDESCRIPTOR_H

#include <QtCore>
#include "g3dtlas_global.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 *
 * \brief Waveform Packet Descriptor. Optional VLR defined by LAS Specification.
 *
 * Waveform Packet Descriptor
 * User ID: LASF_Spec
 * Record ID: 100 <= n <= 354 (i.e. 255 waveform packet descriptions)
 * Reguired for point data formats 4, 5, 9, and 10.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#pragma pack(1)

/*!
 * \brief Waveform Packet Descriptor VLR.
 * \remark size = 26
 */
struct LasVLRPointWaveformPacketDescriptor
{
    quint8 bitsPerSample;               //!< 2-32 bits
    quint8 compressionType;             //!< 0: no compression, reserved for future use
    quint32 numberOfSamples;            //!< number of samples
    quint32 temporalSamplesSpacing;     //!< picoseconds (MHz); 500 = 500 MHz
    double digitizerGain;               //!< volts = digitizingOffset + digitizingGain * waveformAmplitude
    double digitizerOffset;
};

#pragma pack()

#endif // LASVLRWAVEFORMPACKETDESCRIPTOR_H
