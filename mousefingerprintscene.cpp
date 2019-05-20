#include "mousefingerprintscene.h"

//constructor
MouseFingerprintScene::MouseFingerprintScene()
{
    this->point.setX(0);
    this->point.setY(0);
    this->draggingState = false;
    this->imgWidth = 0;
    this->imgHeight = 0;
}


//events
void MouseFingerprintScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "mouseDoubleClickEvent x:" << event->scenePos().x() << " y: " << event->scenePos().y();

    this->point = {static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y())};

    if (this->mode == MouseFingerprintSceneModes::MARKER) {
        this->point = getNormalizedCursorPositionInsideImage(static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y()), this->imgWidth, this->imgHeight, this->minutiaMarkerSettings->blocksize, this->minutiaMarkerSettings->blocksize);

        emit pushMinutiaSignal(Minutia(this->point, this->minutiaMarkerSettings->blocksize, this->minutiaMarkerSettings->blocksize, false));
    }
    else if (this->mode == MouseFingerprintSceneModes::CHECKER) {
        emit predictMinutiaSignal(this->point);
    }
}

void MouseFingerprintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "mouseMoveEvent x:" << event->scenePos().x() << " y: " << event->scenePos().y();

    this->point = {static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y())};

    if (this->imgWidth != 0 && this->imgHeight != 0) {
        if (this->mode == MouseFingerprintSceneModes::MARKER) {
            if (this->draggingState) {
                this->point = getNormalizedCursorPositionInsideImage(static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y()), this->imgWidth, this->imgHeight);
//                this->draggingRectangle = getNormalizedDraggingRectangleInsideImage(this->draggingRectangle.x(), this->draggingRectangle.y(), this->point.x(), this->point.y());

                this->draggingRectangle.setBottomRight(this->point);
                emit setActualPositionSignal(this->point, true, this->draggingRectangle.topLeft());
            }
            else {
                this->point = getNormalizedCursorPositionInsideImage(static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y()), this->imgWidth, this->imgHeight, this->minutiaMarkerSettings->blocksize, this->minutiaMarkerSettings->blocksize);

                emit setActualPositionSignal(this->point, false, QPoint());
            }
        }
    }
}

void MouseFingerprintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "mousePressEvent x: " << event->scenePos().x() << " y: " << event->scenePos().y();

    this->point = {static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y())};

    if (event->button() == Qt::RightButton) {
        this->draggingState = true;
        this->draggingRectangle.setTopLeft(getNormalizedCursorPositionInsideImage(static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y()), this->imgWidth, this->imgHeight));
    }
}

void MouseFingerprintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //    qDebug() << "mouseReleaseEvent x: " << event->scenePos().x() << " y: " << event->scenePos().y();

    this->point = {static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y())};

    if (this->draggingState) {
        this->point = getNormalizedCursorPositionInsideImage(static_cast<int>(event->scenePos().x()), static_cast<int>(event->scenePos().y()), this->imgWidth, this->imgHeight);

        this->draggingRectangle.setBottomRight(this->point);
        this->draggingRectangle = getNormalizedDraggingRectangleInsideImage(this->draggingRectangle.topLeft().x(), this->draggingRectangle.topLeft().y(), this->draggingRectangle.bottomRight().x(), this->draggingRectangle.bottomRight().y());
        if ((this->draggingRectangle.topLeft() - this->draggingRectangle.bottomRight()).manhattanLength() > this->MIN_DRAGGING_RECT_SIZE) {
            emit pushMinutiaSignal(Minutia(this->draggingRectangle.topLeft(), this->draggingRectangle.width(), this->draggingRectangle.height(), true));
        }

        this->draggingState = false;
        this->draggingRectangle = QRect();
    }

}

void MouseFingerprintScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && !this->draggingState) {
        emit pushMinutiaSignal(Minutia(this->point, this->minutiaMarkerSettings->blocksize, this->minutiaMarkerSettings->blocksize, false));
    }
}

/***
 * Utils
 ***/
bool MouseFingerprintScene::cursorIsInImage(int x, int y, int imgWidth, int imgHeight,  int areaWidth, int areaHeight) {
    return x >= 0 && y >= 0 && x + areaWidth < imgWidth &&  y + areaHeight < imgHeight;
}

