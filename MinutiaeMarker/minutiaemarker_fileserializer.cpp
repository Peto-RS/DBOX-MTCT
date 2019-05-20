#include "minutiaemarker_fileserializer.h"

#include <fstream>
#include <vector>

MinutiaeMarker_FileSerializer::MinutiaeMarker_FileSerializer()
{

}

void MinutiaeMarker_FileSerializer::writeFileToDisk(std::ofstream &file, MinutiaeMarkerSettings settings, QMap<QString, QVector<Minutia> > images)
{
    //Global config
    file << "GLOBAL_CONFIG" << std::endl;
    file << settings.toTextFile();

    //Minutiae list
    file << "MINUTIAE_LIST" << std::endl;
    for (auto img = images.begin(); img != images.end(); img++) {
        for (auto block : img.value()) {
            file << "id=" << img.key().toStdString() << ";" << block.toTextFile() << std::endl;
        }
    }
}

std::tuple<MinutiaeMarkerSettings, QMap<QString, QVector<Minutia>>> MinutiaeMarker_FileSerializer::loadFromFile(std::ifstream &file)
{
    std::map<std::string, std::string> paramsGlobal;
    std::map<std::string, std::vector<std::map<std::string, std::string>>> paramsMinutiae;

    std::string line = "";
    std::string MODE = "";

    while (std::getline (file, line))
    {
        if (line == "GLOBAL_CONFIG") {
            MODE = "GLOBAL_CONFIG";
            continue;
        }
        else if (line == "MINUTIAE_LIST") {
            MODE = "MINUTIAE_LIST";
            continue;
        }


        if (MODE == "GLOBAL_CONFIG") {
            QStringList list = QString::fromStdString(line).split('=');
            paramsGlobal[list[0].toStdString()] = list[1].toStdString();
        }
        else if (MODE == "MINUTIAE_LIST") {
            QStringList list = QString::fromStdString(line).split(';');

            QStringList imgNameSplit = list[0].split('=');
            std::string imgName = imgNameSplit[1].toStdString();

            std::map<std::string, std::string> p;
            for (int i = 1; i < list.length() - 1; i++) {
                QStringList split = list[i].split('=');

                p[split[0].toStdString()] = split[1].toStdString();
            }

            paramsMinutiae[imgName].push_back(p);
        }
    }

    std::tuple<MinutiaeMarkerSettings, QMap<QString, QVector<Minutia>>> tupleToReturn;

    QMap<QString, QVector<Minutia>> images;

    for (auto img = paramsMinutiae.begin(); img != paramsMinutiae.end(); img++) {
        for (auto it: img->second) {
            images[QString::fromStdString(img->first)].append(Minutia::fromTextFile(it));
        }
    }


    std::get<0>(tupleToReturn) = MinutiaeMarkerSettings::fromTextFile(paramsGlobal);
    std::get<1>(tupleToReturn) = images;

    return tupleToReturn;
}
