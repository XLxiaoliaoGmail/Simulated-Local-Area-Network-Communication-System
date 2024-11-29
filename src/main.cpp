#include "../include/_common.h"

#define __DEBUG_MODE

void run() {
    auto en = new Environment();
    std::vector<Robot*> robots;
    std::vector<Station*> stations;

    en->registerEvent(10, [en, &robots, &stations](){
        // simulation environment

        // setup server
        uint16_t addrCount = 0;
        auto server = new Server(std::to_string(addrCount++), en);
        server->setLogEnable(true);
        server->setRobotLoginKey(ROBOT_LOGIN_KEY);
        server->setStationLoginKey(STATION_LOGIN_KEY);

        // setup robots
        for(uint16_t i=0; i<10; i++) {
            auto robot = new Robot(std::to_string(addrCount++), en);
            robots.push_back(robot);
            robot->sendServerLogin(ROBOT_LOGIN_KEY);
        }

        // setup stations
        for(uint16_t i=0; i<10; i++) {
            auto station = new Station(std::to_string(addrCount++), en);
            stations.push_back(station);
            station->sendServerLogin(STATION_LOGIN_KEY);
        }
    });

    en->endAt(10000);
    en->run();
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
