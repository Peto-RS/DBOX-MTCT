#ifndef MOUSEFINGERPRINTSCENE_H
#define MOUSEFINGERPRINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QRect>
#include <QtMath>

#include "image.h"
#include <MinutiaeMarker/minutia.h>
#include <MinutiaeMarker/minutiaemarker_settings.h>

///
/// \brief The MouseFingerprintScene class
/// This class function is emitting mouse and keyboard actions
class MouseFingerprintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ///
    /// \brief MouseFingerprintScene
    /// Default constructor
    MouseFingerprintScene();

    enum class MouseFingerprintSceneModes {CHECKER, CHECKER_HEATMAP, MARKER, TRAINER};
    enum class CursorPositionRelativeToImage
    {
        INSIDE,
        OUTSIDE_TOP, OUTSIDE_RIGHT, OUTSIDE_BOTTOM, OUTSIDE_LEFT,
        OUTSIDE_TOP_RIGHT, OUTSIDE_TOP_LEFT, OUTSIDE_BOTTOM_RIGHT, OUTSIDE_BOTTOM_LEFT
    };

    void setMode(const MouseFingerprintSceneModes &value);

    //utils
    bool cursorIsInImage(int, int, int, int, int areaWidth = 0, int areaHeight = 0);
    CursorPositionRelativeToImage getCursorPositionRelativeToImage(int, int, int, int, int areaWidth = 0, int areaHeight = 0);
    QPoint getNormalizedCursorPositionInsideImage(int, int, int, int, int areaWidth = 0, int areaHeight = 0);
    QRect getNormalizedDraggingRectangleInsideImage(int, int, int, int);

    /***
     * Minutiae marker
     ***/
    //Getters and setters
    void setMinutiaMarkerSettings(MinutiaeMarkerSettings *value);

    Image getImage() const;
    void setImage(const Image &value);

    void setImgWidth(int value);
    void setImgHeight(int value);

private:
    //constants
    const int MIN_DRAGGING_RECT_SIZE = 15;
    MouseFingerprintSceneModes mode;

    //store current cursor position on scene
    bool draggingState;
    QRect draggingRectangle;
    QPoint point;

    Image image;
    int imgWidth;
    int imgHeight;

    /***
     * Minutiae marker
     ***/
    MinutiaeMarkerSettings *minutiaMarkerSettings;

signals:
    void pushMinutiaSignal(Minutia minutia);
    void predictMinutiaSignal(QPoint point);
    void setActualPositionSignal(QPoint, bool, QPoint);

protected:  
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
};

#endif // MOUSEFINGERPRINTSCENE_H
