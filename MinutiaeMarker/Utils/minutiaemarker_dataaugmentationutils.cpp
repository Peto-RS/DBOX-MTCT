#include "minutiaemarker_dataaugmentationutils.h"

MinutiaeMarker_DataAugmentationUtils::MinutiaeMarker_DataAugmentationUtils() {}

QImage MinutiaeMarker_DataAugmentationUtils::rotateImage(QImage image, int angle)
{
    QTransform imgRotate;
    imgRotate.rotate(angle);

    return image.transformed(imgRotate);
}

QImage MinutiaeMarker_DataAugmentationUtils::irisBlur(QImage image, double gaussBlurSigmaX_image, double gaussBlurSigmaX_mask)
{
    cv::Mat block = QMatConverter::QImage2Mat(image, CV_8UC1);
    cv::Mat blockBlurred;
    cv::Mat irisBlurredBlock = cv::Mat::zeros(block.size(), block.type());

    int kernelSize = 9;

    cv::GaussianBlur(block, blockBlurred, cv::Size(kernelSize, kernelSize), gaussBlurSigmaX_image);

    cv::Mat mask = cv::Mat(block.rows, block.cols, CV_8UC1, cv::Scalar(255));
    cv::circle(mask, cv::Point (block.cols / 2, block.rows / 2), int(block.rows / 2 * 0.75), cv::Scalar(0), -1);
    cv::GaussianBlur(mask, mask, cv::Size(kernelSize, kernelSize), gaussBlurSigmaX_mask);

    for (int y = 0; y < irisBlurredBlock.rows; ++y)
        for (int x = 0; x < irisBlurredBlock.cols; ++x)
        {
            uchar pixelOrig = block.at<uchar>(y, x);
            uchar pixelBlur = blockBlurred.at<uchar>(y, x);
            float blurVal = mask.at<unsigned char>(y, x)/255.0f;
            uchar pixelOut = uchar(blurVal * pixelBlur + (1.0f - blurVal)* pixelOrig);

            irisBlurredBlock.at<uchar>(y, x) = pixelOut;
        }

    return QMatConverter::Mat2QImage(irisBlurredBlock, QImage::Format_Grayscale8);
}

QImage MinutiaeMarker_DataAugmentationUtils::gaussianBlur(QImage image, double gaussBlurSigmaX)
{
    cv::Mat blurredImg = QMatConverter::QImage2Mat(image, CV_8UC1);

    cv::GaussianBlur(blurredImg, blurredImg, cv::Size(3, 3), gaussBlurSigmaX);

    return QMatConverter::Mat2QImage(blurredImg, QImage::Format_Grayscale8);
}

QImage MinutiaeMarker_DataAugmentationUtils::sharpenImage(QImage image)
{
    cv::Mat sharpenedImg = QMatConverter::QImage2Mat(image, CV_8UC1);

    cv::GaussianBlur(sharpenedImg, sharpenedImg, cv::Size(0, 0), 3);
    cv::addWeighted(sharpenedImg, 1.5, sharpenedImg, -0.5, 0, sharpenedImg);

    return QMatConverter::Mat2QImage(sharpenedImg, QImage::Format_Grayscale8);
}

QImage MinutiaeMarker_DataAugmentationUtils::mirrorImage(QImage image, bool mirrorHorizontal)
{
    return mirrorHorizontal ? image.mirrored(true, false) : image.mirrored();
}
