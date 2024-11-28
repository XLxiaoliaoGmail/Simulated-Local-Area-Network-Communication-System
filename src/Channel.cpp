#include "../include/_common.h"

void Channel::occupy(const std::string& msg) {
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

void Channel::removeListener(const Device* d) {
    auto it = std::find(this->listeners.begin(), this->listeners.end(), d);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}