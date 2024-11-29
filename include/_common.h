#if !defined(__COMMON_H)
#define __COMMON_H

#define CHANNEL_COUNTS              8
#define TIME_FORMAT_LENGTH          5
#define DEVICE_INDEX_FORMAT_LENGTH  4
#define TX_DELAY_BASE               10
#define PAYLOAD_MAX_LENGTH          128
#define KEY_LENGTH                  16
#define ADDR_LENGTH                 16
#define DEFAULT_SERVER_CHANNEL      0
#define MSGTYPE_LENGTH_IN_STR       2

#define ROBOT_LOGIN_KEY             "nxqHmTMtnQs6Cr5X"
#define STATION_LOGIN_KEY           "tZnUiIRRYogTv6PG"

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
    LOGIN_SUCCESS,
    NEED_CHARGE,
    HANDSHAKE,
    KEEP_ALIVE,
};

typedef std::string     ADDR_TYPEDEF;
typedef uint8_t         CHANNEL_INDEX_TYPEDEF;
typedef uint64_t        TIME_TYPEDEF;
typedef uint16_t        ROBOT_POWER_TYPEDEF;

class Message;
class Device;
class Environment;
class Channel;
class SimEvent;
class ProtocolDevice;
class Robot;
class Station;
class Server;

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
