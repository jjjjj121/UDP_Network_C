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

	//家南 积己

	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN ServerSockADDR;

	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));

	ServerSockADDR.sin_family = PF_INET;
	ServerSockADDR.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockADDR.sin_port = htons(1234);

	int ServerLength = sizeof(ServerSockADDR);

	//connect(ServerSocket, (SOCKADDR*)&ServerSockADDR, ServerLength);


	//佬扁 颇老
	FILE* TF = fopen("test7.jpg", "rb");

	char Buffer[1024] = {};

	while (!feof(TF))
	{

		/*SOCKADDR_IN ClientSockADDR;
		memset(&ClientSockADDR, 0, sizeof(SOCKADDR_IN));
		int ClientSockLength = sizeof(ClientSockADDR);*/

		//recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (SOCKADDR*)&ClientSockADDR, &ClientSockLength);
		//cout << "Recv IP : " << inet_ntoa(ClientSockADDR.sin_addr) << endl;
		//memset(Buffer, 0, sizeof(Buffer));

		size_t ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), TF);

		sendto(ServerSocket, Buffer, ReadSize, 0, (SOCKADDR*)&ServerSockADDR, sizeof(ServerSockADDR));
		//cout << "size : " << sizeof(Buffer) << endl;

		for (int i = 0; i < 10000; ++i);
		
	}

	sendto(ServerSocket, Buffer, 0, 0, (SOCKADDR*)&ServerSockADDR, sizeof(ServerSockADDR));
	cout << "size : " << sizeof(Buffer) << endl;


	fclose(TF);



	closesocket(ServerSocket);

	WSACleanup();


	return 0;
}