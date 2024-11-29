#if !defined(__CHANNEL_H)
#define __CHANNEL_H

#include "_common.h"

class Channel {
private:
    uint8_t userNum;
    bool mixed;
    const Message* msg;
    std::list<Device*> listeners;

public:
    explicit Channel() : userNum(0), mixed(false) {}
    void occupy(const Message* msg);
    void release();
    inline void addListener(Device* d){ this->listeners.push_back(d); };
    inline void removeListener(Device* d){ this->listeners.remove(d); }
    inline bool isBusy() const { return this->userNum > 0; }
    inline bool isMixed() const { return this->mixed; }
    inline const Message* getMsg() const { return this->msg; }
    inline std::list<Device*> getListeners() const { return this->listeners; }
};

#endif // __CHANNEL_H

