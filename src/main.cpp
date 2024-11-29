#include "../include/_common.h"

#define __DEBUG_MODE

void run() {
    auto en = new Environment();
    std::vector<Robot*> robots;
    std::vector<Station*> stations;

    en->registerEvent(10, [en, &robots, &stations](){
        // simulation environment

        // setup server
        ADDR_TYPEDEF addrCount = SERVER_ADDR;
        auto server = new Server(addrCount++, en);
        server->setLogEnable(true);
        server->setRobotLoginKey(ROBOT_LOGIN_KEY);
        server->setStationLoginKey(STATION_LOGIN_KEY);

        // setup robots
        for(uint16_t i=0; i<10; i++) {
            auto robot = new Robot(addrCount++, en);
            robot->setLogEnable(true);
            robots.push_back(robot);
            robot->sendServerLogin(ROBOT_LOGIN_KEY);
        }

        // setup stations
        for(uint16_t i=0; i<10; i++) {
            auto station = new Station(addrCount++, en);
            station->setLogEnable(true);
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
