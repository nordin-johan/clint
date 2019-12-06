/**
 * clint
 *
 * Simple tcp client
 *
 */

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{

    // create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return 1;
    }

    // remote hint structure
    int port = 54000;
    string ipaddr = "127.0.0.1";

    // roll on ipv4
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipaddr.c_str(), &hint.sin_addr);

    // connect sock
    int connres = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connres == -1) {
        return 1;
    }

    char buf[4096];
    string userinput;

    do {

        cout << "> ";
        getline(cin, userinput);

        // send data
        int sendres = send(sock, userinput.c_str(), userinput.size() + 1, 0);
        if (sendres == -1) {
            cout << "Error: Could not send data";
            continue;
        }

        //recv data
        memset(buf, 0, 4096);
        int bytesrecieved = recv(sock, buf, 4096, 0);

        // display data
        cout << "SERVER> " << string(buf, bytesrecieved) << "\r\n";


    } while(true);

    // close socket
    close(sock);

    return 0;

}
