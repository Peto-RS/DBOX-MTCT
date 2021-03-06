#ifndef MINUTIAEMARKER_DATAAUGMENTATIONUTILS_H
#define MINUTIAEMARKER_DATAAUGMENTATIONUTILS_H

#include "qmatconverter.h"

#include <QImage>

#include "opencv2/opencv.hpp"

///
/// \brief The MinutiaeMarker_ImageUtils class.
/// Collection of static methods for the purpose of data augmentation.
///
class MinutiaeMarker_DataAugmentationUtils
{
public:
    ///
    /// \brief MinutiaeMarker_ImageUtils
    /// Default constructor
    MinutiaeMarker_DataAugmentationUtils();

    /***
     * Static methods
     ***/
    ///
    /// \brief Rotate image by given angle in degrees.
    /// \param image - input image
    /// \param angle - angle in degrees
    /// \return Rotated image
    ///
    static QImage rotateImage(QImage image, int angle);

    ///
    /// \brief Perform iris blur operation on given image.
    /// \param image - input image
    /// \param gaussBlurSigmaX_image - value of function parameter cv::GaussianBlur sigmaX applied to image itself
    /// \param gaussBlurSigmaX_mask - value of function parameter cv::GaussianBlur sigmaX applied to image circular mask
    /// \return Image with application of iris blur
    ///
    static QImage irisBlur(QImage image, double gaussBlurSigmaX_image, double gaussBlurSigmaX_mask);

    ///
    /// \brief Perform Gaussian blur operation on given image using cv::GaussianBlur function.
    /// \param image - input image
    /// \param gaussBlurSigmaX - value of function parameter cv::GaussianBlur sigmaX applied to image
    /// \return Image with application of Gaussian blur
    ///
    static QImage gaussianBlur(QImage image, double gaussBlurSigmaX);

    ///
    /// \brief Apply Gaussian blur filter with weighted sum of pixels on given image using cv::GaussianBlur function.
    /// \param image - input image
    /// \return Image with application of Gaussian blur filter with sharpening
    ///
    static QImage sharpenImage(QImage image);

    ///
    /// \brief Perform mirroring operation on input image.
    /// \param image - input image
    /// \param mirrorHorizontal - if set to true use horizontal mirorring, else use vertical mirorring
    /// \return Image with application of mirroring on image
    ///
    static QImage mirrorImage(QImage image, bool mirrorHorizontal = true);
};

#endif // MINUTIAEMARKER_DATAAUGMENTATIONUTILS_H
