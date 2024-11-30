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
    this->on(MsgType::X_SERVER_LOGIN, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(payload == ROBOT_X_SERVER_LOGIN_KEY) {
            this->addRobotAddr(senderAddr);
            this->log("Robot login, addr:" + Message::uintToHexString(senderAddr, ADDR_FORMAT_LENGTH) + ", send back login success");
            this->send(MsgType::X_SERVER_LOGIN, MAIN_CHANNEL, senderAddr);
            return;
        }
        if(payload == STATION_X_SERVER_LOGIN_KEY) {
            this->addStationAddr(senderAddr);
            this->log("Station login, addr:" + Message::uintToHexString(senderAddr, ADDR_FORMAT_LENGTH) + ", send back login success");
            this->send(MsgType::X_SERVER_LOGIN, MAIN_CHANNEL, senderAddr);
            return;
        }
    });
    this->on(MsgType::STATION_SERVER_FREE_UPDATE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(!isStation(senderAddr)){
            return;
        }
        if(payload == MSG_STATUS_TRUE){
            this->setStationStatus(senderAddr, true);
        } else if(payload == MSG_STATUS_FALSE){
            this->setStationStatus(senderAddr, false);
        }
        this->send(MsgType::STATION_SERVER_FREE_UPDATE, MSG_STATUS_TRUE, MAIN_CHANNEL, senderAddr);
    });
    this->on(MsgType::BOT_SERVER_NEED_CHARGE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(!isRobot(senderAddr)){
            return;
        }
        StationData* freeStation = this->getFreeStation();
        if(!freeStation){
            // if no found
            this->send(MsgType::BOT_SERVER_NEED_CHARGE, MSG_STATUS_FALSE, MAIN_CHANNEL, senderAddr);
        } else {
            this->send(MsgType::BOT_SERVER_NEED_CHARGE, Message::positionToHexString(freeStation->x, freeStation->y), MAIN_CHANNEL, senderAddr);
            std::string handshakeKey = Message::generateRandomString(HANDSHAKE_KEY_LENGTH);
            
            // send key to station
            // must send to listener first
            this->send(MsgType::SERVER_X_CHARGE_HANDSHAKE_INFO, 
                handshakeKey, 
                MAIN_CHANNEL, 
                freeStation->addr, 
                [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
                    // call back handler
            });
            this->log("Send station handshake key");
            
            // send key and addr to bot
            this->send(MsgType::SERVER_X_CHARGE_HANDSHAKE_INFO, 
                handshakeKey + Message::addrToHexString(freeStation->addr), 
                MAIN_CHANNEL, 
                senderAddr, 
                [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
                    // call back handler
            });
            this->log("Send bot handshake key" + handshakeKey);
        }
    });
    this->on(MsgType::STATION_SERVER_POSITION_UPDATE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(!isStation(senderAddr)){
            return;
        }
        if(payload.length() != POSITION_UNIT_FORMAT_LENGTH + POSITION_UNIT_FORMAT_LENGTH){
            this->error("Position length cannot match");
        }
        this->stationsInfo[senderAddr]->x = Message::hexStringToUint(payload.substr(0,8));
        this->stationsInfo[senderAddr]->y = Message::hexStringToUint(payload.substr(8,8));
        this->send(MsgType::STATION_SERVER_POSITION_UPDATE, MSG_STATUS_TRUE, MAIN_CHANNEL, senderAddr);
    });
}