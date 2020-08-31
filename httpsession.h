#pragma once
#include <vector>
#include "session.h"
#include "httpserver.h"
#include <string.h>
#include <thread>
#include <sstream>
#include <iostream>

#define DEFAULT_BUFLEN 512
// Các lệnh cơ bản trong http-request
#define GET  "GET"
#define HEAD  "HEAD"
#define POST  "POST"
#define PUT  "PUT"
#define DELETE  "DELETE"
#define OPTION  "OPTION"
#define CONNECT  "CONNECT"
#define TRACE  "TRACE"

class Response
{
public:
    string status_line;
    string header;
    string body;
public:
    Response();

};


class HTTPSession : public Session
{
public:
    Response response;
    void End();
public:
    HTTPSession(TcpSocket* slave);

    ~HTTPSession();
    string getResponse();
    bool GetStatus();
    void doGet(char* cmd_argv[], int cmd_argc);
    void doQuit(char* cmd_argv[], int cmd_argc);
    void doHead(char* cmd_argv[], int cmd_argc);
    void doPost(char* cmd_argv[], int cmd_argc);
    void doPut(char* cmd_argv[], int cmd_argc);
    void doDelete(char* cmd_argv[], int cmd_argc);
    void doConnect(char* cmd_argv[], int cmd_argc);
    void doTrace(char* cmd_argv[], int cmd_argc);
    void doOption(char* cmd_argv[], int cmd_argc);
};
