#include "../include/_common.h"

Device::Device(ADDR_TYPEDEF addr, Environment* en) : 
    txDelay(TX_DELAY_BASE), 
    addr(addr), 
    en(en), 
    busy(false),
    listeningIndex(0) 
    {
        this->log("listening to channel[0]");
    }

ADDR_TYPEDEF Device::getId() const {
    return this->addr;
}


void Device::detectMsg(const std::string& msg, CHANNEL_INDEX_TYPEDEF channelIndex) {
    log("rx <- " + msg);
}

void Device::sendMsg(const std::string& msg, CHANNEL_INDEX_TYPEDEF channelIndex) {
    if(channelIndex >= CHANNEL_COUNTS) {
        throw std::runtime_error("channelIndex too large");
    }
    if(this->en->getChannels()[channelIndex].isBusy()) {
        this->en->delayEvent(this->txDelay, [this, msg, channelIndex]() {
            this->sendMsg(msg, channelIndex);
        });
        log("ch[" + std::to_string(channelIndex) + "] occupied, waiting for [" + std::to_string(this->txDelay) + "] ticks");
        this->txDelay += this->txDelay;
    } else {
        if(this->txDelay != TX_DELAY_BASE) {
            this->txDelay = TX_DELAY_BASE;
        }
        log("tx[" + std::to_string(channelIndex) + "] -> " + msg);
        this->busy = true;
        const TIME_TYPEDEF sendingTime = msg.length() + 16;
        this->en->broadcast(msg, this->addr, channelIndex, sendingTime);
        en->delayEvent(sendingTime, [this](){
            this->busy = false;
        });
    }
}

void Device::listenTo(CHANNEL_INDEX_TYPEDEF channelIndex) {
    if(channelIndex >= CHANNEL_COUNTS) {
        throw std::runtime_error("channelIndex too large");
    }
    if(channelIndex != this->listeningIndex) {
        this->en->getChannels()[this->listeningIndex].removeListener(this);
        this->listeningIndex = channelIndex;
        this->en->getChannels()[channelIndex].addListener(this);
        this->log("listening to channel[" + std::to_string(channelIndex) + "]");
    }
}

void Device::log(const std::string& log) {
    std::cout << "[" 
              << std::setw(TIME_FORMAT_LENGTH) << std::setfill('0') << this->en->getTime()
              << "][D]:"
              << log
              << std::endl;
}