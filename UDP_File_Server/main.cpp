#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

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


	//make socket
	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN ServerSockADDR;

	//set server info
	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));
	ServerSockADDR.sin_addr.s_addr = INADDR_ANY;
	ServerSockADDR.sin_port = htons(1234);
	ServerSockADDR.sin_family = PF_INET;


	//socket bind ip:port
	bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN));
	string ASendMessage;

	//쓰기 파일
	FILE* TF = fopen("test8.jpg", "wb");

	//버퍼
	char Buffer[1024] = {};

	int RecvLength = 0;


	SOCKADDR_IN ClientSockADDR;
	memset(&ClientSockADDR, 0, sizeof(SOCKADDR_IN));
	int ClientSockLength = sizeof(ClientSockADDR);

	while (1)
	{



		//SOCKADDR_IN ClientSockADDR;
		//memset(&ClientSockADDR, 0, sizeof(SOCKADDR_IN));
		//int ClientSockLength = sizeof(ClientSockADDR);
		//memset(Buffer, 0, sizeof(Buffer));


		RecvLength = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (SOCKADDR*)&ClientSockADDR, &ClientSockLength);
		//cout << "size : " << sizeof(Buffer) << endl;


		if (RecvLength <= 0)
		{
			break;
		}
		
		
		size_t WriteSize = fwrite(Buffer, sizeof(char), sizeof(Buffer), TF);

	}


	fclose(TF);

	//close socket
	closesocket(ServerSocket);

	//cleanup winsock
	WSACleanup();


	return 0;

}