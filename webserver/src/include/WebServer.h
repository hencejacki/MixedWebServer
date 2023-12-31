#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include <vector>
#include <map>

#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include "Log.h"
#include "ThreadPool.h"

class EventLoop;
class Channel;
class WebServer
{
private:
    EventLoop *_mainReactor;
    std::vector<EventLoop*> _subReactors;
    ThreadPool *_pool;

    Acceptor *_acceptor;
    std::map<int, Connection*> _map;

    std::string _srcDir;

    std::function<void(Connection*)> _on_connect_callback;
    
    void handleConnection(Socket*);

    void deleteConnection(Socket*);

    // void handleReadEvent(int sockFd);

public:
    explicit WebServer(uint16_t port, const char *dbHost, const unsigned int dbPort, const char *dbUser, const char *dbPwd, const char *dbName, int connPoolNums, bool openLog = true, int logLevel = 1, int logSize = 0);
    ~WebServer();

    void start();

    void OnConnect(std::function<void(Connection*)> const &cb);
};
#endif  // _WEBSERVER_H