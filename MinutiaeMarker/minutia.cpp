#include "minutia.h"

#include "Config/dbox_mtct_config.h"

#include <iostream>

bool stringToBool(std::string text) {
    if (text.compare("1") == 0) {
        return true;
    }

    return false;
}

//constructors
Minutia::Minutia() {
    this->createdInDragAndDropMode = false;
}

Minutia::Minutia(QPoint coordinates)
{
    this->coordinates = coordinates;
    this->createdInDragAndDropMode = false;
}

Minutia::Minutia(QPoint coordinates, int width, int height, bool createdInDragAndDropMode)
{
    this->coordinates = coordinates;
    this->width = width;
    this->height = height;
    this->createdInDragAndDropMode = createdInDragAndDropMode;
}

Minutia::Minutia(QPoint coordinates, int width, int height, std::string imgPath, MinutiaConfig selectedMinutiaType)
{
    this->coordinates = coordinates;
    this->width = width;
    this->height = height;
    this->imgPath = imgPath;
    this->type = selectedMinutiaType;

    this->createdInDragAndDropMode = false;
}

Minutia Minutia::fromTextFile(std::map<std::string, std::string> params)
{
    Minutia m;

    m.type = params.find("type") != params.end() ? DboxMTCTConfig::Minutiae[params["type"]] : DboxMTCTConfig::Minutiae["nothing"];
    m.coordinates = {params.find("x") != params.end() ? std::stoi(params["x"]) : 0, params.find("y") != params.end() ? std::stoi(params["y"]) : 0};
    m.width = params.find("width") != params.end() ? std::stoi(params["width"]) : 19;
    m.height = params.find("height") != params.end() ? std::stoi(params["height"]) : 19;
    m.createdInDragAndDropMode = params.find("createdInDragAndDropMode") != params.end() ? stringToBool(params["createdInDragAndDropMode"]) : false;

    return m;
}

std::string Minutia::toTextFile()
{
    return "type=" + this->type.getId() + ";" +
           "x=" + std::to_string(this->getCoordinates().x()) + ";" +
           "y=" + std::to_string(this->getCoordinates().y()) + ";" +
           "width=" + std::to_string(this->getWidth()) + ";" +
           "height=" + std::to_string(this->getHeight()) + ";" +
           "createdInDragAndDropMode=" + std::to_string(this->createdInDragAndDropMode) + ";";
}

//getters and setters
QPoint Minutia::getCoordinates() const
{
    return coordinates;
}

void Minutia::setCoordinates(const QPoint &value)
{
    coordinates = value;
}

int Minutia::getWidth() const
{
    return width;
}

void Minutia::setWidth(int value)
{
    width = value;
}

int Minutia::getHeight() const
{
    return height;
}

void Minutia::setHeight(int value)
{
    height = value;
}

std::string Minutia::getImgPath() const
{
    return imgPath;
}

void Minutia::setImgPath(const std::string &value)
{
    imgPath = value;
}

MinutiaConfig Minutia::getType() const
{
    return type;
}

void Minutia::setType(const MinutiaConfig &value)
{
    type = value;
}

bool Minutia::getCreatedInDragAndDropMode() const
{
    return createdInDragAndDropMode;
}

void Minutia::setCreatedInDragAndDropMode(bool value)
{
    createdInDragAndDropMode = value;
}
