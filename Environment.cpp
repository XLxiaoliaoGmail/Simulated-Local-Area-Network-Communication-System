#include <iostream>
#include <vector>
#include "Device.h"
#include "common.h"

class Environment {
private:
    std::vector<Device*> devices;
public:
    explicit Environment() {

    }

    void addDevice() {
        devices.push_back(new Device(devices.size(), this));
    }

    void broadcast(const String& message, ADDR_TYPEDEF senderAddr) {
        for (Device* device : devices) {
            if (device->getId() != senderAddr) {
                device->getMsg(message);
            }
        }
    }
};