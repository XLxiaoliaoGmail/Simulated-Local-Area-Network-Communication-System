#include "../include/_common.h"

uint64_t _generateRandomUInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);
    return dis(gen); // 返回生成的随机数
}

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
        server->setRobotLoginKey(ROBOT_X_SERVER_LOGIN_KEY);
        server->setStationLoginKey(STATION_X_SERVER_LOGIN_KEY);

        // setup robots
        for(uint16_t i=0; i<10; i++) {
            auto robot = new Robot(addrCount++, en);
            robot->setLogEnable(true);
            robots.push_back(robot);
            robot->login(ROBOT_X_SERVER_LOGIN_KEY);
        }

        // setup stations
        for(uint16_t i=0; i<10; i++) {
            auto station = new Station(addrCount++, en, _generateRandomUInt(), _generateRandomUInt());
            station->setLogEnable(true);
            stations.push_back(station);
            station->login(STATION_X_SERVER_LOGIN_KEY);
        }
    })->then(5000, [en, &robots, &stations](){
        // assume that a robot out of power
        robots[0]->needCharge();
    });

    en->endAt(10000);
    en->run();
}

int main() {
    #ifdef _DEBUG
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
