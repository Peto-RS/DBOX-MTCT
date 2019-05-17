#ifndef MINUTIAEMARKER_SETTINGS_H
#define MINUTIAEMARKER_SETTINGS_H

#include "Config/dbox_mtct_config.h"
#include "Config/minutia_config.h"
#include "MinutiaeMarker/Config/minutiamarker_config.h"

#include <QDebug>
#include <QString>

///
/// \brief The MinutiaeMarkerSettings class
/// This class stores all the values from user interface on the Minutiae Marker tab
class MinutiaeMarkerSettings
{
public:
    //variables
    int blocksize;
    int additionalBlocks;
    MinutiaConfig selectedMinutiaType;
    bool useRotation;
    bool useBlur;
    double blurValue;
    bool useMirroring;
    bool useIrisBlur;
    double irisBlurValue;
    double irisBlurRadius;
    QString inputPath;
    QString outputPath;
    QString outputFormat;
    bool useSameSizeForImages;

    //constructors
    MinutiaeMarkerSettings();

    //methods
    void printToConsole();
};

#endif // MINUTIAEMARKER_SETTINGS_H
