#if !defined(__CHANNEL_H)
#define __CHANNEL_H

#include "_common.h"

class Channel {
private:
    uint8_t userNum;
    bool mixed;
    std::string msg;
    std::vector<Device*> listeners;

public:
    explicit Channel() : userNum(0), mixed(false), msg("") {}
    void occupy(const std::string& msg);
    void release();
    inline void addListener(Device* d){ listeners.push_back(d); };
    void removeListener(const Device* d);
    inline bool isBusy() const { return this->userNum > 0; }
    inline bool isMixed() const { return this->mixed; }
    inline std::string getMsg() const { return this->msg; }
    inline std::vector<Device*> getListeners() const { return this->listeners; }
};

#endif // __CHANNEL_H

