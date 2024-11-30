#if !defined(__ProtocolDevice_H)
#define __ProtocolDevice_H

#include "_common.h"

class ProtocolDevice : public Device{
private:
    std::unordered_map<MsgType, std::function<void(ADDR_TYPEDEF, const std::string&)>> callbacks;
    std::unordered_map<MsgType, std::function<void(ADDR_TYPEDEF, const std::string&)>> onceCallbacks;
public:
    explicit ProtocolDevice(ADDR_TYPEDEF addr, Environment* en) : Device(addr, en) {}
    std::string formatKeyStr(const std::string& key){
        auto format = key;
        if (format.length() < KEY_FORMAT_LENGTH) {
            format.insert(0, KEY_FORMAT_LENGTH - format.length(), 'x');
        } else if (format.length() > KEY_FORMAT_LENGTH) {
            format = format.substr(0, KEY_FORMAT_LENGTH);
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
    inline void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target) {
        Device::send(MsgTypeToHexString(type) + payload, channelIndex, target);
    }
    inline void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target){
        Device::send(MsgTypeToHexString(type), channelIndex, target);
    }
    inline void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        Device::send(MsgTypeToHexString(type) + payload, channelIndex, target);
        this->once(type, callback);
    }
    inline void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target, std::function<void(ADDR_TYPEDEF, const std::string&)> callback){
        Device::send(MsgTypeToHexString(type), channelIndex, target);
        this->once(type, callback);
    }
    inline void on(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        this->callbacks[type] = callback;
    }
    inline void once(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback) {
        this->onceCallbacks[type] = callback;
    }
    inline void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload) {
        if(this->onceCallbacks.count(type) != 0) {
            this->onceCallbacks.at(type)(senderAddr, payload);
        }
        if(this->callbacks.count(type) != 0) {
            this->callbacks.at(type)(senderAddr, payload);
        }
    }
    inline void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex) override {
        // just handle msg that target is self
        if(Message::hexStringToUint(msg->target) != this->getAddr()) {
            return;
        }
        this->msgHandler(Message::hexStringToUint(msg->sender), hexStringToMsgType(msg->payload.substr(0,MSGTYPE_LENGTH_IN_STR)), msg->payload.substr(MSGTYPE_LENGTH_IN_STR));
    };
    inline void log(const std::string& who, const std::string& log) {
        Device::log("[" + who + "]" + log);
    };
};

#endif // __ProtocolDevice_H
