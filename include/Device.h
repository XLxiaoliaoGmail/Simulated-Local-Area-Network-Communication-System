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
    bool waiting;
    std::function<void(bool)> onBusyChanged;
    std::function<void(bool)> onWaitingChanged;
    CHANNEL_INDEX_TYPEDEF listeningIndex;
protected:
    void send(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex);
    void log(const std::string& log);
    
public:
    explicit Device(ADDR_TYPEDEF addr, Environment* en);
    virtual void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex);
    ADDR_TYPEDEF getId() const;
    void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex);
    void setBusy(bool v);
    void setWaiting(bool v);
    inline void setOnBusyChanged(std::function<void(bool)> callback) { this->onBusyChanged = callback; }
    inline void setOnWaitingChanged(std::function<void(bool)> callback) { this->onWaitingChanged = callback; }
};

#endif // __DEVICE_H
