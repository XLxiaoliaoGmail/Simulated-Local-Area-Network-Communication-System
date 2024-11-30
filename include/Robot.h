#if !defined(__ROBOT_H)
#define __ROBOT_H

#include "_common.h"

class Robot : public ProtocolDevice {
private:
    bool needCharging;
    bool loginSuccess;

public:
    explicit Robot(ADDR_TYPEDEF addr, Environment* en);
    inline void powerOn(){}
    inline void moveToStation(){}
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }
    inline void log(const std::string& log) { ProtocolDevice::log("Robot", log); }
    // to server
    void login(std::string loginKey);
    void needCharge();
    inline void sendToServer(MsgType type, const std::string payload) {
        ProtocolDevice::send(type, payload, SERVER_CHANNEL, SERVER_ADDR);
    }
    inline void sendToServer(MsgType type){
        ProtocolDevice::send(type, SERVER_CHANNEL, SERVER_ADDR);
    }
    inline void sendToServer(MsgType type, const std::string payload, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        ProtocolDevice::send(type, payload, SERVER_CHANNEL, SERVER_ADDR, callback);
    }
    inline void sendToServer(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback){
        ProtocolDevice::send(type, SERVER_CHANNEL, SERVER_ADDR, callback);
    }
};

#endif // __ROBOT_H
