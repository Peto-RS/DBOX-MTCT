#include "minutiaemarker.h"
#include "MinutiaeMarker/Config/minutiamarker_config.h"

MinutiaeMarker::MinutiaeMarker()
{
    this->setObjectName("marker");

//    MinutiaeMarkerSettings defaultSettings = MinutiaeMarkerConfig::getDefaultMinutiaeMarkerSetting();
    this->settings = new MinutiaeMarkerSettings();

//    this->settings->blocksize = defaultSettings.blocksize;
//    this->settings->additionalBlocks = defaultSettings.additionalBlocks;
//    this->settings->selectedMinutiaType = defaultSettings.selectedMinutiaType;
//    this->settings->useRotation = defaultSettings.useRotation;
//    this->settings->useBlur = defaultSettings.useBlur;
//    this->settings->blurValue = defaultSettings.blurValue;
//    this->settings->useMirroring = defaultSettings.useMirroring;
//    this->settings->useIrisBlur = defaultSettings.useIrisBlur;
//    this->settings->irisBlurValue = defaultSettings.irisBlurValue;
//    this->settings->irisBlurRadius = defaultSettings.irisBlurRadius;
//    this->settings->inputPath = defaultSettings.inputPath;
//    this->settings->outputPath = defaultSettings.outputPath;
//    this->settings->outputFormat = defaultSettings.outputFormat;
//    this->settings->useSameSizeForImages = defaultSettings.useSameSizeForImages;
}

void MinutiaeMarker::setImages(const QMap<QString, QVector<Minutia> > &value)
{
    images = value;
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

int checkGivenImageCountInFolder(QDir dir, QString imgName) {
    int countToReturn = 0;

    for (auto iName : dir.entryList()) {
        if (iName.contains(imgName))
            countToReturn++;
    }

    return countToReturn;
}

void MinutiaeMarker::generateBlocks()
{
    this->getSettings()->printToConsole();
    QString classPath, rightOutputPath;
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
        //store count of images in each class
//        std::map<QString, int> fileNumbers;
        int fileNumbers;

        for (auto block : img.value()) {
            classPath = this->settings->outputPath + QString::fromStdString(block.getType().getId());

            dir.mkpath(classPath);
            dir.setPath(classPath);

//            fileNumbers = checkExistingImagesCountByMinutiaeTypes(dir);
            fileNumbers = checkGivenImageCountInFolder(dir, img.key().left(img.key().lastIndexOf(".")));

            rightImgName = QString::fromStdString(block.getType().getId()) + "_" + img.key().left(img.key().lastIndexOf(".")) + this->settings->outputFormat.mid(1).toLower();

            fpImg.load(this->settings->inputPath + "/" + img.key());
            fpImg = fpImg.convertToFormat(QImage::Format_Grayscale8);

            blockOrig = fpImg.copy(QRect(block.getCoordinates().x(), block.getCoordinates().y(), block.getWidth(), block.getHeight()));

            int imgHeight, imgWidth;
            imgHeight = blockOrig.height();
            imgWidth = blockOrig.width();
            if (this->settings->useSameSizeForImages && imgHeight != this->settings->blocksize && imgWidth != this->settings->blocksize) {
                blockOrig = blockOrig.scaled(this->settings->blocksize, this->settings->blocksize);
            }

            blockOrig.save(classPath + "/orig_rot0_" + QString::number(fileNumbers++) + "_" + rightImgName);

            if (this->settings->useBlur) {
                blockBlur = dataAugmentationUtils.gaussianBlur(blockOrig, this->settings->blurValue);
                blockBlur.save(classPath + "/blur_rot0_" + QString::number(fileNumbers++) + "_" + rightImgName);
            }
            if (this->settings->useIrisBlur) {
                blockIrisBlur = dataAugmentationUtils.irisBlur(blockOrig, this->settings->irisBlurValue, this->settings->irisBlurRadius);
                blockIrisBlur.save(classPath + "/irisblur_rot0_" + QString::number(fileNumbers++) + "_" + rightImgName);
            }

            if (this->settings->useMirroring && !this->settings->useRotation) {
                dataAugmentationUtils.mirrorImage(blockOrig, false).save(classPath + "/orig_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                dataAugmentationUtils.mirrorImage(blockOrig).save(classPath + "/orig_mirrHor_" + QString::number(fileNumbers++) + "_" + rightImgName);

                if (this->settings->useBlur) {
                    dataAugmentationUtils.mirrorImage(blockBlur, false).save(classPath + "/blur_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                    dataAugmentationUtils.mirrorImage(blockBlur).save(classPath + "/blur_mirrHor_" + QString::number(fileNumbers++) + "_" + rightImgName);
                }

                if (this->settings->useIrisBlur) {
                    dataAugmentationUtils.mirrorImage(blockIrisBlur, false).save(classPath + "/irisblur_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                    dataAugmentationUtils.mirrorImage(blockIrisBlur).save(classPath + "/irisblur_mirrHor_" + QString::number(fileNumbers++) + "_" + rightImgName);
                }
            }


            if (this->settings->useRotation) {
                if (this->settings->useMirroring) {
                    dataAugmentationUtils.mirrorImage(blockOrig, false).save(classPath + "/orig_rot0_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);

                    if (this->settings->useBlur) {
                        dataAugmentationUtils.mirrorImage(blockBlur, false).save(classPath + "/blur_rot0_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                    }

                    if (this->settings->useIrisBlur) {
                        dataAugmentationUtils.mirrorImage(blockIrisBlur, false).save(classPath + "/irisblur_rot0_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                    }
                }

                for (int rot = 90; rot < 360; rot += 90) {
                    dataAugmentationUtils.rotateImage(blockOrig, rot).save(classPath + "/orig_rot" + QString::number(rot) + "_" + QString::number(fileNumbers++) + "_" + rightImgName);

                    if (this->settings->useMirroring) {
                        blockTemp = dataAugmentationUtils.rotateImage(blockOrig, rot);
                        dataAugmentationUtils.mirrorImage(blockTemp, rot).save(classPath + "/orig_rot" + QString::number(rot) + "_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                    }

                    if (this->settings->useBlur) {
                        dataAugmentationUtils.rotateImage(blockBlur, rot).save(classPath + "/blur_rot" + QString::number(rot) + "_" + QString::number(fileNumbers++) + "_" + rightImgName);

                        if (this->settings->useMirroring) {
                            blockTemp = dataAugmentationUtils.rotateImage(blockBlur, rot);
                            dataAugmentationUtils.mirrorImage(blockTemp, false).save(classPath + "/blur_rot" + QString::number(rot) + "_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                        }
                    }

                    if (this->settings->useIrisBlur) {
                        dataAugmentationUtils.rotateImage(blockIrisBlur, rot).save(classPath + "/irisblur_rot" + QString::number(rot) + "_" + QString::number(fileNumbers++) + "_" + rightImgName);

                        if (this->settings->useMirroring) {
                            blockTemp = dataAugmentationUtils.rotateImage(blockIrisBlur, rot);
                            dataAugmentationUtils.mirrorImage(blockTemp, false).save(classPath + "/irisblur_rot" + QString::number(rot) + "_mirrVer_" + QString::number(fileNumbers++) + "_" + rightImgName);
                        }
                    }
                }
            }
        }

        //Progress bar update
        currentFile += img.value().size();
        if (static_cast<int>(((currentFile*1.0) / allFile * 100) > saveProgress)) {
            saveProgress = static_cast<int>((currentFile*1.0) / allFile * 100);
            emit updateProgressBarSignal(this->objectName(), saveProgress);
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
