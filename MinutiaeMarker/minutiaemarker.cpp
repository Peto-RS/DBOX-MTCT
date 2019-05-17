#include "minutiaemarker.h"

MinutiaeMarker::MinutiaeMarker()
{
    this->setObjectName("marker");

    this->settings = new MinutiaeMarkerSettings();
    this->settings->outputPath = QDir::currentPath();
}

void MinutiaeMarker::run()
{
    exec();
}

void MinutiaeMarker::removeMinutia(int lineNum)
{
    if (lineNum < this->minutiae.size()) this->minutiae.removeAt(lineNum);
}

void MinutiaeMarker::removeAllBlocks()
{
    this->images.clear();
    this->minutiae.clear();
}

void MinutiaeMarker::pushMinutia(Minutia minutia)
{
    minutia.setType(this->settings->selectedMinutiaType);

    this->minutiae.push_back(minutia);

    emit updateMinutiaeMarkerSceneSignal("add");
}

void MinutiaeMarker::insertImage(QString imgName, QVector<Minutia> minutiae)
{
    this->images.insert(imgName, minutiae);
}

QMap<QString, QVector<Minutia>> MinutiaeMarker::getImages() const
{
    return images;
}

void MinutiaeMarker::updataMinutiae(QString prevImgName, QString imgName)
{
    if (this->minutiae.empty())
        this->images.remove(prevImgName);
    else
        this->images[prevImgName] = this->minutiae;

    if (this->images.find(imgName) != this->images.end())
        this->minutiae = this->images[imgName];
    else
        this->minutiae.clear();

    emit updateMinutiaeMarkerSceneSignal("remove");
}

int MinutiaeMarker::countOutputFiles()
{
    int fileCnt = 0;

    for (auto img = this->images.begin(); img != this->images.end(); img++)
        fileCnt += img.value().size();

    return fileCnt;
}

std::map<QString, int> checkExistingImagesCountByMinutiaeTypes(QDir dir) {
    std::map<QString, int> mapToReturn;
    std::vector<QString> allMinutiaeIds = DboxMTCTConfig::getAllMinutiaIds();

    for (auto id: allMinutiaeIds) {
       mapToReturn[id] = 0;
    }

    for (auto imgName : dir.entryList()) {
        for (auto id: allMinutiaeIds) {
            if (imgName.contains(id)) {
                mapToReturn[id]++;
            }
        }
    }

    return mapToReturn;
}

