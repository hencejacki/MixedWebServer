#ifndef _CHANNEL_H
#define _CHANNEL_H
#include <sys/epoll.h>
#include <functional>

class EventLoop;
class Channel
{
private:
    EventLoop *_loop;
    int _fd;
    uint32_t _events;
    uint32_t _revents;
    bool _inPoll;

    std::function<void()> _writeCallback;
    std::function<void()> _readCallback;

public:
    Channel(EventLoop*, int);
    ~Channel();

    void enableReading();
    void EnableWriting();
    void useET();
    uint32_t getEvents();
    void SetRevents(uint32_t);
    uint32_t GetRevents();
    bool isInPoll();
    void setInPoll();
    int getFd();

    void setReadCallback(std::function<void()> const &cb);
    void setWriteCallback(std::function<void()> const &cb);
    void handleEvent();
};

#endif  // _CHANNEL_H