#ifndef MINUTIAEMARKER_CONFIG_H
#define MINUTIAEMARKER_CONFIG_H

#include <Config/minutia_config.h>

#include <map>
#include <vector>

#include <QString>

///
/// \brief The DboxMTCTConfig class
/// This class stores all the data used in all parts of our application in form of static variables and functions.
class DboxMTCTConfig
{
public:
    //variables
    ///
    /// \brief The MinutiaTypes enum
    /// List of all minutiae types available in our application
    enum class MinutiaTypes
    {
        BIFURCATION,
        BREAK,
        BRIDGE,
        CROSSBAR,
        DOCK,
        DOT,
        ENCLOSURE,
        NOTHING,
        OPPOSITE_BIFURCATIONS,
        OVERLAP,
        RETURN,
        SHORT_RIDGE,
        SPIKE,
        TERMINATION,
        TRIFURCATION
    };

    ///
    /// \brief Minutiae
    /// Configuration map of all minutiae types
    static std::map<std::string, MinutiaConfig> Minutiae;

    //constructors
    ///
    /// \brief DboxMTCTConfig
    /// Default constructor
    DboxMTCTConfig();

    //methods
    ///
    /// \brief Function with all minutiae types with flag set to "active = true"
    /// \return all minutiae types with flag set to "active = true"
    ///
    static std::map<std::string, MinutiaConfig> getAllActiveMinutiae();

    ///
    /// \brief Function to get all minutia ids
    /// \return all minutia ids in std::vector<QString>
    ///
    static std::vector<QString> getAllMinutiaIds();

    ///
    /// \brief Function to get specific MinutiaConfig by property "name"
    /// \return MinutiaConfig instance filtered by property "name"
    ///
    static MinutiaConfig getMinutiaConfigByName(QString);

    ///
    /// \brief Function with all configurable parameters for all minutiae types
    /// \return all minutiae types available in our application
    ///
    static std::map<std::string, MinutiaConfig> setupMinutiae();
};

#endif // MINUTIAEMARKER_CONFIG_H
