#ifndef MINUTIAEMARKER_FILESERIALIZER_H
#define MINUTIAEMARKER_FILESERIALIZER_H

#include "MinutiaeMarker/minutia.h"
#include "MinutiaeMarker/minutiaemarker_settings.h"

#include <fstream>

class MinutiaeMarker_FileSerializer
{
public:
    MinutiaeMarker_FileSerializer();

    static void writeFileToDisk(std::ofstream &file, MinutiaeMarkerSettings settings, QMap<QString, QVector<Minutia>> images);
    static std::tuple<MinutiaeMarkerSettings, QMap<QString, QVector<Minutia> > > loadFromFile(std::ifstream &file);
};

#endif // MINUTIAEMARKER_FILESERIALIZER_H
