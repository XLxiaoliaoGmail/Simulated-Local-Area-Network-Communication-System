#if !defined(__ROBOT_H)
#define __ROBOT_H

#include "_common.h"

class Robot : public ProtocolDevice {
private:
    bool needCharging;
    bool loginSuccess;
    POWER_TYPEDEF power;
    ADDR_TYPEDEF chargingStationAddr;

public:
    explicit Robot(ADDR_TYPEDEF addr, Environment* en);
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }
    inline void log(const std::string& log) { ProtocolDevice::log("Robot", log); }
    inline void gotoPosition(Position pos){
        this->log("Move to position :" + Message::positionToHexString(pos.x, pos.y) );
    }
    inline void chagingUp(){ this->power += 20; }
    inline POWER_TYPEDEF getPower() const { return this->power; }
    // to server
    void login(std::string loginKey);
    void needCharge();
    inline void sendToServer(MsgType type, const std::string payload) {
        ProtocolDevice::send(type, payload, MAIN_CHANNEL, SERVER_ADDR);
    }
    inline void sendToServer(MsgType type){
        ProtocolDevice::send(type, MAIN_CHANNEL, SERVER_ADDR);
    }
    inline void sendToServer(MsgType type, const std::string payload, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        ProtocolDevice::send(type, payload, MAIN_CHANNEL, SERVER_ADDR, callback);
    }
    inline void sendToServer(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback){
        ProtocolDevice::send(type, MAIN_CHANNEL, SERVER_ADDR, callback);
    }
    // to station
    void sendHandshakeToStation(std::string handShakey, ADDR_TYPEDEF stationAddr, CHANNEL_INDEX_TYPEDEF channelIndex);
    inline void keepAliveWhenCharging();
    inline void sendPowerFinish(ADDR_TYPEDEF stationAddr);
};

#endif // __ROBOT_H
