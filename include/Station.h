/**
 * @file Station.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__STATION_H)
#define __STATION_H

#include "_common.h"

/**
 * @class Station
 * @brief Represents a station in the simulation that communicates with a server and handles its own state.
 */
class Station : public ProtocolDevice {
private:
    bool occupied; ///< Indicates whether the station is occupied
    bool loginSuccess; ///< Indicates if the station has successfully logged in
    POSITION_UNIT_TYPEDEF x; ///< The x-coordinate of the station's position
    POSITION_UNIT_TYPEDEF y; ///< The y-coordinate of the station's position
    ADDR_TYPEDEF chargingBotAddr; ///< The address of the charging bot associated with the station

public:
    /**
     * @brief Constructor for the Station class
     * @param addr The address of the station
     * @param en The environment in which the station operates
     * @param x The x-coordinate of the station's position
     * @param y The y-coordinate of the station's position
     */
    explicit Station(ADDR_TYPEDEF addr, Environment* en, POSITION_UNIT_TYPEDEF x, POSITION_UNIT_TYPEDEF y);

    /**
     * @brief Log a message in console
     * @param log The log message to be displayed
     */
    inline void log(const std::string& log) { ProtocolDevice::log("Station", log); }

    /**
     * @brief Send a message to the server without a payload
     * @param type The message type to be sent
     */
    inline void sendToServer(MsgType type){
        ProtocolDevice::send(type, MAIN_CHANNEL, SERVER_ADDR);
    }

    /**
     * @brief Send a message to the server with a payload
     * @param type The message type to be sent
     * @param payload The payload of the message
     */
    inline void sendToServer(MsgType type, const std::string payload) {
        ProtocolDevice::send(type, payload, MAIN_CHANNEL, SERVER_ADDR);
    }

    /**
     * @brief Send a message to the server with a payload and a callback for handling responses
     * @param type The message type to be sent
     * @param payload The payload of the message
     * @param callback A callback function to handle the server's response
     */
    inline void sendToServer(MsgType type, const std::string payload, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        ProtocolDevice::send(type, payload, MAIN_CHANNEL, SERVER_ADDR, callback);
    }

    /**
     * @brief Send a message to the server without a payload and with a callback for handling responses
     * @param type The message type to be sent
     * @param callback A callback function to handle the server's response
     */
    inline void sendToServer(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback){
        ProtocolDevice::send(type, MAIN_CHANNEL, SERVER_ADDR, callback);
    }

    /**
     * @brief Login to the server with the specified login key
     * @param loginKey The login key for authentication
     */
    void login(std::string loginKey);

    /**
     * @brief Update the station's free/occupied status on the server
     * @param free Indicates whether the station is free or occupied
     */
    void updateFreeToServer(bool free);

    /**
     * @brief Update the station's position on the server
     */
    void updatePositionToServer();

    /**
     * @brief Get the x-coordinate of the station's position
     * @return The x-coordinate of the station's position
     */
    inline POSITION_UNIT_TYPEDEF getX(){ return this->x; }

    /**
     * @brief Get the y-coordinate of the station's position
     * @return The y-coordinate of the station's position
     */
    inline POSITION_UNIT_TYPEDEF getY(){ return this->y; }

    /**
     * @brief Set the station's occupancy status and update the server accordingly
     * @param v The occupancy status, where true means occupied and false means free
     */
    inline void setOccupied(bool v){ this->occupied = v; this->updateFreeToServer(!v); }
};

#endif // __STATION_H
