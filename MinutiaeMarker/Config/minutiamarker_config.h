#ifndef MINUTIAEMARKER_CONFIG_H
#define MINUTIAEMARKER_CONFIG_H

#include "MinutiaeMarker/minutiaemarker_settings.h"

#include <map>

#include <QString>


class MinutiaeMarkerConfig
{
public:
    //constructors
    MinutiaeMarkerConfig();

    static MinutiaeMarkerSettings getDefaultMinutiaeMarkerSetting();
};

#endif // MINUTIAEMARKER_CONFIG_H
