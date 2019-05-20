#include "minutiamarker_config.h"
#include "Config/dbox_mtct_config.h"

//constructor
MinutiaeMarkerConfig::MinutiaeMarkerConfig() {
}

MinutiaeMarkerSettings MinutiaeMarkerConfig::getDefaultMinutiaeMarkerSetting()
{
    MinutiaeMarkerSettings settingToReturn;
    settingToReturn.blocksize = 19;
    settingToReturn.additionalBlocks = 2;

    settingToReturn.selectedMinutiaType = DboxMTCTConfig::Minutiae["nothing"];
    settingToReturn.useRotation = true;

    settingToReturn.useBlur = true;
    settingToReturn.blurValue = 0.6;

    settingToReturn.useMirroring = true;

    settingToReturn.useIrisBlur = true;
    settingToReturn.irisBlurValue = 0.8;
    settingToReturn.irisBlurRadius = 3.0;

    settingToReturn.outputPath = "./output";
    settingToReturn.outputFormat = "*.BMP";

    settingToReturn.useSameSizeForImages = true;

    return settingToReturn;
}
