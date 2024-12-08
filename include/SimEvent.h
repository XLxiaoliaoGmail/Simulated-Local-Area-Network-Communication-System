/**
 * @file SimEvent.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__EVENT_H)
#define __EVENT_H

#include "_common.h"

/**
 * @class SimEvent
 * @brief Represents a simulation event that can be scheduled to occur at a specific simulation time.
 */
class SimEvent {
private:
    TIME_TYPEDEF emitTick; ///< The tick at which the event will be emitted
    std::function<void()> callback; ///< The callback function to be executed when the event is emitted
    Environment* en; ///< Pointer to the environment where the event is being scheduled

public:
    /**
     * @brief Constructor for the SimEvent class.
     * @param en The environment in which the event is registered
     * @param emitTick The time tick when the event will be emitted
     * @param callback The callback function to be executed when the event is emitted
     */
    explicit SimEvent(Environment* en, TIME_TYPEDEF emitTick, std::function<void()> callback);

    /**
     * @brief Chain another event with a delay. Registers an event to be executed after a specified delay from the current event.
     * @param delayTime The time delay before this event is triggered
     * @param callback The callback function to be executed after the delay
     * @return A pointer to the new event
     */
    SimEvent* then(TIME_TYPEDEF delayTime, std::function<void()> callback);

    /**
     * @brief Emit the event and execute its callback function. User should not call this function
     */
    void emit();

    /**
     * @brief Get the emit time of the event.
     * @return The time tick at which the event is scheduled to be emitted
     */
    inline TIME_TYPEDEF getEmitTick() const { return this->emitTick; }
};

#endif // __EVENT_H
