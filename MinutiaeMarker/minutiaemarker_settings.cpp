#include "minutiaemarker_settings.h"

#include <algorithm>

bool MinutiaeMarkerSettings::stringToBool(std::string text) {
    if (text.compare("1") == 0) {
        return true;
    }

    return false;
}

static std::string doubleToString(std::string s) {
    std::replace(s.begin(), s.end(), ',', '.');

    return s;
}

MinutiaeMarkerSettings::MinutiaeMarkerSettings()
{
    this->selectedMinutiaType = DboxMTCTConfig::Minutiae["nothing"];
}

MinutiaeMarkerSettings MinutiaeMarkerSettings::fromTextFile(std::map<std::string, std::string> params)
{
    MinutiaeMarkerSettings m;

    m.blocksize = params.find("blocksize") != params.end() ? std::stoi(params["blocksize"]) : 0;
    m.selectedMinutiaType = params.find("selectedMinutiaType") != params.end() ? DboxMTCTConfig::Minutiae[params["selectedMinutiaType"]] : DboxMTCTConfig::Minutiae["nothing"];
    m.useRotation = params.find("useRotation") != params.end() ? stringToBool(params["useRotation"]) : false;
    m.useBlur = params.find("useBlur") != params.end() ? stringToBool(params["useBlur"]) : false;
    m.blurValue = params.find("blurValue") != params.end() ? std::stod(params["blurValue"]) : 0;
    m.useMirroring = params.find("useMirroring") != params.end() ? stringToBool(params["useMirroring"]) : false;
    m.useIrisBlur = params.find("useIrisBlur") != params.end() ? stringToBool(params["useIrisBlur"]) : false;
    m.irisBlurValue = params.find("irisBlurValue") != params.end() ? std::stod(params["irisBlurValue"]) : 0;
    m.irisBlurRadius = params.find("irisBlurRadius") != params.end() ? std::stod(params["irisBlurRadius"]) : 0;
    m.inputPath = params.find("inputPath") != params.end() ? QString::fromStdString(params["inputPath"]) : "";
    m.outputPath = params.find("outputPath") != params.end() ? QString::fromStdString(params["outputPath"]) : "";
    m.useSameSizeForImages = params.find("useSameSizeForImages") != params.end() ? stringToBool(params["useSameSizeForImages"]) : false;

    return m;
}

std::string MinutiaeMarkerSettings::toTextFile()
{
    return
            "blocksize=" + std::to_string(this->blocksize) + "\n" +
            "selectedMinutiaType=" + this->selectedMinutiaType.getId() + "\n" +
            "useRotation=" + std::to_string(this->useRotation) + "\n" +
            "useBlur=" + std::to_string(this->useBlur) + "\n" +
            "blurValue=" + doubleToString(std::to_string(this->blurValue)) + "\n" +
            "useMirroring=" + std::to_string(this->useMirroring) + "\n" +
            "useIrisBlur=" + std::to_string(this->useIrisBlur) + "\n" +
            "irisBlurValue=" + doubleToString(std::to_string(this->irisBlurValue)) + "\n" +
            "irisBlurRadius=" + doubleToString(std::to_string(this->irisBlurRadius)) + "\n" +
            "inputPath=" + this->inputPath.toStdString() + "\n" +
            "outputPath=" + this->outputPath.toStdString() + "\n" +
            "useSameSizeForImages=" + std::to_string(this->useSameSizeForImages) + "\n";
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
