#include "../include/_common.h"

int main() {
    Environment en;
    std::vector<Device*> devices;
    for (uint8_t i = 1; i <= 3; ++i) {
        devices.push_back(en.addDevice());
    }
    
    en.registerEvent(10, [devices](){
        devices[2]->sendMsg("this is d2", 0);
    });
    
    en.registerEvent(100, [devices](){
        devices[3]->listenTo(3);
    });
    
    en.registerEvent(200, [devices](){
        devices[1]->sendMsg("this is d1", 0);
    });

    en.endAt(1000);
    en.run();

    return 0;
}
