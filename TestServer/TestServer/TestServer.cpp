#include "pch.h"
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#pragma warning(disable:4996)
using namespace std;
SOCKET Connections[100];
int counter = 0;

void Chat(int index) 
{
	char soob[256];
	while (true) 
	{
       recv(Connections[index], soob, sizeof(soob), NULL);
	   for (int i = 0;i < counter;i++) 
	   {
		   if (i == index)
		   {
			   continue;
		   }
			   send(Connections[i], soob, sizeof(soob), NULL);
	   }
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

	SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL);
	bind(slisten, (SOCKADDR*)&addr, sizeof(addr));
	listen(slisten, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100;i++)
	{
		newConnection = accept(slisten, (SOCKADDR*)&addr, &size);
	if (newConnection == 0)
		cout << "Error" << endl;
	else
		cout << "Client Connected" << endl;

	Connections[i] = newConnection;
	counter++;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Chat, (LPVOID)(i), NULL, NULL);
	}

	return 0;
}
