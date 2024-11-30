#include "../include/_common.h"

Station::Station(ADDR_TYPEDEF addr, Environment* en, Location loc) : 
    ProtocolDevice(addr, en), 
    occupied(false), 
    location(loc) {
    this->setOnWaitingChanged([this](bool waiting){
        if(waiting) {
            this->log("Channel occupied, wiating ...");
        } else {
            this->log("Message sent");
        }
    });
    // this->setOnBusyChanged([this](bool busy){
    //     if(!busy) {
    //         this->log("Message sent");
    //     }
    // });
}

void Station::login(std::string loginKey) {
    this->sendToServer(MsgType::LOGIN, loginKey, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        this->loginSuccess = true;
        this->log("Login succecssfully");
        this->updateFreeToServer(true);
    });
    this->log("Try to send LOGIN");
}

void Station::updateFreeToServer(bool free) {
    this->sendToServer(MsgType::STATION_FREE_UPDATE, free?MSG_STATUS_TRUE:MSG_STATUS_FALSE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        if(payload == MSG_STATUS_TRUE){
            this->log("Update status to succecssfully");
        } else {
            // error handler
        }
    });
    this->log("Try to send STATION_FREE_UPDATE");
}

void Station::updateLocationToServer() {
    this->sendToServer(MsgType::STATION_LOCATION_UPDATE, free?MSG_STATUS_TRUE:MSG_STATUS_FALSE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        if(payload == MSG_STATUS_TRUE){
            this->log("Update status to succecssfully");
        } else {
            // error handler
        }
    });
    this->log("Try to send STATION_FREE_UPDATE");
}