#if !defined(__ENVIRONMENT_H)
#define __ENVIRONMENT_H

#include "_common.h"

class Environment {
private:
    bool running;
    std::vector<Device*> devices;
    TIME_TYPEDEF time;
    std::unordered_map<TIME_TYPEDEF, std::vector<SimEvent*>> eventsAtCertainTick;
    Channel channels[CHANNEL_COUNTS];

public:
    explicit Environment() : running(false), time(0) {};

    inline void addDevice(Device* d){ this->devices.push_back(d); };
    void broadcast(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex, TIME_TYPEDEF sendingTime);
    void update();
    SimEvent* registerEvent(TIME_TYPEDEF tick, std::function<void()> callback);
    inline SimEvent* delayEvent(TIME_TYPEDEF delayTick, std::function<void()> callback){ return this->registerEvent(this->time + delayTick, callback); };
    void log(const std::string& log);
    inline TIME_TYPEDEF getTime() const { return time; };
    void endAt(TIME_TYPEDEF time);
    void stopRun();
    void run();
    inline Channel* getChannels(){ return this->channels; };
};

#endif // __ENVIRONMENT_H
