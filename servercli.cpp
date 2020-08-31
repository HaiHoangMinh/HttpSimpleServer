#include <iostream>
#include "servercli.h"
#include <windows.h>


ServerCLI::ServerCLI():CmdLineInterface("HTTP>")
{
    http = new HTTPServer();
    initCmd();

}
ServerCLI::~ServerCLI()
{
    delete http;
}


void ServerCLI::initCmd()
{
    addCmd("start",CLI_CAST(&ServerCLI::doStart));
    addCmd("stop",CLI_CAST(&ServerCLI::doStop));
    addCmd("restart",CLI_CAST(&ServerCLI::doRestart));
    addCmd("status",CLI_CAST(&ServerCLI::doStatus));
    addCmd("help", CLI_CAST(&ServerCLI::doHelp));
}

void ServerCLI::doStart(char * cmd_argv[], int cmd_argc)
{
    if(http->isRunning())
        cout << "HTTP server is running!" << endl;
    else if(http->start())
        cout << "HTTP Server started" << endl;
    else
        cout << "HTTP Server failed to start" <<endl;
}

void ServerCLI::doStop(char * cmd_argv[], int cmd_argc)
{
    http->stop();
    cout << "HTTP Server stopped" << endl;
}



void ServerCLI::doRestart(char * cmd_argv[], int cmd_argc)
{

    if(http->restart())
        cout << "HTTP Server restarted" << endl;
    else
        cout << "HTTP Server failed to restart" <<endl;

}

void ServerCLI::doStatus(char * cmd_argv[], int cmd_argc)
{

    if(http->isRunning())
        cout << "HTTP Server is running\n";
    else
        cout << "HTTP Server is not running\n";

}

void ServerCLI::doHelp(char * cmd_argv[], int cmd_argc)
{
    cout << "Cac lenh cua chuong trinh:" << endl;
    cout << "- start               Bat HTTP server" << endl;
    cout << "- stop                Tat HTTP server" << endl;
    cout << "- status              Trang thai HTTP server" << endl;
    cout << "- help                Tro giup" << endl;
}

