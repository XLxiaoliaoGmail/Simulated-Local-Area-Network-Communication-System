#if !defined(__CHANNEL_H)
#define __CHANNEL_H

#include "_common.h"

class Channel {
public:
    uint8_t userNum;
    bool isMixed;
    std::string msg;

    explicit Channel() : userNum(0), isMixed(false), msg("") {}
    void occupy(const std::string& msg);
    void release();
};

#endif // __CHANNEL_H

