#include "lasfileheader.h"

/*!
 * *****************************************************************
 *                               G3DTLas
 * *****************************************************************
 * \file lasfileheader.cpp
 *
 * \brief The implemenation of the LasFileHeader14 class.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


/*!
 * \brief Default constructor.
 */
LasFileHeader14::LasFileHeader14()
{
    setNull();
}


/*!
 * \brief Clear header.
 */
void LasFileHeader14::setNull()
{
    memset(reinterpret_cast<void*>(this), 0, sizeof(LasFileHeader14));
}


/*!
 * \brief Reads header from a file. Copy data from the old fields to ensure backward compatibility.
 * \param file Reference to open las-file.
 * \return True, if header was sucessfully read.
 */
bool LasFileHeader14::read(QFile &file)
{
    bool error = true;

    setNull();
    if (file.seek(0))
        if (file.read(reinterpret_cast<char *>(this), sizeof(LasFileHeader11)) == sizeof(LasFileHeader11))
            if (getFileSignature() == "LASF")
                if (this->versionMajor == 1 && 1 <= this->versionMinor && this->versionMinor <= 4)
                    if (file.seek(0))
                    {
                        switch (this->versionMinor)
                        {
                            case 3:
                            error = (file.read(reinterpret_cast<char *>(this), sizeof(LasFileHeader13)) != sizeof(LasFileHeader13));
                                break;
                            case 4:
                                error = (file.read(reinterpret_cast<char *>(this), sizeof(LasFileHeader14)) != sizeof(LasFileHeader14));
                                break;
                            default:
                                error = false;
                                break;
                        }

                        if (!error && this->versionMinor < 4)
                        {
                            // copy data from the legacy fields (backward compatibility)
                            if (0 < this->legacy_number_of_points && this->legacy_number_of_points != this->number_of_points) this->number_of_points = this->legacy_number_of_points;
                            for(quint32 i = 0; i < 5; i++)
                            {
                                if (0 < this->legacy_number_of_points_by_return[i]) this->number_of_points_by_return[i] = this->legacy_number_of_points_by_return[i];
                            }
                        }                       
                    }

    if (error) setNull();
    return !error;
}


/*!
 * \brief Gets file signature.
 * \return File signature.
 */
QString LasFileHeader14::getFileSignature()
{
    return charToQString(this->fileSignature, LAS11_FILE_SIGNATURE_LENGTH);
}


/*!
 * \brief Gets the name of a LIDAR sensor (scanner) or data processing procedure.
 * \return System ID.
 */
QString LasFileHeader14::getSystemID()
{
    return  charToQString(this->systemID, LAS11_SYSTEMID_LENGTH);
}


/*!
 * \brief Gets the name of generating software.
 * \return Name of generating software.
 */
QString LasFileHeader14::getGeneratingSoftware()
{
    return charToQString(this->generatingSoftware, LAS11_GENERATING_SOFTWARE_LENGTH);
}


/*!
 * \brief Sets the standard las-file signature.
 */
void LasFileHeader14::setFileSignature()
{
    qstringToChar(LAS11_FILE_SIGNATURE, this->fileSignature, LAS11_FILE_SIGNATURE_LENGTH);
}


/*!
 * \brief Sets the name of a generating software.
 * \param Software name.
 */
void LasFileHeader14::setGeneratingSoftware(QString softwareName)
{
    qstringToChar(softwareName, this->generatingSoftware, LAS11_GENERATING_SOFTWARE_LENGTH);
}


/*!
 * \brief Sets the name of a LIDAR sensor (scanner) or data processing procedure.
 * \param System name.
 */
void LasFileHeader14::setSystemID(QString systemName)
{
    qstringToChar(systemName, this->systemID, LAS11_SYSTEMID_LENGTH);
}


/*!
 * \brief Reads a field value.
 * \param field Pointer to a char array.
 * \param fieldLength Array length.
 * \return Field value.
 */
QString LasFileHeader14::charToQString(char *field, qint16 fieldLength)
{
    QString str = "";

    str = QString::fromLocal8Bit(field, fieldLength).trimmed();

    return str;
}


/*!
 * \brief Write string to a field.
 * \param str Input string.
 * \param field Pointer to a char array.
 * \param fieldLength Maximal field length.
 * \remark In accordance to standard, unused field chars are set to 0.
 */
void LasFileHeader14::qstringToChar(QString str, char *field, qint16 fieldLength)
{
    QByteArray b;

    if (field != nullptr && 0 < fieldLength)
    {
        memset(field, 0, size_t(fieldLength));
        if (str.length() < fieldLength) fieldLength = qint16(str.length());
        b = str.toLocal8Bit();
        memcpy(field, b.data(), size_t(fieldLength));
    }
}
