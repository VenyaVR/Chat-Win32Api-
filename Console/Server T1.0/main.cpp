#include <winsock2.h>
#include <iostream>
#include <windows.h>
using namespace std;

int     	  Port;
char 	    IP[16];
char Password[256];
char password[256];

const int MaxConnections = 1000;

struct USER
{
	char*		 Name;
	SOCKET Connection;
		
}User[MaxConnections];

SOCKET Connections[100];
int Counter;

void MessageHandler(int index) 
{
	char msg[256];
	
	cout << "Connect new user her number: " << Counter << endl;
	wsprintf(msg, "Connect new user her number: %d", Counter);
	
	for(int i = 0; i < Counter; i++) 
	{
		if(i != index) 
			send(User[i].Connection, msg, sizeof(msg), 0);
	}
	
	while(true) 
	{
		recv(User[index].Connection, msg, sizeof(msg), 0);
		for(int i = 0; i < Counter; i++) 
		{
			if(i != index) 
				send(User[i].Connection, msg, sizeof(msg), 0);
		}
	}
}

int main(int argc, char* argv[]) 
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	WSAStartup(DLLVersion, &wsaData); 
	
	cout << "Enter IP: ";
	cin >> IP;
	cout << "Enter Port: ";
	cin >> Port;
	cout << "Enter new password: ";
	cin >> Password;
	
	SOCKADDR_IN addr;
	int nSizeOfADDR      =  sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port 		 = 	 htons(Port);
	addr.sin_family 	 =       AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
		
	for(int i = 0; i < MaxConnections; i++) 
	{	
		ReplaceConnect:
		if((newConnection = accept(sListen, (SOCKADDR*)&addr, &nSizeOfADDR))) 
		{	
			recv(newConnection, password, sizeof(password), 0);
			
			if(!strcmp(Password, password))
			{	
				send(newConnection, "Server: true password", strlen("Server: true password"), 0);	
			
				User[i].Connection = newConnection;
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MessageHandler, (LPVOID)(i), 0, 0);
				Counter++;
			}
			else
			{	
				send(newConnection, "(Server::Error): Wrong password", strlen("(Server::Error): Wrong password"), 0);	
				goto ReplaceConnect;
			}
		}
	}

	system("pause");
	return 0;
}

