#include "../include/_common.h"

void Environment::broadcast(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex, TIME_TYPEDEF sendingTime) {
    if(channelIndex >= CHANNEL_COUNTS) {
        this->error("channelIndex too large");
    }
    this->channels[channelIndex].occupy(msg);

    this->delayEvent(sendingTime, [this, channelIndex](){
        if(!this->channels[channelIndex].isMixed()) {
            std::srand(std::time(0));
            const Channel& ch = this->channels[channelIndex];
            const Message* msg = ch.getMsg();
            for(auto d : ch.getListeners()) {
                // different signal propagation time
                this->delayEvent(std::rand() % 10 + 1, [d, msg, channelIndex](){
                    d->recieve(msg, channelIndex);
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
        event->emit();
    }
}

SimEvent* Environment::registerEvent(TIME_TYPEDEF tick, std::function<void()> callback) {
    SimEvent* event = new SimEvent(this, tick, callback);
    this->eventsAtCertainTick[tick].push_back(event);
    return event;
}

void Environment::endAt(TIME_TYPEDEF time) {
    this->registerEvent(time, [this](){
        this->stopRun();
    });
}

void Environment::log(const std::string& log) {
    std::cout << "[" 
              << std::setw(TIME_FORMAT_LENGTH) << std::setfill('0') << this->time
              << "][E]:"
              << log
              << std::endl;
}

void Environment::stopRun() {
    this->running = false;
}

void Environment::run() {
    this->running = true;
    this->log("Start simulating");
    while(this->running) {
        this->update();
    }
    this->log("Stop successfully");
}