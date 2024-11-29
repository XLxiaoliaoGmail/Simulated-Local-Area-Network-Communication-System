#if !defined(__STATION_H)
#define __STATION_H

#include "_common.h"

class Station : public ProtocolDevice {
private:
    bool occupied;

public:
    explicit Station(ADDR_TYPEDEF addr, Environment* en)
        : ProtocolDevice(addr, en), occupied(false) {
    }
};

#endif // __STATION_H
