#if !defined(__MESSSAGE_H)
#define __MESSSAGE_H

#include "_common.h"

class Message {
public:
    std::string sender;
    std::string target;
    std::string payload;
    explicit Message(ADDR_TYPEDEF sender, ADDR_TYPEDEF target, std::string payload):
        sender(Message::uintToHexString(sender, ADDR_FORMAT_LENGTH)), 
        target(Message::uintToHexString(target, ADDR_FORMAT_LENGTH)), 
        payload(payload) {

        if(payload.length() > PAYLOAD_MAX_LENGTH){
            this->error("Payload length too large");
        }
    };
    static inline void error(std::string s){ throw std::runtime_error(s); }
    static std::string generateRandomString(uint16_t length) {
        const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::random_device rd; 
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, characters.size() - 1);

        std::string randomStr;
        for (size_t i = 0; i < length; ++i) {
            randomStr += characters[dis(gen)];
        }

        return randomStr;
    }
    static inline std::string positionToHexString(POSITION_UNIT_TYPEDEF x, POSITION_UNIT_TYPEDEF y){
        return Message::uintToHexString(x, POSITION_UNIT_FORMAT_LENGTH) + Message::uintToHexString(y, POSITION_UNIT_FORMAT_LENGTH);
    }
    static inline std::string addrToHexString(ADDR_TYPEDEF addr){
        return Message::uintToHexString(addr, ADDR_FORMAT_LENGTH);
    }
    static inline Position hexStringToPosition(std::string s){
        if(s.length() != POSITION_UNIT_FORMAT_LENGTH + POSITION_UNIT_FORMAT_LENGTH){
            Message::error("Position hex string length cannot match");
        }
        Position pos;
        pos.x = Message::hexStringToUint(s.substr(0, POSITION_UNIT_FORMAT_LENGTH));
        pos.y = Message::hexStringToUint(s.substr(POSITION_UNIT_FORMAT_LENGTH, POSITION_UNIT_FORMAT_LENGTH));
        return pos;
    }
    static std::string uintToHexString(uint64_t num, uint16_t len) {
        std::ostringstream oss;
        oss << std::setw(len)
            << std::setfill('0')
            << std::hex
            << num;
        return oss.str();
    }
    static uint64_t hexStringToUint(const std::string& addrStr) {
        uint64_t addr;
        std::istringstream iss(addrStr);
        iss >> std::hex >> addr;
        if (iss.fail()) {
            Message::error("Invalid address format");
        }
        return addr;
    }
};

#endif // __MESSSAGE_H
