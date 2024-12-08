/**
 * @file ProtocolDevice.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__ProtocolDevice_H)
#define __ProtocolDevice_H

#include "_common.h"

/**
 * @class ProtocolDevice
 * @brief This class represents a protocol-specific device that extends the Device class.
 *        It provides message handling mechanisms, including the ability to register callbacks for different message types 
 *        and send messages with specific payloads. 
 */
class ProtocolDevice : public Device {
private:
    std::unordered_map<MsgType, std::function<void(ADDR_TYPEDEF, const std::string&)>> callbacks; ///< A map that holds the callback functions for each message type.
    std::unordered_map<MsgType, std::function<void(ADDR_TYPEDEF, const std::string&)>> onceCallbacks; ///< A map that holds the one-time callback functions for each message type.

public:
    /**
     * @brief Constructor of the ProtocolDevice class
     * @param addr The address of the device
     * @param en The environment in which the device operates
     */
    explicit ProtocolDevice(ADDR_TYPEDEF addr, Environment* en) : Device(addr, en) {}

    /**
     * @brief Format a key string to ensure it meets the specified length, adding 'x' characters as needed.
     * @param key The key string to be formatted
     * @return The formatted key string
     */
    std::string formatKeyStr(const std::string& key){
        auto format = key;
        if (format.length() < KEY_FORMAT_LENGTH) {
            format.insert(0, KEY_FORMAT_LENGTH - format.length(), 'x');
        } else if (format.length() > KEY_FORMAT_LENGTH) {
            format = format.substr(0, KEY_FORMAT_LENGTH);
        }
        return format;
    }

    /**
     * @brief Convert a MsgType to its hexadecimal string representation
     * @param num The MsgType to convert
     * @return The hexadecimal string representation of the MsgType
     */
    std::string MsgTypeToHexString(MsgType num) {
        std::stringstream ss;
        ss << std::hex << std::setw(MSGTYPE_LENGTH_IN_STR) << std::setfill('0') << static_cast<int>(num);
        return ss.str();
    }

    /**
     * @brief Convert a hexadecimal string to a MsgType
     * @param hexStr The hexadecimal string representing the MsgType
     * @return The MsgType
     */
    inline MsgType hexStringToMsgType(const std::string& hexStr) {
        return static_cast<MsgType>(std::stoi(hexStr));
    }

    /**
     * @brief Send a message with the specified type and payload to a target device via a specified channel
     * @param type The message type
     * @param payload The message payload
     * @param channelIndex The index of the channel to use for sending the message
     * @param target The address of the target device
     */
    inline void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target) {
        Device::send(MsgTypeToHexString(type) + payload, channelIndex, target);
    }

    /**
     * @brief Send a message with the specified type without payload to a target device via a specified channel
     * @param type The message type
     * @param channelIndex The index of the channel to use for sending the message
     * @param target The address of the target device
     */
    inline void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target){
        Device::send(MsgTypeToHexString(type), channelIndex, target);
    }

    /**
     * @brief Send a message with the specified type and payload to a target device via a specified channel, 
     *        and register a one-time callback function to be executed when the response is received.
     * @param type The message type
     * @param payload The message payload
     * @param channelIndex The index of the channel to use for sending the message
     * @param target The address of the target device
     * @param callback The callback function to be executed upon receiving the response
     */
    inline void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        Device::send(MsgTypeToHexString(type) + payload, channelIndex, target);
        this->once(type, callback);
    }

    /**
     * @brief Send a message with the specified type without payload to a target device via a specified channel, 
     *        and register a one-time callback function to be executed when the response is received.
     * @param type The message type
     * @param channelIndex The index of the channel to use for sending the message
     * @param target The address of the target device
     * @param callback The callback function to be executed upon receiving the response
     */
    inline void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target, std::function<void(ADDR_TYPEDEF, const std::string&)> callback){
        Device::send(MsgTypeToHexString(type), channelIndex, target);
        this->once(type, callback);
    }

    /**
     * @brief Register a callback function for a specific message type. 
     * @param type The message type
     * @param callback The callback function to be executed
     */
    inline void on(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        this->callbacks[type] = callback;
    }

    /**
     * @brief Register a one-time callback function for a specific message type. 
     * @param type The message type
     * @param callback The callback function to be executed
     */
    inline void once(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        this->onceCallbacks[type] = callback;
    }

    /**
     * @brief Handle the incoming message by invoking the corresponding callback for the message type. User should not call this function
     * @param senderAddr The address of the sender device
     * @param type The type of the message
     * @param payload The message payload
     */
    inline void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload) {
        if(this->onceCallbacks.count(type) != 0) {
            this->onceCallbacks.at(type)(senderAddr, payload);
            this->onceCallbacks.erase(type);
        }
        if(this->callbacks.count(type) != 0) {
            this->callbacks.at(type)(senderAddr, payload);
        }
    }

    /**
     * @brief Handle the received message, if the target address matches this device's address. User should not call this function
     * @param msg The message received
     * @param channelIndex The channel through which the message was received
     */
    inline void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex) override {
        // just handle msg that target is self
        if(Message::hexStringToUint(msg->target) != this->getAddr()) {
            return;
        }
        this->msgHandler(Message::hexStringToUint(msg->sender), hexStringToMsgType(msg->payload.substr(0,MSGTYPE_LENGTH_IN_STR)), msg->payload.substr(MSGTYPE_LENGTH_IN_STR));
    };

    /**
     * @brief Log a message for this device, with an optional sender label
     * @param who The sender of the log message
     * @param log The log message
     */
    inline void log(const std::string& who, const std::string& log) {
        Device::log("[" + who + "]" + log);
    };
};

#endif // __ProtocolDevice_H
