#include "../include/_common.h"

Robot::Robot(ADDR_TYPEDEF addr, Environment* en) : 
    ProtocolDevice(addr, en), 
    needCharging(false),
    loginSuccess(false),
    power(100),
    chargingStationAddr(NOWHERE_ADDR) {
    this->setOnWaitingChanged([this](bool waiting){
        if(waiting) {
            this->log("Channel occupied, wiating ...");
        } else {
            this->log("Message sent");
        }
    });
    this->on(MsgType::BOT_STATION_CHARGE_KEEPALIVE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(this->chargingStationAddr == NOWHERE_ADDR){
            return;
        }
        if(this->chargingStationAddr != senderAddr){
            this->error("this->chargingStationAddr != senderAddr");
        }
        if(payload == MSG_STATUS_TRUE) {
            this->chagingUp();
            this->log("Charging up, now power = " + std::to_string(this->getPower()));
            if(this->getPower() >= 100){
                // charging finish
                this->sendPowerFinish(senderAddr);
            }else{
                this->keepAliveWhenCharging();
            }
        }
    });
}

void Robot::login(std::string loginKey) {
    this->sendToServer(MsgType::X_SERVER_LOGIN, loginKey, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        this->loginSuccess = true;
        this->log("Login succecssfully");
    });
    this->log("Try to send login");
}

void Robot::needCharge() {
    // assume that power is low
    this->power = 0;
    this->sendToServer(MsgType::BOT_SERVER_NEED_CHARGE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        if(payload.length() != POSITION_UNIT_FORMAT_LENGTH + POSITION_UNIT_FORMAT_LENGTH) {
            this->error("Position str length cannot match");
        }
        Position pos = Message::hexStringToPosition(payload);
        this->gotoPosition(pos);

        // set up listener
        this->once(MsgType::SERVER_X_CHARGE_HANDSHAKE_INFO, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
            if(payload.length() != HANDSHAKE_KEY_LENGTH + ADDR_FORMAT_LENGTH){
                this->error("Payload length error");
            }
            std::string handshakeKey = payload.substr(0, HANDSHAKE_KEY_LENGTH);
            ADDR_TYPEDEF stationAddr = Message::hexStringToUint(payload.substr(HANDSHAKE_KEY_LENGTH, ADDR_FORMAT_LENGTH));
            
            this->log("Get charge info, key:" + handshakeKey + ", stationAddr:" + payload.substr(HANDSHAKE_KEY_LENGTH, ADDR_FORMAT_LENGTH));
            // start handshake
            this->sendHandshakeToStation(handshakeKey, stationAddr, MAIN_CHANNEL);
        });
    });
    this->log("Try to send need charge");
}

void Robot::sendHandshakeToStation(std::string handshakeKey, ADDR_TYPEDEF stationAddr, CHANNEL_INDEX_TYPEDEF channelIndex){
    this->send(
        MsgType::BOT_STATION_CHARGE_HANDSHAKE,
        handshakeKey,
        MAIN_CHANNEL, 
        stationAddr, 
        [this, stationAddr](ADDR_TYPEDEF senderAddr, const std::string & payload) {
            if(stationAddr != senderAddr){
                this->error("stationAddr != senderAddr");
            }
            if(payload == MSG_STATUS_TRUE){
                this->log("Handshake successfully to station:" + Message::addrToHexString(senderAddr));
                this->chargingStationAddr = senderAddr;
                this->keepAliveWhenCharging();
            } else {
                this->error("Handshake error");
            }
    });
    this->log("Send handshakeKey to station");
}

inline void Robot::keepAliveWhenCharging(){
    this->log("Send keep alive");
    this->send(
        MsgType::BOT_STATION_CHARGE_KEEPALIVE, 
        MSG_STATUS_TRUE,
        MAIN_CHANNEL, 
        this->chargingStationAddr);
}

inline void Robot::sendPowerFinish(ADDR_TYPEDEF stationAddr){
    this->send(
        MsgType::BOT_STATION_CHARGE_KEEPALIVE, 
        MSG_STATUS_FALSE,
        MAIN_CHANNEL, 
        stationAddr
    );
}