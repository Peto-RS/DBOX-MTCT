#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>

///
/// \brief The Image class
/// Class to store basic image entity in the application
class Image
{
public:
    ///
    /// \brief Image
    /// Default constructor
    Image();
    Image(QImage, QString);
    Image(QImage, QString, QString);

    QImage getImg() const;
    void setImg(const QImage &value);
    QString getImgName() const;
    void setImgName(const QString &value);
    QString getImgPath() const;
    void setImgPath(const QString &value);

private:
    //variables
    QImage img;
    QString imgName;
    QString imgPath;
};

#endif // IMAGE_H
