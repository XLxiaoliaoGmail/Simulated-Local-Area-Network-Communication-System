#if !defined(__MESSSAGE_H)
#define __MESSSAGE_H

#include "_common.h"

class Message {
public:
    std::string sender;
    std::string target;
    std::string payload;
    explicit Message(ADDR_TYPEDEF sender, ADDR_TYPEDEF target, std::string payload):
        sender(Message::formatAddr(sender)), 
        target(Message::formatAddr(target)), 
        payload(payload) {

        if(payload.length() > PAYLOAD_MAX_LENGTH){
            throw std::runtime_error("Payload length too large");
        }
    };
    static std::string formatAddr(ADDR_TYPEDEF addr) {
        std::ostringstream oss;
        oss << std::setw(ADDR_LENGTH_IN_MSG)
            << std::setfill('0')
            << std::hex
            << addr;
        return oss.str();
    }
    static ADDR_TYPEDEF parseAddr(const std::string& addrStr) {
        ADDR_TYPEDEF addr;
        std::istringstream iss(addrStr);
        iss >> std::hex >> addr;  // 以十六进制方式解析字符串
        if (iss.fail()) {
            throw std::runtime_error("Invalid address format");
        }
        return addr;
    }
};

#endif // __MESSSAGE_H
