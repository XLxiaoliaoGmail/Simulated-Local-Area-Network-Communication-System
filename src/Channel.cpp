#include "../include/_common.h"

void Channel::occupy(const std::string& msg) {
    this->userNum ++;
    if(userNum > 1) {
        this->isMixed = true;
    }
    this->msg = msg;
}

void Channel::release() {
    if(this->userNum == 0) {
        throw std::runtime_error("Cannot release when userNum = 0");
    }
    this->userNum --;
    if(this->isMixed && userNum == 0) {
        this->isMixed = false;
    }
}