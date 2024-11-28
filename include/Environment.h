#if !defined(__ENVIRONMENT_H)
#define __ENVIRONMENT_H

#include "_common.h"

class Environment {
private:
    bool running;
    std::vector<Device*> devices;
    TIME_TYPEDEF time;
    std::unordered_map<TIME_TYPEDEF, std::vector<std::function<void()>>> eventsAtCertainTick;
    Channel channels[CHANNEL_COUNTS];

public:
    explicit Environment();
    Device* getDeviceByIndex(ADDR_TYPEDEF addr);
    Device* addDevice();
    void broadcast(const std::string& message, ADDR_TYPEDEF senderAddr, uint8_t channelIndex);
    void update();
    void registerEvent(TIME_TYPEDEF happenTick, std::function<void()> event);
    inline void delayEvent(TIME_TYPEDEF delayTick, std::function<void()> event) { this->registerEvent(this->time + delayTick, event); };
    void log(const std::string& log);
    inline TIME_TYPEDEF getTime() const { return time; }
    void endAt(TIME_TYPEDEF time);
    void stopRun();
    void run();
};

#endif // __ENVIRONMENT_H
