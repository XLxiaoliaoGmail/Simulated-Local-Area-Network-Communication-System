#include "../include/_common.h"

void Server::msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload) {
    switch (type) {
    case MsgType::LOGIN :
        if(payload == ROBOT_LOGIN_KEY) {
            this->addRobotAddr(senderAddr);
            this->log("Robot login, addr:" + senderAddr);
            this->send(MsgType::LOGIN_SUCCESS, senderAddr, DEFAULT_SERVER_CHANNEL);
            return;
        }
        if(payload == STATION_LOGIN_KEY) {
            this->addStationAddr(senderAddr);
            this->log("Station login, addr:" + senderAddr);
            return;
        }
        break;
    
    default:
        break;
    }
}