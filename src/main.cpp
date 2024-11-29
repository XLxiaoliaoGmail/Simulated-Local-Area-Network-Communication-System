#include "../include/_common.h"

#define __DEBUG_MODE

void run() {
    Environment en;
    std::vector<Device*> devices;
    for (uint8_t i = 1; i <= 3; ++i) {
        devices.push_back(en.addDevice());
    }
    
    auto t1 = en.registerEvent(10, [devices](){
        devices[2]->sendMsg("this is d2", 0);
    });
    t1->then(100, [devices](){
        devices[0]->listenTo(3);
    })->then(100, [devices](){
        devices[1]->sendMsg("this is d1", 0);
    })->then(1, [devices](){
        devices[2]->sendMsg("this is d1", 0);
    });
    
    en.endAt(1000);
    en.run();
}

int main() {
    #ifdef __DEBUG_MODE
    try {
        run();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
    #else
        run();
    #endif
    
    return 0;
}
