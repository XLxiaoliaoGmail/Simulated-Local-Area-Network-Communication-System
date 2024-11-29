#include "../include/_common.h"

void Channel::occupy(const Message* msg) {
    this->userNum ++;
    if(userNum > 1) {
        this->mixed = true;
    }
    this->msg = msg;
}

void Channel::release() {
    if(this->userNum == 0) {
        throw std::runtime_error("Cannot release when userNum = 0");
    }
    this->userNum --;
    if(this->mixed && userNum == 0) {
        this->mixed = false;
    }
}
