#if !defined(__MESSSAGE_H)
#define __MESSSAGE_H

#include "_common.h"

class Message {
public:
    ADDR_TYPEDEF sender;
    std::string payload;
    explicit Message(ADDR_TYPEDEF sender, std::string payload):sender(sender), payload(payload) {
        if(payload.length() > PAYLOAD_MAX_LENGTH){
            throw std::runtime_error("Payload length too large");
        }
    };
};

#endif // __MESSSAGE_H
