#include "../include/_common.h"

Robot::Robot(ADDR_TYPEDEF addr, Environment* en) : 
    ProtocolDevice(addr, en), 
    needCharging(false),
    loginSuccess(false) {
    this->setOnWaitingChanged([this](bool waiting){
        if(waiting) {
            this->log("Channel occupied, wiating ...");
        } else {
            this->log("Message sent");
        }
    });
}

void Robot::login(std::string loginKey) {
    this->sendToServer(MsgType::LOGIN, loginKey, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
        this->loginSuccess = true;
        this->log("Login succecssfully");
    });
    this->log("Try to send login");
}

void Robot::needCharge() {
    this->sendToServer(MsgType::BOT_NEED_CHARGE, [this](ADDR_TYPEDEF senderAddr, const std::string & payload){
        if(senderAddr != SERVER_ADDR) {
            return;
        }
    });
    this->log("Try to send need charge");
}