#include "../include/_common.h"

StationData* Server::getFreeStation() {
    for(const auto& [addr, stationData] : this->stationsInfo){
        if(stationData->free == true){
            return stationData;
        }
    }
    return nullptr;
}

Server::Server(ADDR_TYPEDEF addr, Environment* en) : 
    ProtocolDevice(addr, en),
    robotLoginKey(16, 'x'),
    stationLoginKey(16, 'x') {
    this->setOnWaitingChanged([this](bool waiting){
        if(waiting) {
            this->log("Channel occupied, wiating ...");
        } else {
            this->log("Message sent");
        }
    });
    this->on(MsgType::LOGIN, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(payload == ROBOT_LOGIN_KEY) {
            this->addRobotAddr(senderAddr);
            this->log("Robot login, addr:" + Message::uintToHexString(senderAddr) + ", send back login success");
            this->send(MsgType::LOGIN, SERVER_CHANNEL, senderAddr);
            return;
        }
        if(payload == STATION_LOGIN_KEY) {
            this->addStationAddr(senderAddr);
            this->log("Station login, addr:" + Message::uintToHexString(senderAddr) + ", send back login success");
            this->send(MsgType::LOGIN, SERVER_CHANNEL, senderAddr);
            return;
        }
    });
    this->on(MsgType::STATION_FREE_UPDATE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(!isStation(senderAddr)){
            return;
        }
        if(payload == MSG_STATUS_TRUE){
            this->setStationStatus(senderAddr, true);
        } else if(payload == MSG_STATUS_FALSE){
            this->setStationStatus(senderAddr, false);
        }
        this->send(MsgType::STATION_FREE_UPDATE, MSG_STATUS_TRUE, SERVER_CHANNEL, senderAddr);
    });
    this->on(MsgType::BOT_NEED_CHARGE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(!isRobot(senderAddr)){
            return;
        }
        StationData* freeStation = this->getFreeStation();
        if(freeStation){
            this->send(MsgType::BOT_NEED_CHARGE, MSG_STATUS_FALSE, SERVER_CHANNEL, senderAddr);
        } else {
            
        }
    });
}