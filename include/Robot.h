/**
 * @file Robot.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#ifndef __ROBOT_H
#define __ROBOT_H

#include "_common.h"

/**
 * @class Robot
 * @brief Represents a robot device that extends the ProtocolDevice class.
 *        This class includes functionality for movement, power management, and communication with a server and charging station.
 */
class Robot : public ProtocolDevice {
private:
    bool needCharging; ///< Indicates whether the robot needs charging
    bool loginSuccess; ///< Indicates whether the robot's login attempt was successful
    POWER_TYPEDEF power; ///< The current power level of the robot
    ADDR_TYPEDEF chargingStationAddr; ///< The address of the charging station the robot is connected to

public:
    /**
     * @brief Constructor for the Robot class
     * @param addr The address of the robot
     * @param en The environment in which the robot operates
     */
    explicit Robot(ADDR_TYPEDEF addr, Environment* en);

    /**
     * @brief Starts listening to a specific channel
     * @param channelIndex The index of the channel to listen to
     */
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }

    /**
     * @brief Print log in console
     * @param log The log message
     */
    inline void log(const std::string& log) { ProtocolDevice::log("Robot", log); }

    /**
     * @brief Assume the bot moves to a certain position
     * @param pos The target position to move to
     */
    inline void gotoPosition(Position pos){
        this->log("Move to position :" + Message::positionToHexString(pos.x, pos.y) );
    }

    /**
     * @brief Increases the robot's power by 20 units
     */
    inline void chagingUp(){ this->power += 20; }

    /**
     * @brief Returns the current power level of the robot
     * @return The current power level
     */
    inline POWER_TYPEDEF getPower() const { return this->power; }

    /**
     * @brief Sends a login request to the server
     * @param loginKey The login key for the server
     */
    void login(std::string loginKey);

    /**
     * @brief Notifies that the robot needs charging
     */
    void needCharge();

    /**
     * @brief Sends a message to the server with a specific type and payload
     * @param type The message type
     * @param payload The message payload
     */
    inline void sendToServer(MsgType type, const std::string payload) {
        ProtocolDevice::send(type, payload, MAIN_CHANNEL, SERVER_ADDR);
    }

    /**
     * @brief Sends a message to the server with a specific type (without payload)
     * @param type The message type
     */
    inline void sendToServer(MsgType type){
        ProtocolDevice::send(type, MAIN_CHANNEL, SERVER_ADDR);
    }

    /**
     * @brief Sends a message to the server with a specific type, payload, and callback function
     * @param type The message type
     * @param payload The message payload
     * @param callback The callback function to be invoked after the message is processed
     */
    inline void sendToServer(MsgType type, const std::string payload, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        ProtocolDevice::send(type, payload, MAIN_CHANNEL, SERVER_ADDR, callback);
    }

    /**
     * @brief Sends a message to the server with a specific type and callback function (without payload)
     * @param type The message type
     * @param callback The callback function to be invoked after the message is processed
     */
    inline void sendToServer(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback){
        ProtocolDevice::send(type, MAIN_CHANNEL, SERVER_ADDR, callback);
    }

    /**
     * @brief Sends a handshake message to the charging station
     * @param handShakey The handshake message
     * @param stationAddr The address of the charging station
     * @param channelIndex The channel index for communication
     */
    void sendHandshakeToStation(std::string handShakey, ADDR_TYPEDEF stationAddr, CHANNEL_INDEX_TYPEDEF channelIndex);

    /**
     * @brief Sends a keep-alive message when the robot is charging
     */
    inline void keepAliveWhenCharging();

    /**
     * @brief Notifies the charging station that the robot's power has finished charging
     * @param stationAddr The address of the charging station
     */
    inline void sendPowerFinish(ADDR_TYPEDEF stationAddr);
};

#endif // __ROBOT_H
