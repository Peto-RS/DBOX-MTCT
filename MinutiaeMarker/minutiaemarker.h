#ifndef MINUTIAEMARKER_H
#define MINUTIAEMARKER_H

#include "Utils/minutiaemarker_dataaugmentationutils.h"

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QDir>
#include <QThread>

#include <vector>

#include "mousefingerprintscene.h"
#include "opencv2/opencv.hpp"

#include "minutia.h"
#include "minutiaemarker_settings.h"

///
/// \brief The MinutiaeMarker class
/// This class stores all the data regarding to the Minutiae Marker tab in the application. It runs in the separate thread.
class MinutiaeMarker : public QThread
{
    Q_OBJECT

private:
    //utils
    MinutiaeMarker_DataAugmentationUtils dataAugmentationUtils;

    //variables
    MinutiaeMarkerSettings *settings;

    QMap<QString, QVector<Minutia>> images;
    QVector<Minutia> minutiae;

    void run();

    int countOutputFiles();

public:
    //constructors
    MinutiaeMarker();

    QVector<Minutia> getMinutiae() const;
    void setMinutiae(const QVector<Minutia> &value);

    QMap<QString, QVector<Minutia>> getImages() const;
    void insertImage(QString imgName, QVector<Minutia> minutiae);
    void removeMinutia(int lineNum);
    void removeAllBlocks();

    void generateBlocks();

    MinutiaeMarkerSettings *getSettings() const;
    void setSettings(MinutiaeMarkerSettings *value);

private slots:
    void pushMinutia(Minutia);
    void updataMinutiae(QString prevImgName, QString imgName);

signals:
    void updateProgressBarSignal(QString barName, int value, QString text = "");
    void updateMinutiaeMarkerSceneSignal(QString action);
    void blocksSaved();
};

#endif // MINUTIAEMARKER_H
