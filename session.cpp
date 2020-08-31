#include "session.h"

Session::Session(TcpSocket* slave)
{
    this->slave = slave;
    this->quitSession = false;
}
Session::~Session()
{
}

void Session::doUnknown(char* cmd_argv[], int cmd_argc)
{
}

void Session::reset()
{
}


bool Session::isQuit()
{
    return quitSession;
}

void Session::setCurrCmd(const char* cmdName)
{

}
