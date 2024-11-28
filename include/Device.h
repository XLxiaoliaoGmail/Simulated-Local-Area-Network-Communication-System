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
public:
    explicit Device(ADDR_TYPEDEF addr, Environment* en);
    ADDR_TYPEDEF getId() const;
    void getMsg(const std::string& msg, uint8_t channelIndex);
    void sendMsg(const std::string& msg, uint8_t channelIndex);
    void log(const std::string& log);
};

#endif // __DEVICE_H
