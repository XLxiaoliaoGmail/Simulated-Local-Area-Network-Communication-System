#include "../include/_common.h"

Station::Station(ADDR_TYPEDEF addr, Environment* en, POSITION_UNIT_TYPEDEF x, POSITION_UNIT_TYPEDEF y) : 
    ProtocolDevice(addr, en), 
    occupied(false), 
    x(x),
    y(y),
    chargingBotAddr(NOWHERE_ADDR) {
    this->setOnWaitingChanged([this](bool waiting){
        if(waiting) {
            this->log("Channel occupied, wiating ...");
        } else {
            this->log("Message sent");
        }
    });
}

void Station::login(std::string loginKey) {
    this->sendToServer(MsgType::X_SERVER_LOGIN, loginKey, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        this->loginSuccess = true;
        this->log("Login succecssfully");
        this->updateFreeToServer(true);
        this->updatePositionToServer();

        // msg listener
        this->on(MsgType::SERVER_X_CHARGE_HANDSHAKE_INFO, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
            std::string handshakeKey = payload;
            // listen to handshake from bot
            this->log("Listen for handshakeKey:" + handshakeKey);
            this->once(
                MsgType::BOT_STATION_CHARGE_HANDSHAKE, 
                [this, handshakeKey](ADDR_TYPEDEF senderAddr, const std::string & payload){
                    if(handshakeKey == payload){
                        this->log("Handshake successfully with bot:" + Message::addrToHexString(senderAddr));
                        this->setOccupied(true);
                        this->send(
                            MsgType::BOT_STATION_CHARGE_HANDSHAKE,
                            MSG_STATUS_TRUE,
                            MAIN_CHANNEL,
                            senderAddr
                        );
                        this->chargingBotAddr = senderAddr;
                    } else {
                        this->error("Handshake error");
                    }
            });
        });

        this->on(MsgType::BOT_STATION_CHARGE_KEEPALIVE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
            if(this->chargingBotAddr == NOWHERE_ADDR){
                return;
            }
            if(senderAddr != this->chargingBotAddr){
                this->error("senderAddr != this->chargingBotAddr");
            }
            if(payload == MSG_STATUS_TRUE){
                // keep alive
                this->send(
                    MsgType::BOT_STATION_CHARGE_KEEPALIVE,
                    MSG_STATUS_TRUE,
                    MAIN_CHANNEL,
                    senderAddr
                );
                this->log("Recieve keep alive");
            }
            if(payload == MSG_STATUS_FALSE){
                // stop charging
                this->chargingBotAddr = NOWHERE_ADDR;
                this->log("Recieve stop charging");
                this->setOccupied(false);
            }
        });
    });
    this->log("Try to send X_SERVER_LOGIN");
}

void Station::updateFreeToServer(bool free) {
    this->sendToServer(MsgType::STATION_SERVER_FREE_UPDATE, free?MSG_STATUS_TRUE:MSG_STATUS_FALSE, [this, free](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        if(payload == MSG_STATUS_TRUE){
            this->log("Update status to server succecssfully, current status: " + std::string(free?"free":"occupied"));
        } else {
            // error handler
        }
    });
    this->log("Try to send STATION_SERVER_FREE_UPDATE");
}

void Station::updatePositionToServer() {
    this->sendToServer(
        MsgType::STATION_SERVER_POSITION_UPDATE, 
        Message::positionToHexString(this->x, this->y), 
        [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        if(payload == MSG_STATUS_TRUE){
            this->log("Update position to server succecssfully, current position: x[" + Message::uintToHexString(this->getX(), POSITION_UNIT_FORMAT_LENGTH) + "] y[" + Message::uintToHexString(this->getY(), POSITION_UNIT_FORMAT_LENGTH) +"]" );
        } else {
            // error handler
        }
    });
    this->log("Try to send STATION_SERVER_POSITION_UPDATE");
}