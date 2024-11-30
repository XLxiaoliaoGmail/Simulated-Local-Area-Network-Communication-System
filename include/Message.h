#if !defined(__MESSSAGE_H)
#define __MESSSAGE_H

#include "_common.h"

class Message {
public:
    std::string sender;
    std::string target;
    std::string payload;
    explicit Message(ADDR_TYPEDEF sender, ADDR_TYPEDEF target, std::string payload):
        sender(Message::uintToHexString(sender, ADDR_LENGTH_IN_MSG)), 
        target(Message::uintToHexString(target, ADDR_LENGTH_IN_MSG)), 
        payload(payload) {

        if(payload.length() > PAYLOAD_MAX_LENGTH){
            throw std::runtime_error("Payload length too large");
        }
    };
    static std::string uintToHexString(uint64_t num, uint16_t len) {
        std::ostringstream oss;
        oss << std::setw(len)
            << std::setfill('0')
            << std::hex
            << num;
        return oss.str();
    }
    static uint64_t hexStringToUint(const std::string& addrStr) {
        ADDR_TYPEDEF addr;
        std::istringstream iss(addrStr);
        iss >> std::hex >> addr;
        if (iss.fail()) {
            throw std::runtime_error("Invalid address format");
        }
        return addr;
    }
};

#endif // __MESSSAGE_H
