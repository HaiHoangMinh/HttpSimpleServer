#include <iostream>
#include "servercli.h"

using namespace std;

int main()
{
    cout << "HTTP Server!" << endl;
    ServerCLI cli;
    cli.initCmd();
    cli.run();
    return 0;
}
