#include "dbox_mtct_config.h"

//constructor
DboxMTCTConfig::DboxMTCTConfig() {}

std::map<std::string, MinutiaConfig> DboxMTCTConfig::setupMinutiae()
{
    std::map<std::string, MinutiaConfig> mapToReturn;

    //BIFURCATION
    MinutiaConfig bifurcation;
    bifurcation.setIsActive(true);
    bifurcation.setId("bifurcation");
    bifurcation.setColorHexCode("#000000");
    bifurcation.setIconPath("./Resources/MinutiaeIcons/BIFURCATION.png");
    bifurcation.setName("BIFURCATION");

    //BREAK
    MinutiaConfig breakMinutia;
    breakMinutia.setIsActive(true);
    breakMinutia.setId("break");
    breakMinutia.setColorHexCode("#000000");
    breakMinutia.setIconPath("./Resources/MinutiaeIcons/BREAK.png");
    breakMinutia.setName("BREAK");

    //BRIDGE
    MinutiaConfig bridge;
    bridge.setIsActive(true);
    bridge.setId("bridge");
    bridge.setColorHexCode("#000000");
    bridge.setIconPath("./Resources/MinutiaeIcons/BRIDGE.png");
    bridge.setName("BRIDGE");

    //CROSSBAR
    MinutiaConfig crossbar;
    crossbar.setIsActive(true);
    crossbar.setId("crossbar");
    crossbar.setColorHexCode("#000000");
    crossbar.setIconPath("./Resources/MinutiaeIcons/CROSSBAR.png");
    crossbar.setName("CROSSBAR");

    //DOCK
    MinutiaConfig dock;
    dock.setIsActive(true);
    dock.setId("dock");
    dock.setColorHexCode("#000000");
    dock.setIconPath("./Resources/MinutiaeIcons/DOCK.png");
    dock.setName("DOCK");

    //DOT
    MinutiaConfig dot;
    dot.setIsActive(true);
    dot.setId("dot");
    dot.setColorHexCode("#000000");
    dot.setIconPath("./Resources/MinutiaeIcons/DOT.png");
    dot.setName("DOT");

    //ENCLOSURE
    MinutiaConfig enclosure;
    enclosure.setIsActive(true);
    enclosure.setId("enclosure");
    enclosure.setColorHexCode("#000000");
    enclosure.setIconPath("./Resources/MinutiaeIcons/ENCLOSURE.png");
    enclosure.setName("ENCLOSURE");

    //NOTHING
    MinutiaConfig nothing;
    nothing.setIsActive(true);
    nothing.setId("nothing");
    nothing.setColorHexCode("#555555");
    nothing.setIconPath("./Resources/MinutiaeIcons/NOTHING.png");
    nothing.setName("NOTHING");

    //OPPOSITE_BIFURCATIONS
    MinutiaConfig opposite_bifurcations;
    opposite_bifurcations.setIsActive(true);
    opposite_bifurcations.setId("opposite_bifurcations");
    opposite_bifurcations.setColorHexCode("#000000");
    opposite_bifurcations.setIconPath("./Resources/MinutiaeIcons/OPPOSITE_BIFURCATIONS.png");
    opposite_bifurcations.setName("OPPOSITE_BIFURCATIONS");

    //OVERLAP
    MinutiaConfig overlap;
    overlap.setIsActive(true);
    overlap.setId("overlap");
    overlap.setColorHexCode("#000000");
    overlap.setIconPath("./Resources/MinutiaeIcons/OVERLAP.png");
    overlap.setName("OVERLAP");

    //RETURN
    MinutiaConfig returnMinutia;
    returnMinutia.setIsActive(true);
    returnMinutia.setId("return");
    returnMinutia.setColorHexCode("#000000");
    returnMinutia.setIconPath("./Resources/MinutiaeIcons/RETURN.png");
    returnMinutia.setName("RETURN");

    //SHORT_RIDGE
    MinutiaConfig short_ridge;
    short_ridge.setIsActive(true);
    short_ridge.setId("return");
    short_ridge.setColorHexCode("#000000");
    short_ridge.setIconPath("./Resources/MinutiaeIcons/SHORT_RIDGE.png");
    short_ridge.setName("SHORT_RIDGE");

    //SPIKE
    MinutiaConfig spike;
    spike.setIsActive(true);
    spike.setId("spike");
    spike.setColorHexCode("#000000");
    spike.setIconPath("./Resources/MinutiaeIcons/SPIKE.png");
    spike.setName("SPIKE");

    //TERMINATION
    MinutiaConfig termination;
    termination.setIsActive(true);
    termination.setId("termination");
    termination.setColorHexCode("#000000");
    termination.setIconPath("./Resources/MinutiaeIcons/TERMINATION.png");
    termination.setName("TERMINATION");

    //TRIFURCATION
    MinutiaConfig trifurcation;
    trifurcation.setIsActive(true);
    trifurcation.setId("trifurcation");
    trifurcation.setColorHexCode("#000000");
    trifurcation.setIconPath("./Resources/MinutiaeIcons/TRIFURCATION.png");
    trifurcation.setName("TRIFURCATION");

    mapToReturn.insert({"bifurcation", bifurcation});
    mapToReturn.insert({"break", breakMinutia});
    mapToReturn.insert({"bridge", bridge});
    mapToReturn.insert({"crossbar", crossbar});
    mapToReturn.insert({"dock", dock});
    mapToReturn.insert({"dot", dot});
    mapToReturn.insert({"enclosure", enclosure});
    mapToReturn.insert({"nothing", nothing});
    mapToReturn.insert({"opposite_bifurcations", opposite_bifurcations});
    mapToReturn.insert({"overlap", overlap});
    mapToReturn.insert({"return", returnMinutia});
    mapToReturn.insert({"short_ridge", short_ridge});
    mapToReturn.insert({"spike", spike});
    mapToReturn.insert({"termination", termination});
    mapToReturn.insert({"trifurcation", trifurcation});

    return mapToReturn;
}

//variables
std::map<std::string, MinutiaConfig> DboxMTCTConfig::Minutiae = setupMinutiae();

//public methods
std::map<std::string, MinutiaConfig> DboxMTCTConfig::getAllActiveMinutiae()
{
    std::map<std::string, MinutiaConfig> mapToRet;

    for (auto it=Minutiae.begin(); it!=Minutiae.end(); ++it) {
        if (it->second.getIsActive()) {
            mapToRet[it->first] = it->second;
        }
    }

    return mapToRet;
}

std::vector<QString> DboxMTCTConfig::getAllMinutiaIds()
{
    std::vector<QString> vectorToReturn;

    for (auto it=Minutiae.begin(); it!=Minutiae.end(); ++it) {
        vectorToReturn.push_back(QString::fromStdString(it->first));
    }

    return vectorToReturn;
}

MinutiaConfig DboxMTCTConfig::getMinutiaConfigByName(QString name)
{
    MinutiaConfig MinutiaConfig = Minutiae["nothing"];

    for (auto it=Minutiae.begin(); it!=Minutiae.end(); ++it) {
        if (it->second.getName() == name.toStdString() && it->second.getIsActive()) {
            MinutiaConfig = it->second;
        }
    }

    return MinutiaConfig;
}
