#include "../include/_common.h"

SimEvent::SimEvent(Environment* en, TIME_TYPEDEF emitTick, std::function<void()> callback) : 
    emitTick(emitTick), 
    callback(callback),
    en(en) 
    {};

void SimEvent::emit() {
    this->callback();
}

SimEvent* SimEvent::then(TIME_TYPEDEF delayTime, std::function<void()> callback) {
    return this->en->registerEvent(this->emitTick + delayTime, callback);
}