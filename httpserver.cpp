#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include "httpserver.h"
#include "httpsession.h"

using namespace std;

Request::Request(string& me,string& uri,string& he)
{
    this->Method = me;
    this->URI = uri;
    this->header = he;
}
Request::Request()
{

}
string  Request::getMethod()
{
        return Method;

}
string Request::getURI()
{
        return URI;

}
string  Request::getHead()
{
        return header;

}


HTTPServer::HTTPServer(unsigned short port):TCPServer(port)
{
    initCmd();
}
HTTPServer::~HTTPServer()
{
    if(isRunning())
    {
        stop();
        cout<< "HTTP Server stopped!\n";
    }
}

void HTTPServer::initCmd()
{
    addCmd(GET, FUNC_CAST(&HTTPSession::doGet));
    addCmd(HEAD, FUNC_CAST(&HTTPSession::doHead));
    addCmd(POST, FUNC_CAST(&HTTPSession::doPost));
    addCmd(PUT, FUNC_CAST(&HTTPSession::doPut));
    addCmd(DELETE, FUNC_CAST(&HTTPSession::doDelete));
    addCmd(OPTION, FUNC_CAST(&HTTPSession::doOption));
    addCmd(CONNECT, FUNC_CAST(&HTTPSession::doConnect));
    addCmd(TRACE, FUNC_CAST(&HTTPSession::doTrace));
}

int HTTPServer::checkRequest(TcpSocket* slave, char* buffer, int buflen) // Đọc cú pháp request
{
    int bytes_recv;
     try
    {

        ostringstream os;
        do
        {
            bytes_recv = slave->recvLine(buffer,256); // Loai bo ky tu "/r/n"
            if (bytes_recv>=2)
            {
                 buffer[bytes_recv-2] = 0;
                 os << buffer;
            }

        }
        while (bytes_recv > 2);
        this->check = os.str();
        string s = this->check;
        string a[50] ;
        istringstream iss(s);
        int i =0;
        do
        {
            string sub;
            iss >> sub;
            a[i] = sub;
            i++;
        } while (iss);
        this->request.Method = a[0];
        if (request.Method != "GET" && request.Method != "HEAD" && request.Method != "POST" && request.Method != "PUT" && request.Method != "DELETE" && request.Method != "TRACE" && request.Method != "CONNECT" && request.Method != "OPTION")
            {
                slave->send("HTTP/1.0 400 Bad Request ");
                return -1;
            }
        else return bytes_recv;
    }
    catch(SocketException&e )
    {
        cerr << e.what() << endl;
        return -1;
    }
}
 unsigned short HTTPServer::getRequest(char *sCmdBuf, int len, char * cmd_argv[], int& cmd_argc)
 {

        //cmd_argc = 3;
        if(len<=0)   return -1;
        string s = this->check;
        string a[50] ;
        istringstream iss(s);
        int i =0;
        do
        {
            string sub;
            iss >> sub;
            a[i] = sub;
            i++;
        } while (iss);
        this->request.URI = a[1].erase(0,1);
        for(int j = 2; j<= i;j++)
        {
            request.header = request.header + a[j] + "  ";
        }

        if(request.Method=="GET")
        {        return 0;        }
        if(request.Method=="HEAD")
        {        return 1;        }
        else{        return 2;        }

}
 void HTTPServer::startNewSession(TcpSocket* slave)
 {
        // Tao session moi --> gui ket noi --> ket thuc session
    HTTPSession* session = new HTTPSession(slave);
    char cmdBuffer[256];
    char sCmdBuf[256];
    int cmdLen;
    char* cmdArgv[256];
    int cmdArgc;
    unsigned short cmdId;
    try
    {

        while(!session->isQuit())
        {
            // Nhan lenh
            cmdBuffer[0] = 0;
            cmdLen = checkRequest(slave, cmdBuffer, 256);
            // Kiem tra lenh
            if(cmdLen <= 0)
                break;
            // Phan tich request
            cmdId = getRequest(sCmdBuf, cmdLen, cmdArgv, cmdArgc);
            // Thuc hien tra ve response
            doCmd(session,cmdId,cmdArgv,cmdArgc);
            if(request.Method == "GET")
            {
                this->getResource(slave);
                this->res=session->getResponse();
                stringstream ss;
                ss << this->body_length;
                string str = ss.str();
                this->res = this->res +  str;
                slave->send(this->res);
                slave->send("\r\n");
                slave->send(this->body);
                break;
            }
            else if (request.Method == "HEAD")
            {
                this->getResource(slave);
                //this->res=session->getResponse();
                stringstream ss;
                ss << this->body_length;
                string str = ss.str();
                //this->res = this->res +  str;
                //slave->send(this->res);
                //cout << res;
                slave->send(str);
                slave->send("\r\n");
                break;
            }
            else{
                slave->send("\r\n");
                break;
            }
        }
        // session finish
        slave->close();
        if (session->isQuit())
        {
            delete session;
            cout << "--- Session end ---\n";
        }
    }

    catch(SocketException&e)
    {
        cerr << e.what() << endl;
        delete session;
    }
 }

void HTTPServer::getResource(TcpSocket* slave)
{
        ifstream f;
        string data;
        this->body="";
        char* buffer;
        int i=0;
        this->body_length = 0;
        if( this->request.URI=="")
        {
            f.open("index.html",ios::in|ios::binary);
            while(!f.eof())
            {
                //f.read(buffer,256);
                f >> data;
                //cout << data;
                //cout << buffer;
                //slave->send(data);
                this->body = this->body + data ;
                //this->body_length = this->body_length + data.size();
                this->body_length =  this->body.size();
                //slave->send(buffer,256);
            }
            slave->send("\r\n");
            f.close();
        }
        else{
            f.open(this->request.URI, ios::in|ios::binary);
            char buff[256];
            while(!f.eof())
            {
                //f.read((char *) &buff[i],sizeof(buff));
                //i++;
                f >> data;
                //slave->send(data);
                this->body = this->body + data ;
                //this->body_length = this->body_length + data.size();
                this->body_length =  this->body.size();
                //slave->send(buff,256);
            }
            slave->send("\r\n");
            f.close();
        }
        // DOc file anh theo dang nhi phan
        //string result = data.str();

}




