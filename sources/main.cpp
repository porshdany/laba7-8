#include "Server.h"
#include "Client.h"
#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;
int main(int argc, char* argv[]) {
    init();

    Server server;

    Client client;

    client.work();
}
