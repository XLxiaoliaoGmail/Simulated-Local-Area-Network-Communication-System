#if !defined(__EVENT_H)
#define __EVENT_H

#include "_common.h"

class SimEvent {
private:
    TIME_TYPEDEF emitTick;
    std::function<void()> callback;
    Environment* en;

public:
    explicit SimEvent(Environment* en, TIME_TYPEDEF emitTick, std::function<void()> callback);
    SimEvent* then(TIME_TYPEDEF delayTime, std::function<void()> callback);
    void emit();
    inline TIME_TYPEDEF getEmitTick() const { return this->emitTick; }
};

#endif // __EVENT_H
