#if !defined(__ProtocolDevice_H)
#define __ProtocolDevice_H

#include "_common.h"

class ProtocolDevice : public Device{
public:
    explicit ProtocolDevice(ADDR_TYPEDEF addr, Environment* en) : Device(this->formatAddrStr(addr), en) {}
    std::string formatKeyStr(const std::string& key){
        auto format = key;
        if (format.length() < KEY_LENGTH) {
            format.insert(0, KEY_LENGTH - format.length(), 'x');
        } else if (format.length() > KEY_LENGTH) {
            format = format.substr(0, KEY_LENGTH);
        }
        return format;
    }
    std::string formatAddrStr(const std::string& addr){
        auto format = addr;
        if (format.length() < ADDR_LENGTH) {
            format.insert(0, KEY_LENGTH - format.length(), 'x');
        } else if (format.length() > ADDR_LENGTH) {
            format = format.substr(0, ADDR_LENGTH);
        }
        return format;
    }
    std::string MsgTypeToHexString(MsgType num) {
        std::stringstream ss;
        ss << std::hex << std::setw(MSGTYPE_LENGTH_IN_STR) << std::setfill('0') << static_cast<int>(num);
        return ss.str();
    }

    inline MsgType hexStringToMsgType(const std::string& hexStr) {
        return static_cast<MsgType>(std::stoi(hexStr));
    }
    inline void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex) {
        Device::send(MsgTypeToHexString(type) + payload, channelIndex);
    }
    inline void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex){
        Device::send(MsgTypeToHexString(type), channelIndex);
    }
    virtual void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload) = 0;
    inline void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex) override {
        this->msgHandler(msg->sender, hexStringToMsgType(msg->payload.substr(0,MSGTYPE_LENGTH_IN_STR)), msg->payload.substr(MSGTYPE_LENGTH_IN_STR));
    };
    inline void log(const std::string& who, const std::string& log) {
        Device::log("[" + who + "]" + log);
    };
};

#endif // __ProtocolDevice_H
