#if !defined(__COMMON_H)
#define __COMMON_H

#define CHANNEL_COUNTS              8
#define TX_DELAY_BASE               10
#define PAYLOAD_MAX_LENGTH          128

#define KEY_FORMAT_LENGTH           16
#define TIME_FORMAT_LENGTH          5
#define ADDR_FORMAT_LENGTH          4
#define LOCATION_UNIT_FORMAT_LENGTH 8

#define ADDR_LENGTH_IN_MSG          4
#define SERVER_CHANNEL              0

#define NOWHERE_ADDR                0
#define SERVER_ADDR                 1

#define MSGTYPE_LENGTH_IN_STR       2

#define ROBOT_LOGIN_KEY             "nxqHmTMtnQs6Cr5X"
#define STATION_LOGIN_KEY           "tZnUiIRRYogTv6PG"

#define MSG_STATUS_TRUE             "1"
#define MSG_STATUS_FALSE            "0"

#include <cstdint>
#include <queue>
#include <functional>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <format>
#include <list>
#include <sstream>

enum MsgType : uint8_t {
    LOGIN,

    BOT_NEED_CHARGE,

    STATION_FREE_UPDATE,
    STATION_LOCATION_UPDATE,
};

typedef uint16_t        ADDR_TYPEDEF;
typedef uint8_t         CHANNEL_INDEX_TYPEDEF;
typedef uint64_t        TIME_TYPEDEF;
typedef uint16_t        ROBOT_POWER_TYPEDEF;
typedef uint32_t        LOCATION_UNIT_TYPEDEF;

class Location;
class Message;
class Device;
class Environment;
class Channel;
class SimEvent;
class ProtocolDevice;
class Robot;
class Station;
class Server;

#include "Location.h"
#include "Message.h"
#include "SimEvent.h"
#include "Channel.h"
#include "Device.h"
#include "Environment.h"

#include "ProtocolDevice.h"
#include "Robot.h"
#include "Station.h"
#include "Server.h"

#endif // __COMMON_H
