#include "../include/_common.h"

void Server::msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload) {
    switch (type) {
    case MsgType::LOGIN :
        if(payload == ROBOT_LOGIN_KEY) {
            this->addRobotAddr(senderAddr);
            this->log("Robot login, addr:" + Message::formatAddr(senderAddr) + ", send back login success");
            this->send(MsgType::LOGIN_SUCCESS, SERVER_CHANNEL, senderAddr);
            return;
        }
        if(payload == STATION_LOGIN_KEY) {
            this->addStationAddr(senderAddr);
            this->log("Station login, addr:" + Message::formatAddr(senderAddr));
            return;
        }
        break;
    
    default:
        break;
    }
}