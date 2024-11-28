#include "../include/_common.h"

int main() {
    Environment en;
    std::vector<Device*> devices;
    for (uint8_t i = 1; i <= 10; ++i) {
        devices.push_back(en.addDevice());
    }
    
    en.registerEvent(10, [devices](){
        devices[2]->sendMsg("hello world", 1);
    });

    en.endAt(1000);
    en.run();

    return 0;
}
