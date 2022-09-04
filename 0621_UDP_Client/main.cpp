#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//家南 积己

	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN ServerSockADDR;

	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));

	ServerSockADDR.sin_family = PF_INET;
	ServerSockADDR.sin_addr.s_addr = inet_addr("172.16.5.216");
	ServerSockADDR.sin_port = htons(50501);

	int ServerLength = sizeof(ServerSockADDR);

	//connect(ServerSocket, (SOCKADDR*)&ServerSockADDR, ServerLength);

	char Buffer[1024] = {};
	string ASendMessage;

	while (1)
	{
		//memset(Buffer, 0, sizeof(Buffer));
		//cin >> Buffer;

		
		getline(cin, ASendMessage);

		sendto(ServerSocket, ASendMessage.c_str(), strlen(ASendMessage.c_str()), 0, (SOCKADDR*)&ServerSockADDR, sizeof(ServerSockADDR));
		recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (SOCKADDR*)&ServerSockADDR, &ServerLength);
		printf("recvfrom : %s %s\n", inet_ntoa(ServerSockADDR.sin_addr), Buffer);

	}

	closesocket(ServerSocket);

	WSACleanup();


	return 0;
}