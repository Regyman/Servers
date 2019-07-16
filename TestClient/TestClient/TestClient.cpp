#include "pch.h"
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<conio.h>
#pragma warning(disable:4996)
using namespace std;

SOCKET Connection;

void Chat() 
{
	char message1[256];
	while (true) 
	{ 
	  recv(Connection, message1, sizeof(message1), NULL);
	  cout << message1 << endl;
	}
	
}

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error" << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int size = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

     Connection = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Error of connection" << endl;
		return 1;
	}
	else
		cout << "Connected" << endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Chat, NULL, NULL, NULL);
    char message[256];
	while (true) 
	{
		cin.getline(message, sizeof(message));
		send(Connection, message,sizeof(message),NULL);
		Sleep(10);
	}

	_getch();
	return 0;
}