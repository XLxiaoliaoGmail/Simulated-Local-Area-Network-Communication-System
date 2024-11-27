#include <iostream>
#include <vector>
#include <string>
#include "Environment.h"
#include "Device.h"
#include "common.h"

class Device {
private:
    ADDR_TYPEDEF addr;
    Environment* en;

public:
    explicit Device(ADDR_TYPEDEF addr, Environment* en):
        addr(addr),
        en(en) {
    }

    ADDR_TYPEDEF getId() const {
        return addr;
    }

    void getMsg(const String& msg) {
        std::cout << "Device " << addr << " received message: " << msg << std::endl;
    }

    void sendMsg(const String& msg) {
        en->broadcast(msg, addr);
        log("send -> " + msg);
    }

    void log(const String& log) {
        std::cout << "[0x" << std::hex << addr << "]:" << log << std::endl;
    }
};