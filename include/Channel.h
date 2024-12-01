/**
 * @file Channel.h
 * @brief Header file for the Channel class, managing communication between devices.
 * 
 * The Channel class provides mechanisms to manage message passing and device listeners.
 * It supports occupancy control, listener management, and error handling.
 */

#ifndef __CHANNEL_H
#define __CHANNEL_H

#include "_common.h"

/**
 * @class Channel
 * @brief Represents a communication channel between devices.
 * 
 * The Channel class manages occupancy, device listeners, and communication messages.
 * It tracks whether the channel is currently in use, supports message assignment, 
 * and allows listeners to be added or removed.
 */
class Channel {
private:
    uint8_t userNum;         ///< Number of users occupying the channel.
    bool mixed;              ///< Flag indicating if the channel is mixed.
    const Message* msg;      ///< Pointer to the current message on the channel.
    std::list<Device*> listeners;   ///< List of devices listening to the channel.

public:
    /**
     * @brief Default constructor for the Channel class.
     * Initializes the channel to an unoccupied state with no listeners.
     */
    explicit Channel() : userNum(0), mixed(false) {}

    /**
     * @brief Occupy the channel with a message.
     * 
     * This method sets the channel's message and marks the channel as occupied.
     * 
     * @param msg The message to occupy the channel with.
     */
    void occupy(const Message* msg);

    /**
     * @brief Release the channel.
     * 
     * This method releases the channel, clearing the message and allowing 
     * other users to occupy the channel.
     */
    void release();

    /**
     * @brief Add a listener device to the channel.
     * 
     * This method adds a device to the channel's listener list.
     * 
     * @param d Pointer to the device to be added as a listener.
     */
    inline void addListener(Device* d) { this->listeners.push_back(d); };

    /**
     * @brief Remove a listener device from the channel.
     * 
     * This method removes a device from the channel's listener list.
     * 
     * @param d Pointer to the device to be removed from the listener list.
     */
    inline void removeListener(Device* d) { this->listeners.remove(d); }

    /**
     * @brief Check if the channel is currently occupied.
     * 
     * This method checks if the channel is currently in use by a user.
     * 
     * @return True if the channel is occupied, false otherwise.
     */
    inline bool isBusy() const { return this->userNum > 0; }

    /**
     * @brief Check if the channel is mixed.
     * 
     * This method checks if the channel is mixed, as indicated by the `mixed` flag.
     * 
     * @return True if the channel is mixed, false otherwise.
     */
    inline bool isMixed() const { return this->mixed; }

    /**
     * @brief Get the current message on the channel.
     * 
     * This method retrieves the current message stored on the channel.
     * 
     * @return A pointer to the current message.
     */
    inline const Message* getMsg() const { return this->msg; }

    /**
     * @brief Get the list of listener devices on the channel.
     * 
     * This method retrieves the list of devices currently listening to the channel.
     * 
     * @return A list of devices listening to the channel.
     */
    inline std::list<Device*> getListeners() const { return this->listeners; }

    /**
     * @brief Handle an error and throw an exception.
     * 
     * This method is used to throw an exception with the given error message.
     * 
     * @param s The error message to be thrown.
     * @throws std::runtime_error An exception with the provided error message.
     */
    inline void error(std::string s) { throw std::runtime_error(s); }
};

#endif // __CHANNEL_H
