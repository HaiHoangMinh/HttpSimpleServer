#pragma once
#include <fstream>
#include <string.h>
#include "tcpserver.h"
#include "httpsession.h"

class Request
{
public:
    string Method;
    string URI;
    string header;
    string body;
    Request();
    Request (string&,string&,string&);
public:
    string getMethod();
    string getURI();
    string getHead();
};


class HTTPServer: public TCPServer
{
public:
    Request request;
    string check;
    int body_length;
    string body;
    string res;
public:
    HTTPServer(unsigned short port = 8080);
    ~HTTPServer();
    public:
    virtual void startNewSession(TcpSocket* slave);
    int checkRequest(TcpSocket* slave, char* buffer, int buflen); // đọc cú pháp request
    unsigned short getRequest(char *sCmdBuf, int len, char * cmd_argv[], int& cmd_argc); // Phân tích cú pháp Request
    void getResource(TcpSocket* slave); // Lấy tài nguyên từ server
    void initCmd();

};



