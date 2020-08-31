#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include "httpsession.h"
#include <ctime>


using namespace std;

Response::Response()
{

}
HTTPSession::HTTPSession(TcpSocket* slave):Session(slave)
{
    this->quitSession = false;

}
void HTTPSession::End()
{

}
HTTPSession::~HTTPSession()
{
    delete slave;
}
string HTTPSession::getResponse()
{
    return this->response.status_line + this->response.header ;
}
bool HTTPSession::GetStatus()
{
        return this->quitSession;
}
void HTTPSession::doGet(char* cmd_argv[], int cmd_argc)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    string s = string(dt);
    response.status_line = "HTTP/1.0 200 OK\r\n";
    string head = "Server: http/1.0\r\nDate:" + s +"Content-Encoding: gzip\r\nContent-Type: text/html\r\nConnection:keep-alive,close\nContent-Length:";
    response.header = head ;
    //slave->send(response.status_line);
    //slave->send(response.header);
}

void HTTPSession::doHead(char* cmd_argv[], int cmd_argc)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    string s = string(dt);
    response.status_line = "HTTP/1.0 200 OK\r\n";
    string head = "Server: http/1.0\r\nDate:" + s +"Content-Encoding: gzip\r\nContent-Type: text/html\r\nConnection:keep-alive,close\r\nAccess-Control-Allow-Methods: POST, GET, PUT, PATCH, DELETE, OPTIONS\r\nAccess-Control-Allow-Headers: Content-Type,Authorization, Location\r\nAccess-Control-Expose-Headers: Content-Type, Authorization, Location\r\nContent-Length:";
    response.header = head;
    slave->send(response.status_line);
    slave->send(response.header);
}
void HTTPSession::doPost(char* cmd_argv[], int cmd_argc)
{
    response.status_line = "HTTP/1.0 501 Not Implemented\r\n";
    slave->send(response.status_line);
}

void HTTPSession::doPut(char* cmd_argv[], int cmd_argc)
{
    response.status_line = "HTTP/1.0 501 Not Implemented\r\n";
    response.header = "";
    /*slave->send(response.status_line);
    slave->send(response.header);
    slave->send(response.body);*/
}

void HTTPSession::doConnect(char* cmd_argv[], int cmd_argc)
{
    response.status_line = "HTTP/1.0 501 Not Implemented\r\n";
    response.header = "";
    /*slave->send(response.status_line);
    slave->send(response.header);
    slave->send(response.body);*/
}

void HTTPSession::doTrace(char* cmd_argv[], int cmd_argc)
{
    response.status_line = "HTTP/1.0 501 Not Implemented\r\n";
    response.header = "";
    /*slave->send(response.status_line);
    slave->send(response.header);
    slave->send(response.body);*/
}

void HTTPSession::doDelete(char* cmd_argv[], int cmd_argc)
{
    response.status_line = "HTTP/1.0 501 Not Implemented\r\n";
    response.header = "";
    /*slave->send(response.status_line);
    slave->send(response.header);
    slave->send(response.body);*/
}
void HTTPSession::doOption(char* cmd_argv[], int cmd_argc)
{
    response.status_line = "HTTP/1.0 501 Not Implemented\r\n";
    response.header = "";
    /*slave->send(response.status_line);
    slave->send(response.header);
    slave->send(response.body);*/
}
