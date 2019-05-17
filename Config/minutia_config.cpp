#include "minutia_config.h"

//constructors
std::string MinutiaConfig::getIconPath() const
{
    return iconPath;
}

void MinutiaConfig::setIconPath(const std::string &value)
{
    iconPath = value;
}

MinutiaConfig::MinutiaConfig() {}

MinutiaConfig::MinutiaConfig(std::string id, bool isActive, std::string name)
{
    this->id = id;
    this->isActive = isActive;
    this->name = name;
    this->colorHexCode = "#FFFFFF";
}

MinutiaConfig::MinutiaConfig(std::string id, bool isActive, std::string name, std::string colorHexCode, std::string iconPath)
{
    this->id = id;
    this->isActive = isActive;
    this->name = name;
    this->colorHexCode = colorHexCode;
    this->iconPath = iconPath;
}

//getters and setters
std::string MinutiaConfig::getId() const
{
    return id;
}

void MinutiaConfig::setId(const std::string &value)
{
    id = value;
}

bool MinutiaConfig::getIsActive() const
{
    return isActive;
}

void MinutiaConfig::setIsActive(bool value)
{
    isActive = value;
}

std::string MinutiaConfig::getName() const
{
    return name;
}

void MinutiaConfig::setName(const std::string &value)
{
    name = value;
}

std::string MinutiaConfig::getColorHexCode() const
{
    return colorHexCode;
}

void MinutiaConfig::setColorHexCode(const std::string &value)
{
    colorHexCode = value;
}
