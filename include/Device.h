// include\Device.h

#if !defined(__DEVICE_H)
#define __DEVICE_H

#include "_common.h"

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
    bool logEnable;
    std::queue<std::tuple<std::string, CHANNEL_INDEX_TYPEDEF, ADDR_TYPEDEF>> msgQueue;
    void trueSend(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target);
    void enqueue(std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target);
    void processQueue();

protected:
    inline void send(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target) { 
        this->enqueue(payload, channelIndex, target); 
        };
    void log(const std::string& log);
    
public:
    explicit Device(ADDR_TYPEDEF addr, Environment* en);
    virtual void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex);
    inline ADDR_TYPEDEF getAddr() const { return this->addr; };
    void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex);
    void setBusy(bool v);
    void setWaiting(bool v);
    inline void setOnBusyChanged(std::function<void(bool)> callback) { this->onBusyChanged = callback; }
    inline void setOnWaitingChanged(std::function<void(bool)> callback) { this->onWaitingChanged = callback; }
    inline void setLogEnable(bool v){ this->logEnable = v; }
    inline void error(std::string s){ throw std::runtime_error(s); }

};

#endif // __DEVICE_H
