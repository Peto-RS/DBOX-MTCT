#ifndef MINUTIA_CONFIG_H
#define MINUTIA_CONFIG_H

#include <string>

class MinutiaConfig
{
private:
    std::string id;
    bool isActive;
    std::string name;
    std::string colorHexCode;
    std::string iconPath;
public:
    //constructors
    MinutiaConfig();
    MinutiaConfig(std::string id, bool isActive, std::string name);
    MinutiaConfig(std::string id, bool isActive, std::string name, std::string colorHexCode, std::string iconPath);

    //getters and setters
    std::string getId() const;
    void setId(const std::string &value);
    bool getIsActive() const;
    void setIsActive(bool value);
    std::string getName() const;
    void setName(const std::string &value);
    std::string getColorHexCode() const;
    void setColorHexCode(const std::string &value);
    std::string getIconPath() const;
    void setIconPath(const std::string &value);
};

#endif // MINUTIA_CONFIG_H
