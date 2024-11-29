#if !defined(__STATION_H)
#define __STATION_H

#include "_common.h"

class Station : public ProtocolDevice {
private:
    bool occupied;

public:
    explicit Station(ADDR_TYPEDEF addr, Environment* en)
        : ProtocolDevice(addr, en), occupied(false) {
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
    void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload);
    inline void log(const std::string& log) { ProtocolDevice::log("Station", log); }
    // to server
    inline void sendServerLogin(std::string loginKey) {
        this->send(MsgType::LOGIN, loginKey, SERVER_CHANNEL, SERVER_ADDR);
        this->log("Try to send login");
    }
};

#endif // __STATION_H
