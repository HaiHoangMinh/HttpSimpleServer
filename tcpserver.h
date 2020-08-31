#ifndef SERVER_H__
#define SERVER_H__
// Base class for generic TCP server
#include "tcpserversocket.h"
#include "session.h"

class TCPServer
{
protected:
    TcpServerSocket master;
    bool running;
    bool autoStart;
    bool logging;
    unsigned short port;
    unsigned short numCmd;
    string  cmdNameList[SERVER_CMD_MAX_NUM];
    CMD_FUNC cmdDoFunc[SERVER_CMD_MAX_NUM];
    string logFileName;
private:

public:
    TCPServer(unsigned short localPort);
    virtual ~TCPServer();
    bool start();
    void stop();
    bool restart();
    bool isRunning();
    bool getAutoStart() {return autoStart;}
    bool getLogging() {return logging;}
    const string& getLogFileName() const {return logFileName;}
protected:
    void run();
    virtual void startNewSession(TcpSocket* slave)=0;
    virtual void configServer(const string& confFileName);
    virtual void loadServerConfig(const string& confFileName);
    void addCmd(const string& cmdName,CMD_FUNC f);
    // void setAutoStart(bool autostart) {autoStart = autostart;}
    void doCmd(Session* session,uint8_t cmdId, char* cmdArgv[], int cmdArgc);
    virtual void initCmd();
};

#endif // SERVER_H_INCLUDED
