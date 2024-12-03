/**
 * @file Channel.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-02
 * 
 * 
 */
#if !defined(__CHANNEL_H)
#define __CHANNEL_H

#include "_common.h"

/**
 * @class Channel
 * @brief This class simulates a communication channel in the local network, supporting message transmission
 *        and device listening mechanisms. It emulates real-world wireless local network characteristics, including
 *        channel occupation and signal interference. An Environment instance may contain multiple Channels. When
 *        a Device sends a message to a Channel and the message is not interfered with, it will be broadcast to all
 *        Devices listening to that Channel.
 */
class Channel {
private:
    uint8_t userNum; ///< The number of Devices currently using this Channel
    bool mixed; ///< Whether the message on this Channel is mixed with other messages
    const Message* msg; ///< The message currently on this Channel
    std::list<Device*> listeners; ///< The list of Devices currently listening to this Channel

public:
    /**
     * @brief Constructor of Channel
     */
    explicit Channel() : userNum(0), mixed(false) {}

    /**
     * @brief Occupy the Channel with a message. If the Channel is not occupied, the message will be broadcast to all Devices listening to this Channel.
     * @param msg The message to be occupied
     */
    void occupy(const Message* msg);

    /**
     * @brief Release the Channel from the message occupied. If the Channel is not occupied, this function has no effect.
     */
    void release();

    /**
     * @brief Add a Device to the list of Devices listening to this Channel
     * @param device The Device to be added
     */
    inline void addListener(Device* device){ this->listeners.push_back(device); };

    /**
     * @brief Remove a Device from the list of Devices listening to this Channel
     * @param device The Device to be removed
     */
    inline void removeListener(Device* device){ this->listeners.remove(device); }

    /**
     * @brief Check if the Channel is occupied
     * @return true if the Channel is occupied, false otherwise
     */
    inline bool isBusy() const { return this->userNum > 0; }

    /**
     * @brief Check if the message on this Channel is mixed with other messages
     * @return true if the message is mixed, false otherwise
     */
    inline bool isMixed() const { return this->mixed; }

    /**
     * @brief Get the message currently on this Channel
     * @return The message on this Channel
     */
    inline const Message* getMsg() const { return this->msg; }

    /**
     * @brief Get the list of Devices currently listening to this Channel
     * @return The list of Devices listening to this Channel
     */
    inline std::list<Device*> getListeners() const { return this->listeners; }

    /**
     * @brief Throw an exception with a given error message
     * @param message The error message
     */
    inline void error(std::string message){ throw std::runtime_error(message); }
};

#endif // __CHANNEL_H
