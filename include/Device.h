/**
 * @file Device.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__DEVICE_H)
#define __DEVICE_H

#include "_common.h"

/**
 * @class Device
 * @brief This class represents a networked device within a communication environment. Each device
 *        has an address, a reference to an environment, a message queue, and a set of methods to send
 *        and receive messages. It supports state management (e.g., busy or waiting), and can listen
 *        to specific communication channels. Callbacks are provided for state changes, and error handling
 *        is available.
 */
class Device {
private:
    ADDR_TYPEDEF addr; ///< The address of the device
    Environment* en; ///< Pointer to the environment this device belongs to
    TIME_TYPEDEF txDelay; ///< Transmission delay for current message
    bool busy; ///< Indicates if the device is currently busy sending
    bool waiting; ///< Indicates if the device is in a waiting state
    std::function<void(bool)> onBusyChanged; ///< Callback for when the busy state changes
    std::function<void(bool)> onWaitingChanged; ///< Callback for when the waiting state changes
    CHANNEL_INDEX_TYPEDEF listeningIndex; ///< The channel index the device is listening to
    bool logEnable; ///< Whether printing logs is enabled for this device
    std::queue<std::tuple<std::string, CHANNEL_INDEX_TYPEDEF, ADDR_TYPEDEF>> msgQueue; ///< Message queue for the device

private:
    /**
     * @brief This is the actual low-level send method, but users should not be concerned with or use it.
     * @param payload The message payload to be sent
     * @param channelIndex The index of the channel on which the message is sent
     * @param target The address of the target device
     */
    void trueSend(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target);

    /**
     * @brief Enqueue a message to be sent
     * @param payload The message payload to be added to the queue
     * @param channelIndex The index of the channel on which the message will be sent
     * @param target The address of the target device for the message
     */
    void enqueue(std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target);

    /**
     * @brief Process the message queue
     */
    void processQueue();


protected:
    /**
     * @brief This is the method provided for users to use. Users should use this method to send messages.
     * @param payload The message payload
     * @param channelIndex The channel index to send the message on
     * @param target The target address of the message
     */
    inline void send(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target) { 
        this->enqueue(payload, channelIndex, target); 
    };

    /**
     * @brief Log a message if logging is enabled
     * @param log The log message
     */
    void log(const std::string& log);
    
public:
    /**
     * @brief Constructor for the Device class
     * @param addr The address of the device
     * @param en The environment this device belongs to
     */
    explicit Device(ADDR_TYPEDEF addr, Environment* en);

    /**
     * @brief Simulate the behavior of the device after receiving a message.
     * @param msg The message received
     * @param channelIndex The index of the channel the message was received on
     */
    virtual void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex);

    /**
     * @brief Get the address of the device
     * @return The address of the device
     */
    inline ADDR_TYPEDEF getAddr() const { return this->addr; };

    /**
     * @brief Set the device to listen to a specific channel
     * @param channelIndex The channel to listen to
     */
    void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex);

    /**
     * @brief Set the busy state of the device
     * @param v The new busy state
     */
    void setBusy(bool v);

    /**
     * @brief Set the waiting state of the device
     * @param v The new waiting state
     */
    void setWaiting(bool v);

    /**
     * @brief Set the callback function for when the busy state changes
     * @param callback The callback function
     */
    inline void setOnBusyChanged(std::function<void(bool)> callback) { this->onBusyChanged = callback; }

    /**
     * @brief Set the callback function for when the waiting state changes
     * @param callback The callback function
     */
    inline void setOnWaitingChanged(std::function<void(bool)> callback) { this->onWaitingChanged = callback; }

    /**
     * @brief Enable or disable logging for the device
     * @param v The logging state
     */
    inline void setLogEnable(bool v){ this->logEnable = v; }

    /**
     * @brief Throw an exception with a given error message
     * @param s The error message
     */
    inline void error(std::string s){ throw std::runtime_error(s); }

};

#endif // __DEVICE_H