MouseFingerprintScene::CursorPositionRelativeToImage MouseFingerprintScene::getCursorPositionRelativeToImage(int x, int y, int imgWidth, int imgHeight, int areaWidth, int areaHeight) {
    if (x < 0 && y < 0) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_TOP_LEFT";
        return CursorPositionRelativeToImage::OUTSIDE_TOP_LEFT;
    }
    else if (x >= 0 && x <= imgWidth - areaWidth && y < 0) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_TOP";
        return CursorPositionRelativeToImage::OUTSIDE_TOP;
    }
    else if (x > imgWidth - areaWidth && y < 0) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_TOP_RIGHT";
        return CursorPositionRelativeToImage::OUTSIDE_TOP_RIGHT;
    }
    else if (x > imgWidth - areaWidth && y >= 0 && y <= imgHeight) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_RIGHT";
        return CursorPositionRelativeToImage::OUTSIDE_RIGHT;
    }
    else if (x > imgWidth - areaWidth && y > imgHeight - areaHeight) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_BOTTOM_RIGHT";
        return CursorPositionRelativeToImage::OUTSIDE_BOTTOM_RIGHT;
    }
    else if (x >= 0 && x <= imgWidth - areaWidth && y > imgHeight - areaHeight) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_BOTTOM";
        return CursorPositionRelativeToImage::OUTSIDE_BOTTOM;
    }
    else if (x < 0 && y > imgHeight - areaHeight) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_BOTTOM_LEFT";
        return CursorPositionRelativeToImage::OUTSIDE_BOTTOM_LEFT;
    }
    else if (x < 0 && y >= 0 && y <= imgHeight - areaHeight) {
//        qDebug() << "CursorPositionRelativeToImage::OUTSIDE_LEFT";
        return CursorPositionRelativeToImage::OUTSIDE_LEFT;
    }

//qDebug() << "CursorPositionRelativeToImage::INSIDE";
    return CursorPositionRelativeToImage::INSIDE;
}

QPoint MouseFingerprintScene::getNormalizedCursorPositionInsideImage(int x, int y, int imgWidth, int imgHeight, int areaWidth, int areaHeight)
{
    CursorPositionRelativeToImage cursorPos;
    QPoint qPointToEmit;

    cursorPos = getCursorPositionRelativeToImage(x, y, imgWidth - areaWidth, imgHeight - areaHeight, areaWidth, areaHeight);

    if (cursorPos == CursorPositionRelativeToImage::INSIDE) {
        qPointToEmit = QPoint(x, y);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_TOP_LEFT) {
        qPointToEmit = QPoint(0, 0);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_TOP) {
        qPointToEmit = QPoint(x, 0);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_TOP_RIGHT) {
        qPointToEmit = QPoint(imgWidth - areaWidth, 0);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_RIGHT) {
        qPointToEmit = QPoint(imgWidth - areaWidth, y);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_BOTTOM_RIGHT) {
        qPointToEmit = QPoint(imgWidth - areaWidth, imgHeight - areaHeight);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_BOTTOM) {
        qPointToEmit = QPoint(x, imgHeight - areaHeight);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_BOTTOM_LEFT) {
        qPointToEmit = QPoint(0, imgHeight - areaHeight);
    }
    else if (cursorPos == CursorPositionRelativeToImage::OUTSIDE_LEFT) {
        qPointToEmit = QPoint(0, y);
    }

    return qPointToEmit;
}

QRect MouseFingerprintScene::getNormalizedDraggingRectangleInsideImage(int x1, int y1, int x2, int y2)
{
    QRect qRectToReturn;

    qRectToReturn.setTopLeft(QPoint(qMin(x1, x2), qMin(y1, y2)));
    qRectToReturn.setWidth(static_cast<int>(qAbs(x1 - x2)));
    qRectToReturn.setHeight(static_cast<int>(qAbs(y1 - y2)));

    return qRectToReturn;
}

/***
 * Getters and setters
 ***/
void MouseFingerprintScene::setMode(const MouseFingerprintSceneModes &value)
{
    this->mode = value;
}

void MouseFingerprintScene::setMinutiaMarkerSettings(MinutiaeMarkerSettings *value)
{
    minutiaMarkerSettings = value;
}

Image MouseFingerprintScene::getImage() const
{
    return image;
}

void MouseFingerprintScene::setImage(const Image &value)
{
    image = value;
}

void MouseFingerprintScene::setImgWidth(int value)
{
    imgWidth = value;
}

void MouseFingerprintScene::setImgHeight(int value)
{
    imgHeight = value;
}
