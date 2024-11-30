#if !defined(__LOCATION_H)
#define __LOCATION_H

#include "_common.h"

class Location {
    LOCATION_UNIT_TYPEDEF x;
    LOCATION_UNIT_TYPEDEF y;
    explicit Location(LOCATION_UNIT_TYPEDEF x, LOCATION_UNIT_TYPEDEF y) : x(x), y(y) {}

    inline std::string toString(){
        return Message::uintToHexString(x, LOCATION_UNIT_FORMAT_LENGTH) + Message::uintToHexString(y, LOCATION_UNIT_FORMAT_LENGTH);
    }
    static inline Location* fromString(std::string s){
        if(s.length() != (LOCATION_UNIT_FORMAT_LENGTH + LOCATION_UNIT_FORMAT_LENGTH)){
            throw std::runtime_error("Location string length error");
        }
        return new Location(Message::hexStringToUint(s.substr(0,8)), Message::hexStringToUint(s.substr(8,8)));
    }
};

#endif // __LOCATION_H
