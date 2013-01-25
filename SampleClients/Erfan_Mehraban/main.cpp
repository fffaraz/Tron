//Header Files
#include "winsock2.h"
#include "WS2tcpip.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#include <iostream>

using namespace std;

#define BUFFER_SIZE 11000
#include "agent.h"

int main()
{
    WSADATA firstsock;
    if (WSAStartup(MAKEWORD(2,2),&firstsock) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    SOCKET m_socket;
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //UDP socket

    // this call is what allows broadcast packets to be sent:
    char broadcast = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1)
    {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    char reuseaddr = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof reuseaddr) == -1)
    {
        perror("setsockopt (SO_REUSEADDR)");
        exit(1);
    }

    struct sockaddr_in addr_send;
    struct sockaddr_in addr_recv;
    struct sockaddr_in addr_temp;

    addr_recv.sin_family = AF_INET;
    addr_recv.sin_port = htons(30000);
    addr_recv.sin_addr.s_addr = INADDR_ANY;

    addr_send.sin_family = AF_INET;
    addr_send.sin_port = htons(30001);
    addr_send.sin_addr.s_addr = inet_addr("255.255.255.255");

    int rbind = bind(m_socket, (struct sockaddr *) & addr_recv, sizeof (struct sockaddr_in));

    if (rbind != 0)
    {
            printf("Failed. Could not bind");
            return 1;
    }

	int team;
	cout << "Team ? (1 or 2) ";
	cin >> team;
    Agent agent(team);
	TronMap map;
	agent.setMap(&map);


    while(true)
    {
        char buffer[BUFFER_SIZE];
        socklen_t addrLen = sizeof (struct sockaddr_in);
        int nbytes = recvfrom(m_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &addr_temp, &addrLen);
        cout << "RECV " << nbytes << endl;
        memcpy(&map, buffer, nbytes);
        
        char cmd = agent.percept();
        char ans[3];
        ans[0] = cmd;
        ans[1] = '0' + team;
		ans[2] = 0;
        sendto(m_socket, ans, 2, 0, (struct sockaddr *) &addr_send, addrLen);
		cout << "SENT " << ans << endl;
    }

    return 0;
}

