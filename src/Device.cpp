#include "../include/_common.h"

Device::Device(ADDR_TYPEDEF addr, Environment* en) : addr(addr), en(en) {}

ADDR_TYPEDEF Device::getId() const {
    return this->addr;
}

void Device::getMsg(const std::string& msg, uint8_t channelIndex) {
    log("rx <- " + msg);
}

void Device::sendMsg(const std::string& msg, uint8_t channelIndex) {
    log("tx -> " + msg);
    this->en->broadcast(msg, this->addr, channelIndex);
}

void Device::log(const std::string& log) {
    std::cout << "[" 
              << std::setw(TIME_FORMAT_LENGTH) << std::setfill('0') << this->en->getTime()
              << "][D]:"
              << log
              << std::endl;
}