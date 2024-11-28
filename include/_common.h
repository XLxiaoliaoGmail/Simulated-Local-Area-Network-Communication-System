#if !defined(__COMMON_H)
#define __COMMON_H

#define CHANNEL_COUNTS      8
#define TIME_FORMAT_LENGTH  5
#define TX_DELAY_BASE       10

#include <cstdint>
#include <functional>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <format>

typedef uint16_t ADDR_TYPEDEF;
typedef uint8_t CHANNEL_INDEX_TYPEDEF;
typedef uint64_t TIME_TYPEDEF;

class Device;
class Environment;
class Channel;

#include "Channel.h"
#include "Device.h"
#include "Environment.h"

#endif // __COMMON_H
