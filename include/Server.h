#if !defined(__SERVER_H)
#define __SERVER_H

#include "_common.h"

struct RobotData {

    explicit RobotData(){}
};

struct StationData {
    ADDR_TYPEDEF addr;
    bool free;
    POSITION_UNIT_TYPEDEF x;
    POSITION_UNIT_TYPEDEF y;
    explicit StationData(ADDR_TYPEDEF addr) : addr(addr), free(false) {}
};

class Server : public ProtocolDevice {
private:
    std::unordered_map<ADDR_TYPEDEF, RobotData*> robotsInfo;
    std::unordered_map<ADDR_TYPEDEF, StationData*> stationsInfo;
    std::string robotLoginKey;
    std::string stationLoginKey;

public:
    explicit Server(ADDR_TYPEDEF addr, Environment* en);
    inline bool isRobot(ADDR_TYPEDEF addr){
        return this->robotsInfo.count(addr) != 0;
    }
    inline bool isStation(ADDR_TYPEDEF addr){
        return this->stationsInfo.count(addr) != 0;
    }
    StationData* getFreeStation();
    inline void setStationStatus(ADDR_TYPEDEF addr, bool free) {
        if(this->stationsInfo.count(addr) == 0){
            return;
        }
        this->stationsInfo[addr]->free = free;
    }
    inline void setRobotLoginKey(const std::string& key){ 
        this->robotLoginKey = this->formatKeyStr(key);
        this->log("Set up robot login key successfully, key:" + key) ;
    }
    inline void setStationLoginKey(const std::string& key){ 
        this->stationLoginKey = this->formatKeyStr(key); 
        this->log("Set up station login key successfully, key:" + key) ;
    }
    inline void addRobotAddr(ADDR_TYPEDEF addr){ 
        this->robotsInfo[addr] = new RobotData(); 
    }
    inline void addStationAddr(ADDR_TYPEDEF addr){ 
        this->stationsInfo[addr] = new StationData(addr); 
    }
    inline void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::listenTo(channelIndex);
        this->log("Listen to Channel[" + std::to_string(channelIndex) + "]");
    }
    inline void log(const std::string& log) { ProtocolDevice::log("Server", log); }
};

#endif // __SERVER_H
