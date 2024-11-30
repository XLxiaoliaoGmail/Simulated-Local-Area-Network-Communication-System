#if !defined(__STATION_H)
#define __STATION_H

#include "_common.h"

class Station : public ProtocolDevice {
private:
    bool occupied;
    bool loginSuccess;
    Location location;

public:
    explicit Station(ADDR_TYPEDEF addr, Environment* en, Location location);
    inline void log(const std::string& log) { ProtocolDevice::log("Station", log); }
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
    // to server
    void login(std::string loginKey);
    void updateFreeToServer(bool free);
    void updateLocationToServer();
};

#endif // __STATION_H
