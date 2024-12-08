/**
 * @file Message.h
 * @author XLxiaoliao (xlxiaoliao@gmail.com)
 * @brief 
 * @version beta
 * @date 2024-12-08
 * 
 * 
 */
#if !defined(__MESSSAGE_H)
#define __MESSSAGE_H

#include "_common.h"

/**
 * @class Message
 * @brief This class represents a message that is sent from a sender to a target with a payload.
 *        It also includes utility methods to convert between different formats (such as hexadecimal and string)
 *        and to generate random strings.
 */
class Message {
public:
    std::string sender; ///< The address of the sender in hexadecimal format
    std::string target; ///< The address of the target in hexadecimal format
    std::string payload; ///< The message content (payload)

    /**
     * @brief Constructor for the Message class. The payload length is checked to ensure it does not exceed the maximum length.
     * @param sender The address of the sender
     * @param target The address of the target
     * @param payload The content of the message
     */
    explicit Message(ADDR_TYPEDEF sender, ADDR_TYPEDEF target, std::string payload) :
        sender(Message::uintToHexString(sender, ADDR_FORMAT_LENGTH)), 
        target(Message::uintToHexString(target, ADDR_FORMAT_LENGTH)), 
        payload(payload) {

        if (payload.length() > PAYLOAD_MAX_LENGTH) {
            this->error("Payload length too large");
        }
    };

    /**
     * @brief Throws a runtime exception with a given error message
     * @param s The error message
     */
    static inline void error(std::string s) {
        throw std::runtime_error(s);
    }

    /**
     * @brief Generates a random alphanumeric string of a specified length
     * @param length The length of the random string to generate
     * @return A random string of the specified length
     */
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

    /**
     * @brief Converts a position (x, y) to a hexadecimal string representation
     * @param x The x-coordinate of the position
     * @param y The y-coordinate of the position
     * @return The position as a hexadecimal string
     */
    static inline std::string positionToHexString(POSITION_UNIT_TYPEDEF x, POSITION_UNIT_TYPEDEF y) {
        return Message::uintToHexString(x, POSITION_UNIT_FORMAT_LENGTH) + 
               Message::uintToHexString(y, POSITION_UNIT_FORMAT_LENGTH);
    }

    /**
     * @brief Converts an address to a hexadecimal string representation
     * @param addr The address to be converted
     * @return The address as a hexadecimal string
     */
    static inline std::string addrToHexString(ADDR_TYPEDEF addr) {
        return Message::uintToHexString(addr, ADDR_FORMAT_LENGTH);
    }

    /**
     * @brief Converts a hexadecimal string representation of a position to a Position object
     * @param s The hexadecimal string representing the position
     * @return A Position object corresponding to the hexadecimal string
     */
    static inline Position hexStringToPosition(std::string s) {
        if (s.length() != POSITION_UNIT_FORMAT_LENGTH + POSITION_UNIT_FORMAT_LENGTH) {
            Message::error("Position hex string length cannot match");
        }
        Position pos;
        pos.x = Message::hexStringToUint(s.substr(0, POSITION_UNIT_FORMAT_LENGTH));
        pos.y = Message::hexStringToUint(s.substr(POSITION_UNIT_FORMAT_LENGTH, POSITION_UNIT_FORMAT_LENGTH));
        return pos;
    }

    /**
     * @brief Converts a 64-bit unsigned integer to a hexadecimal string representation
     * @param num The number to be converted
     * @param len The length of the resulting hexadecimal string
     * @return The number as a hexadecimal string
     */
    static std::string uintToHexString(uint64_t num, uint16_t len) {
        std::ostringstream oss;
        oss << std::setw(len)
            << std::setfill('0')
            << std::hex
            << num;
        return oss.str();
    }

    /**
     * @brief Converts a hexadecimal string representation of an address to a 64-bit unsigned integer
     * @param addrStr The hexadecimal string representing the address
     * @return The address as a 64-bit unsigned integer
     */
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
