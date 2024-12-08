/**
 * @file Environment.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__ENVIRONMENT_H)
#define __ENVIRONMENT_H

#include "_common.h"

/**
 * @class Environment
 * @brief This class simulates a network environment. It manages devices, channels, and events within the environment.
 *        The environment allows devices to communicate via channels, and events can be scheduled and executed at specific times.
 */
class Environment {
private:
    bool running; ///< Indicates if the simulated environment is currently running
    std::vector<Device*> devices; ///< List of devices in the environment
    TIME_TYPEDEF time; ///< The current time in the environment
    std::unordered_map<TIME_TYPEDEF, std::vector<SimEvent*>> eventsAtCertainTick; ///< A map of events scheduled for specific times
    Channel channels[CHANNEL_COUNTS]; ///< An array of channels in the environment

public:
    /**
     * @brief Constructor of the Environment class
     * Initializes the environment with default values.
     */
    explicit Environment() : running(false), time(0) {};

    /**
     * @brief Add a device to the environment
     * @param d The device to be added
     */
    inline void addDevice(Device* d){ this->devices.push_back(d); };

    /**
     * @brief Broadcast a message to all devices on a specific channel
     * @param msg The message to be broadcasted
     * @param channelIndex The index of the channel on which to broadcast the message
     * @param sendingTime The time at which the message is sent
     */
    void broadcast(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex, TIME_TYPEDEF sendingTime);

    /**
     * @brief Update the environment, processing events and updating the state of devices and channels.
     */
    void update();

    /**
     * @brief Register an event to be executed at a specific time
     * @param tick The time tick at which the event will be executed
     * @param callback The callback function to be executed at the event's time
     * @return A pointer to the registered event
     */
    SimEvent* registerEvent(TIME_TYPEDEF tick, std::function<void()> callback);

    /**
     * @brief Delay an event by a certain number of ticks, registers an event to be executed after a certain delay from the current time.
     * @param delayTick The number of ticks to delay the event
     * @param callback The callback function to be executed after the delay
     * @return A pointer to the delayed event
     */
    inline SimEvent* delayEvent(TIME_TYPEDEF delayTick, std::function<void()> callback){ 
        return this->registerEvent(this->time + delayTick, callback); 
    };

    /**
     * @brief Print log in console
     * @param log The message to be logged
     */
    void log(const std::string& log);

    /**
     * @brief Get the current time in the environment
     * @return The current time
     */
    inline TIME_TYPEDEF getTime() const { return time; };

    /**
     * @brief End the simulation at a specific time
     * @param time The time at which to end the simulation
     */
    void endAt(TIME_TYPEDEF time);

    /**
     * @brief Stop the simulation from running
     */
    void stopRun();

    /**
     * @brief Run the simulation
     */
    void run();

    /**
     * @brief Get the channels in the environment
     * @return A pointer to the array of channels
     */
    inline Channel* getChannels(){ return this->channels; };

    /**
     * @brief Throw an exception with a given error message
     * @param s The error message
     */
    inline void error(std::string s){ throw std::runtime_error(s); }
};

#endif // __ENVIRONMENT_H
