#include "../include/_common.h"

Environment::Environment() {
    this->time = 0;
    this->running = true;
}

Device* Environment::getDeviceByIndex(ADDR_TYPEDEF addr) {
    return devices[addr]; 
}

Device* Environment::addDevice() {
    Device* d = new Device(devices.size(), this);
    devices.push_back(d);
    return d;
}

void Environment::broadcast(const std::string& msg, ADDR_TYPEDEF senderAddr, uint8_t channelIndex) {
    TIME_TYPEDEF sendingTime = msg.length() + 16; // 16 is length of address
    if(channelIndex >= CHANNEL_COUNTS) {
        throw std::runtime_error("channelIndex too large");
    }
    this->channels[channelIndex].occupy(msg);

    this->delayEvent(sendingTime, [this, channelIndex](){
        if(!this->channels[channelIndex].isMixed) {
            std::srand(std::time(0));
            for(auto d : this->devices) {
                // different signal propagation time
                this->delayEvent(std::rand() % 10 + 1, [d, this, channelIndex](){
                    d->getMsg(this->channels[channelIndex].msg, channelIndex);
                });
            }
        }
        this->channels[channelIndex].release();
    });
}

void Environment::update() {
    this->time ++;
    if(this->eventsAtCertainTick.count(this->time) == 0)
        return;
    for(auto event : this->eventsAtCertainTick.at(this->time)) {
        event();
    }
}

void Environment::registerEvent(TIME_TYPEDEF happenTick, std::function<void()> event) {
    this->eventsAtCertainTick[happenTick].push_back(event);
}

void Environment::log(const std::string& log) {
    std::cout << "[" 
              << std::setw(TIME_FORMAT_LENGTH) << std::setfill('0') << this->time
              << "][E]:"
              << log
              << std::endl;
}

void Environment::endAt(TIME_TYPEDEF time) {
    this->registerEvent(time, [this](){
        this->stopRun();
    });
}

void Environment::stopRun() {
    this->running = false;
}

void Environment::run() {
    while(this->running) {
        this->update();
    }
    this->log("Stop successfully");
}

