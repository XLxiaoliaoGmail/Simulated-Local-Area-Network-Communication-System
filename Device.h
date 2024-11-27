#if !defined(__DEVICE_H)
#define __DEVICE_H

typedef uint16_t ADDR_TYPEDEF;

class Device {
private:
    ADDR_TYPEDEF addr;
public:
    explicit Device(ADDR_TYPEDEF addr, Environment* en);
    ADDR_TYPEDEF getId() const;
    void getMsg(const String& message);
};

#endif // __DEVICE_H
