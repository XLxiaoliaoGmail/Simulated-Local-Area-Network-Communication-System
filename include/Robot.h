#if !defined(__ROBOT_H)
#define __ROBOT_H

#include "_common.h"

class Robot : public ProtocolDevice {
private:
    bool needCharging;

public:
    explicit Robot(ADDR_TYPEDEF addr, Environment* en) : ProtocolDevice(addr, en), needCharging(false) {
        this->setOnWaitingChanged([this](bool waiting){
            if(waiting) {
                this->log("Channel occupied, wiating ...");
            }
        });
        this->setOnBusyChanged([this](bool busy){
            if(!busy) {
                this->log("Message sent");
            }
        });
    }
    inline void powerOn(){}
    inline void moveToStation(){}
    void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload);
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }
    inline void log(const std::string& log) { ProtocolDevice::log("Robot", log); }
    // to server
    inline void sendServerLogin(std::string loginKey) {
        this->send(MsgType::LOGIN, loginKey, SERVER_CHANNEL, SERVER_ADDR);
        this->log("Try to send login");
    }
};

#endif // __ROBOT_H
