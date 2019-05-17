#include "minutiaemarker_settings.h"

MinutiaeMarkerSettings::MinutiaeMarkerSettings()
{
    this->selectedMinutiaType = DboxMTCTConfig::Minutiae["nothing"];
}

void MinutiaeMarkerSettings::printToConsole()
{
    qDebug() << "Class: MinutiaeMarkerSettings\n";
    qDebug() << "__________\n";
    qDebug() << "blocksize: " << this->blocksize << "\n";
    qDebug() << "additionalBlocks: " << this->additionalBlocks << "\n";
    qDebug() << "selectedMinutiaType: " << QString::fromStdString(this->selectedMinutiaType.getId()) << "\n";
    qDebug() << "useRotation: " << this->useRotation << "\n";
    qDebug() << "useBlur: " << this->useBlur << "\n";
    qDebug() << "blurValue: " << this->blurValue << "\n";
    qDebug() << "useMirroring: " << this->useMirroring << "\n";
    qDebug() << "useIrisBlur: " << this->useIrisBlur << "\n";
    qDebug() << "irisBlurValue: " << this->irisBlurValue << "\n";
    qDebug() << "irisBlurRadius: " << this->irisBlurRadius << "\n";
    qDebug() << "inputPath: " << this->inputPath << "\n";
    qDebug() << "outputPath: " << this->outputPath << "\n";
    qDebug() << "outputFormat: " << this->outputFormat << "\n";
    qDebug() << "useSameSizeForImages: " << this->useSameSizeForImages << "\n";
}
