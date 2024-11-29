#include "../include/_common.h"

Device::Device(ADDR_TYPEDEF addr, Environment* en) : 
    txDelay(TX_DELAY_BASE), 
    addr(addr), 
    en(en), 
    busy(false),
    waiting(false),
    listeningIndex(SERVER_CHANNEL),
    onBusyChanged(nullptr),
    onWaitingChanged(nullptr),
    logEnable(false)
    {
        // this->log("listening to channel[0]");
        en->getChannels()[SERVER_CHANNEL].addListener(this);
        en->addDevice(this);
    }

void Device::setBusy(bool value) {
    if(this->busy != value) {
        this->busy = value;
        if(onBusyChanged) {
            onBusyChanged(value);
        }
    }
}

void Device::setWaiting(bool value) {
    if(this->waiting != value) {
        this->waiting = value;
        if(onWaitingChanged) {
            onWaitingChanged(value);
        }
    }
}

void Device::recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex) {
    log("rx[" + std::to_string(channelIndex) + "] <- " + msg->payload);
}

void Device::listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
    if(channelIndex >= CHANNEL_COUNTS) {
        throw std::runtime_error("channelIndex too large");
    }
    if(channelIndex != this->listeningIndex) {
        this->en->getChannels()[this->listeningIndex].removeListener(this);
        this->listeningIndex = channelIndex;
        this->en->getChannels()[channelIndex].addListener(this);
        // this->log("listening to channel[" + std::to_string(channelIndex) + "]");
    }
}

void Device::trueSend(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target) {
    if(channelIndex >= CHANNEL_COUNTS) {
        throw std::runtime_error("channelIndex too large");
    }
    if(this->en->getChannels()[channelIndex].isBusy()) {
        this->setWaiting(true);
        this->en->delayEvent(this->txDelay, [this, payload, channelIndex, target]() {
            this->trueSend(payload, channelIndex, target);
        });
        this->txDelay += TX_DELAY_BASE;
    } else {
        if(this->txDelay != TX_DELAY_BASE) {
            this->txDelay = TX_DELAY_BASE;
        }
        this->setBusy(true);
        const TIME_TYPEDEF sendingTime = payload.length() + 16;
        this->en->broadcast(new Message(this->addr, target, payload), channelIndex, sendingTime);
        en->delayEvent(sendingTime, [this](){
            this->setBusy(false);
            this->setWaiting(false);
        });
        // send next
        this->processQueue();
    }
}

void Device::enqueue(std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target) {
    this->msgQueue.emplace(payload, channelIndex, target);
    processQueue();
}

void Device::processQueue() {
    if(msgQueue.empty()) {
        return;
    }
    auto [payload, channelIndex, target] = this->msgQueue.front();
    this->msgQueue.pop();
    this->trueSend(payload, channelIndex, target);
}

void Device::log(const std::string& log) {
    if(!this->logEnable) {
        return;
    }
    std::cout << "[" 
              << std::setw(TIME_FORMAT_LENGTH) << std::setfill('0') << this->en->getTime()
              << "][D]["
              << std::setw(DEVICE_INDEX_FORMAT_LENGTH) << std::setfill('0') << this->addr
              << "]:"
              << log
              << std::endl;
}