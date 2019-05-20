#ifndef MINUTIA_H
#define MINUTIA_H

#include <Config/minutia_config.h>

#include "map"
#include <string>

#include <QMetaType>
#include <QPoint>
#include <QString>

class Minutia
{
private:
    QPoint coordinates;
    int width;
    int height;
    std::string imgPath;
    MinutiaConfig type;
    bool createdInDragAndDropMode;

public:
    //constructors
    Minutia();
    Minutia(QPoint);
    Minutia(QPoint, int, int, bool);
    Minutia(QPoint, int, int, std::string, MinutiaConfig);

    static Minutia fromTextFile(std::map<std::string, std::string>);
    std::string toTextFile();

    //getters and setters
    QPoint getCoordinates() const;
    void setCoordinates(const QPoint &value);
    int getWidth() const;
    void setWidth(int value);
    int getHeight() const;
    void setHeight(int value);
    std::string getImgPath() const;
    void setImgPath(const std::string &value);
    MinutiaConfig getType() const;
    void setType(const MinutiaConfig &value);
    bool getCreatedInDragAndDropMode() const;
    void setCreatedInDragAndDropMode(bool value);
};

#endif // MINUTIA_H
