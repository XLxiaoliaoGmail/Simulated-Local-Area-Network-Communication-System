#if !defined(__ENVIRONMENT_H)
#define __ENVIRONMENT_H

class Environment
{
public:
    explicit Environment();
    void addDevice();
    void broadcast(const String& message, ADDR_TYPEDEF senderAddr);
};


#endif // __ENVIRONMENT_H
