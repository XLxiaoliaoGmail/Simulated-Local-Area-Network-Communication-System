/**
 * @file Server.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__SERVER_H)
#define __SERVER_H

#include "_common.h"

/**
 * @struct RobotData
 * @brief Structure to store data related to robots. Currently.
 */
struct RobotData {
    explicit RobotData(){}
};

/**
 * @struct StationData
 * @brief Structure to store information about stations in the environment, includes the station address, its availability status, and its position (x, y).
 */
struct StationData {
    ADDR_TYPEDEF addr; ///< The address of the station
    bool free; ///< Whether the station is free (available for use)
    POSITION_UNIT_TYPEDEF x; ///< The x-coordinate of the station's position
    POSITION_UNIT_TYPEDEF y; ///< The y-coordinate of the station's position
    
    /**
     * @brief Constructor to initialize station data.
     * @param addr The address of the station
     */
    explicit StationData(ADDR_TYPEDEF addr) : addr(addr), free(false) {}
};

/**
 * @class Server
 * @brief The Server class handles the management of robots and stations, including login key management, and station availability.
 */
class Server : public ProtocolDevice {
private:
    std::unordered_map<ADDR_TYPEDEF, RobotData*> robotsInfo; ///< A map of robot addresses to their corresponding robot data
    std::unordered_map<ADDR_TYPEDEF, StationData*> stationsInfo; ///< A map of station addresses to their corresponding station data
    std::string robotLoginKey; ///< The login key for robots
    std::string stationLoginKey; ///< The login key for stations

public:
    /**
     * @brief Constructor to initialize the server with an address and environment
     * @param addr The address of the server
     * @param en The environment in which the server operates
     */
    explicit Server(ADDR_TYPEDEF addr, Environment* en);

    /**
     * @brief Check if a given address belongs to a robot
     * @param addr The address to check
     * @return true if the address corresponds to a robot, false otherwise
     */
    inline bool isRobot(ADDR_TYPEDEF addr) {
        return this->robotsInfo.count(addr) != 0;
    }

    /**
     * @brief Check if a given address belongs to a station
     * @param addr The address to check
     * @return true if the address corresponds to a station, false otherwise
     */
    inline bool isStation(ADDR_TYPEDEF addr) {
        return this->stationsInfo.count(addr) != 0;
    }

    /**
     * @brief Retrieve a free station if available
     * @return A pointer to the free station if found, otherwise null
     */
    StationData* getFreeStation();

    /**
     * @brief Set the availability status of a station
     * @param addr The address of the station
     * @param free The new availability status (true for free, false for occupied)
     */
    inline void setStationStatus(ADDR_TYPEDEF addr, bool free) {
        if (this->stationsInfo.count(addr) == 0) {
            return;
        }
        this->stationsInfo[addr]->free = free;
    }

    /**
     * @brief Set the login key for robots
     * @param key The login key to set
     */
    inline void setRobotLoginKey(const std::string& key) {
        this->robotLoginKey = this->formatKeyStr(key);
        this->log("Set up robot login key successfully, key:" + key);
    }

    /**
     * @brief Set the login key for stations
     * @param key The login key to set
     */
    inline void setStationLoginKey(const std::string& key) {
        this->stationLoginKey = this->formatKeyStr(key);
        this->log("Set up station login key successfully, key:" + key);
    }

    /**
     * @brief Add a robot with a specific address to the server's list of robots
     * @param addr The address of the robot
     */
    inline void addRobotAddr(ADDR_TYPEDEF addr) {
        this->robotsInfo[addr] = new RobotData();
    }

    /**
     * @brief Add a station with a specific address to the server's list of stations
     * @param addr The address of the station
     */
    inline void addStationAddr(ADDR_TYPEDEF addr) {
        this->stationsInfo[addr] = new StationData(addr);
    }

    /**
     * @brief Make the server listen to a specific channel for incoming messages
     * @param channelIndex The index of the channel to listen to
     */
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }

    /**
     * @brief Log a message with the "Server" tag
     * @param log The log message
     */
    inline void log(const std::string& log) {
        ProtocolDevice::log("Server", log);
    }
};

#endif // __SERVER_H