void MinutiaeMarker::generateBlocks()
{
    this->getSettings()->printToConsole();
    QString leftOutputPath, rightOutputPath;
    QString leftImgName, rightImgName;
    QImage fpImg;
    QImage blockOrig, blockBlur, blockIrisBlur, blockTemp;
    QDir dir;

    int allFile = this->countOutputFiles();
    int currentFile = 0;
    int saveProgress = 0;

    if (this->settings->outputPath[0] == ".")
        this->settings->outputPath = QDir::currentPath() + this->settings->outputPath.mid(1, this->settings->outputPath.length()-1) + "/";

    for (auto img = this->images.begin(); img != this->images.end(); img++) {
        for (int actBlockSize = this->settings->blocksize - this->settings->additionalBlocks*2; actBlockSize <= this->settings->blocksize + this->settings->additionalBlocks*2; actBlockSize += 2) {

            std::map<QString, int> fileNumbers;

            leftOutputPath = this->settings->outputPath + QString::number(actBlockSize) + "x" +  QString::number(actBlockSize);
            rightOutputPath = img.key().left(img.key().lastIndexOf("."));
            dir.mkpath(leftOutputPath + "/orig/rot0/" + rightOutputPath);

            dir.setPath(leftOutputPath + "/orig/rot0/" + rightOutputPath);

            fileNumbers = checkExistingImagesCountByMinutiaeTypes(dir);

            for (auto block : img.value()) {

                leftImgName = leftOutputPath + "/orig/rot0/" + rightOutputPath + "/" + QString::number(actBlockSize);

                rightImgName = img.key().left(img.key().lastIndexOf(".")) + "_" + QString::fromStdString(block.getType().getId()) + "_" + QString::number(fileNumbers[QString::fromStdString(block.getType().getId())]++) + this->settings->outputFormat.mid(1).toLower();

                fpImg.load(this->settings->inputPath + "/" + img.key());
                fpImg = fpImg.convertToFormat(QImage::Format_Grayscale8);

                blockOrig = fpImg.copy(QRect(block.getCoordinates().x() - actBlockSize/2, block.getCoordinates().y() - actBlockSize/2, actBlockSize, actBlockSize));
                blockOrig.save(leftImgName + "_orig_rot0_" + rightImgName);

                if (this->settings->useBlur) {
                    dir.mkpath(leftOutputPath + "/blur/rot0/" + rightOutputPath);

                    leftImgName = leftOutputPath + "/blur/rot0/" + rightOutputPath + "/" + QString::number(actBlockSize);
                    blockBlur = dataAugmentationUtils.gaussianBlur(blockOrig, this->settings->blurValue);
                    blockBlur.save(leftImgName + "_blur_rot0_" + rightImgName);
                }
                if (this->settings->useIrisBlur) {
                    dir.mkpath(leftOutputPath + "/irisblur/rot0/" + rightOutputPath);

                    leftImgName = leftOutputPath + "/irisblur/rot0/" + rightOutputPath + "/" + QString::number(actBlockSize);
                    blockIrisBlur = dataAugmentationUtils.irisBlur(blockOrig, this->settings->irisBlurValue, this->settings->irisBlurRadius);
                    blockIrisBlur.save(leftImgName + "_irisblur_rot0_" + rightImgName);
                }

                if (this->settings->useMirroring && !this->settings->useRotation) {
                    //mirroring vertical
                    dir.mkpath(leftOutputPath + "/orig/mirrVer/" + rightOutputPath);
                    leftImgName = leftOutputPath + "/orig/mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);

                    dataAugmentationUtils.mirrorImage(blockOrig, false).save(leftImgName + "_orig_mirrVer_" + rightImgName);

                    //mirroring horizontal
                    dir.mkpath(leftOutputPath + "/orig/mirrHor/" + rightOutputPath);
                    leftImgName = leftOutputPath + "/orig/mirrHor/" + rightOutputPath + "/" + QString::number(actBlockSize);

                    dataAugmentationUtils.mirrorImage(blockOrig).save(leftImgName + "_orig_mirrHor_" + rightImgName);

                    if (this->settings->useBlur) {
                        //mirroring vertical
                        dir.mkpath(leftOutputPath + "/blur/mirrVer/" + rightOutputPath);

                        leftImgName = leftOutputPath + "/blur/mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);

                        dataAugmentationUtils.mirrorImage(blockBlur, false).save(leftImgName + "_blur_mirrVer_" + rightImgName);

                        //mirroring horizontal
                        dir.mkpath(leftOutputPath + "/blur/mirrHor/" + rightOutputPath);

                        leftImgName = leftOutputPath + "/blur/mirrHor/" + rightOutputPath + "/" + QString::number(actBlockSize);

                        dataAugmentationUtils.mirrorImage(blockBlur).save(leftImgName + "_blur_mirrHor_" + rightImgName);
                    }

                    if (this->settings->useIrisBlur) {
                        //mirroring vertical
                        dir.mkpath(leftOutputPath + "/irisblur/mirrVer/" + rightOutputPath);

                        leftImgName = leftOutputPath + "/irisblur/mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);

                        dataAugmentationUtils.mirrorImage(blockIrisBlur, false).save(leftImgName + "_irisblur_mirrVer_" + rightImgName);

                        //mirroring horizontal
                        dir.mkpath(leftOutputPath + "/irisblur/mirrHor/" + rightOutputPath);

                        leftImgName = leftOutputPath + "/irisblur/mirrHor/" + rightOutputPath + "/" + QString::number(actBlockSize);

                        dataAugmentationUtils.mirrorImage(blockIrisBlur, false).save(leftImgName + "_irisblur_mirrVer_" + rightImgName);
                    }
                }


                if (this->settings->useRotation) {
                    if (this->settings->useMirroring) {
                        dir.mkpath(leftOutputPath + "/orig/rot0_mirrVer/" + rightOutputPath);
                        leftImgName = leftOutputPath + "/orig/rot0_mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);

                        dataAugmentationUtils.mirrorImage(blockOrig, false).save(leftImgName + "_orig_rot0_mirrVer_" + rightImgName);

                        if (this->settings->useBlur) {
                            dir.mkpath(leftOutputPath + "/blur/rot0_mirrVer/" + rightOutputPath);
                            leftImgName = leftOutputPath + "/blur/rot0_mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);

                            dataAugmentationUtils.mirrorImage(blockBlur, false).save(leftImgName + "_blur_rot0_mirrVer_" + rightImgName);
                        }

                        if (this->settings->useIrisBlur) {
                            dir.mkpath(leftOutputPath + "/irisblur/rot0_mirrVer/" + rightOutputPath);
                            leftImgName = leftOutputPath + "/irisblur/rot0_mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);

                            dataAugmentationUtils.mirrorImage(blockIrisBlur, false).save(leftImgName + "_irisblur_rot0_mirrVer_" + rightImgName);
                        }
                    }

                    for (int rot = 90; rot < 360; rot += 90) {
                        leftImgName = leftOutputPath + "/orig/rot" + QString::number(rot) + "/" + rightOutputPath + "/" + QString::number(actBlockSize);
                        dir.mkpath(leftOutputPath + "/orig/rot" + QString::number(rot) + "/" + rightOutputPath);

                        dataAugmentationUtils.rotateImage(blockOrig, rot).save(leftImgName + "_orig_rot" + QString::number(rot) + "_" + rightImgName);

                        if (this->settings->useMirroring) {
                            leftImgName = leftOutputPath + "/orig/rot" + QString::number(rot) + "_mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);
                            dir.mkpath(leftOutputPath + "/orig/rot" + QString::number(rot) + "_mirrVer/" + rightOutputPath);

                            blockTemp = dataAugmentationUtils.rotateImage(blockOrig, rot);
                            dataAugmentationUtils.mirrorImage(blockTemp, rot).save(leftImgName + "_orig_rot" + QString::number(rot) + "_mirrVer_" + rightImgName);
                        }

                        if (this->settings->useBlur) {
                            leftImgName = leftOutputPath + "/blur/rot" + QString::number(rot) + "/" + rightOutputPath + "/" + QString::number(actBlockSize);
                            dir.mkpath(leftOutputPath + "/blur/rot" + QString::number(rot) + "/" + rightOutputPath);

                            dataAugmentationUtils.rotateImage(blockBlur, rot).save(leftImgName + "_blur_rot" + QString::number(rot) + "_" + rightImgName);

                            if (this->settings->useMirroring) {
                                leftImgName = leftOutputPath + "/blur/rot" + QString::number(rot) + "_mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);
                                dir.mkpath(leftOutputPath + "/blur/rot" + QString::number(rot) + "_mirrVer/" + rightOutputPath);

                                blockTemp = dataAugmentationUtils.rotateImage(blockBlur, rot);
                                dataAugmentationUtils.mirrorImage(blockTemp, false).save(leftImgName + "_blur_rot" + QString::number(rot) + "_mirrVer_" + rightImgName);
                            }
                        }

                        if (this->settings->useIrisBlur) {
                            leftImgName = leftOutputPath + "/irisblur/rot" + QString::number(rot) + "/" + rightOutputPath + "/" + QString::number(actBlockSize);
                            dir.mkpath(leftOutputPath + "/irisblur/rot" + QString::number(rot) + "/" + rightOutputPath);

                            dataAugmentationUtils.rotateImage(blockIrisBlur, rot).save(leftImgName + "_irisblur_rot" + QString::number(rot) + "_" + rightImgName);

                            if (this->settings->useMirroring) {
                                leftImgName = leftOutputPath + "/irisblur/rot" + QString::number(rot) + "_mirrVer/" + rightOutputPath + "/" + QString::number(actBlockSize);
                                dir.mkpath(leftOutputPath + "/irisblur/rot" + QString::number(rot) + "_mirrVer/" + rightOutputPath);

                                blockTemp = dataAugmentationUtils.rotateImage(blockIrisBlur, rot);
                                dataAugmentationUtils.mirrorImage(blockTemp, false).save(leftImgName + "_irisblur_rot" + QString::number(rot) + "_mirrVer_" + rightImgName);
                            }
                        }
                    }
                }
            }

            //Progress bar update
            currentFile += img.value().size();
            if (static_cast<int>(((currentFile*1.0) / (allFile*this->settings->additionalBlocks*2)) * 100) > saveProgress) {
                saveProgress = static_cast<int>(((currentFile*1.0) / (allFile*this->settings->additionalBlocks*2)) * 100);
                emit updateProgressBarSignal(this->objectName(), saveProgress);
            }
        }
    }

    emit updateProgressBarSignal(this->objectName(), 0);
    emit blocksSaved();

    this->minutiae.clear();
    this->images.clear();
    emit updateMinutiaeMarkerSceneSignal("remove");
}

//getters and setters
MinutiaeMarkerSettings *MinutiaeMarker::getSettings() const
{
    return settings;
}

void MinutiaeMarker::setSettings(MinutiaeMarkerSettings *value)
{
    settings = value;
}

QVector<Minutia> MinutiaeMarker::getMinutiae() const
{
    return minutiae;
}

void MinutiaeMarker::setMinutiae(const QVector<Minutia> &value)
{
    minutiae = value;
}
