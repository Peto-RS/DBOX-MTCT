#include "image.h"

Image::Image()
{

}

Image::Image(QImage img, QString imgName)
{
    this->img = img;
    this->imgName = imgName;
}

Image::Image(QImage img, QString imgName, QString imgPath)
{
    this->img = img;
    this->imgName = imgName;
    this->imgPath = imgPath;
}

QImage Image::getImg() const
{
    return img;
}

void Image::setImg(const QImage &value)
{
    img = value;
}

QString Image::getImgName() const
{
    return imgName;
}

void Image::setImgName(const QString &value)
{
    imgName = value;
}

QString Image::getImgPath() const
{
    return imgPath;
}

void Image::setImgPath(const QString &value)
{
    imgPath = value;
}
