#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")


DWORD RecvData(char** DataBuffer) {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET ConnectSocket;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
#pragma warning(disable : 4996)
	clientService.sin_addr.s_addr = inet_addr("192.168.186.134");
	clientService.sin_port = htons(4444);
	int iResult = 0;
	INT OnceRecvBytes = 0;
	INT RecvBytes = 0;
	struct timeval timeout = { 3,0 };
	int ret = setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	char* bufferReceivedBytes = new char[2000000];

	do
	{
		iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
		Sleep(5);

	} while (iResult == SOCKET_ERROR);


	do
	{
		OnceRecvBytes = recv(ConnectSocket, bufferReceivedBytes, 4096, NULL);
		RecvBytes += OnceRecvBytes;
		bufferReceivedBytes += OnceRecvBytes;
	} while (OnceRecvBytes > 0);
	
	iResult = closesocket(ConnectSocket);
	*DataBuffer = bufferReceivedBytes- RecvBytes;
	return RecvBytes;
};