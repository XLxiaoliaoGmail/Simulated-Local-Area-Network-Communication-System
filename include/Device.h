// include\Device.h

#if !defined(__DEVICE_H)
#define __DEVICE_H

#include <unordered_map>
#include "_common.h"
#include "Environment.h"

// class Environment;
class Device {
private:
    ADDR_TYPEDEF addr;
    Environment* en;
    TIME_TYPEDEF txDelay;
    bool busy;
    CHANNEL_INDEX_TYPEDEF listeningIndex;
public:
    explicit Device(ADDR_TYPEDEF addr, Environment* en);
    ADDR_TYPEDEF getId() const;
    void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex);
    void detectMsg(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex);
    void sendMsg(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex);
    void log(const std::string& log);
};

#endif // __DEVICE_H
