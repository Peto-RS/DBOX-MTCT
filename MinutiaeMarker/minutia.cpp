#include "minutia.h"

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
