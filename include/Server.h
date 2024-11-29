#if !defined(__SERVER_H)
#define __SERVER_H

#include "_common.h"

class Server : public ProtocolDevice {
private:
    std::vector<ADDR_TYPEDEF> robotsAddr;
    std::vector<ADDR_TYPEDEF> stationsAddr;
    std::string robotLoginKey;
    std::string stationLoginKey;

public:
    explicit Server(ADDR_TYPEDEF addr, Environment* en) : 
        ProtocolDevice(addr, en),
        robotLoginKey(16, 'x'),
        stationLoginKey(16, 'x') {
            this->log("Default listen to ch[" + std::to_string(DEFAULT_SERVER_CHANNEL) + "]");
        }
    inline void setRobotLoginKey(const std::string& key){ 
        this->robotLoginKey = this->formatKeyStr(key);
        this->log("Set up robot login key successfully, key:" + key) ;
    }
    inline void setStationLoginKey(const std::string& key){ 
        this->stationLoginKey = this->formatKeyStr(key); 
        this->log("Set up station login key successfully, key:" + key) ;
    }
    inline void addRobotAddr(ADDR_TYPEDEF addr){ this->robotsAddr.push_back(addr); }
    inline void addStationAddr(ADDR_TYPEDEF addr){ this->stationsAddr.push_back(addr); }
    inline void sendProtocol(MsgType type, const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex) {}
    void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload) override;
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }
    inline void log(const std::string& log) { ProtocolDevice::log("Server", log); }
};

#endif // __SERVER_H
