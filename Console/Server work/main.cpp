#include <winsock2.h>
#include <iostream>
#include <windows.h>
using namespace std;

int     	  Port;
char 	    IP[16];
char Password[256];
char password[256];
char      msg[256];

const int MaxConnections = 100000;

struct USER
{
	char    Name[256];
	SOCKET Connection;
		
}User[MaxConnections];

int Counter;

void MessageHandler(int index) 
{
	char msg[256];

	wsprintf(msg, "\r\n\nServer: connect new user her number: %d, name: %s", Counter - 1, User[Counter - 1].Name);
	for(int nCounter = 0; nCounter < Counter; nCounter++) 
	{
		if(nCounter != index) 
			send(User[nCounter].Connection, msg, sizeof(msg), 0);
	}
	
	while(true) 
	{
		for(int nCounter = 0; nCounter < sizeof(msg); nCounter++)
			msg[nCounter] = 0;
			
		if(recv(User[index].Connection, msg, sizeof(msg), 0))
		{
			if(!strcmp(msg, "closesocket"))
			{
				closesocket(User[index].Connection);
				break;	
			}
				
			for(int i = 0; i < Counter; i++) 
			{
				if(i != index) 
					send(User[i].Connection, msg, sizeof(msg), 0);
			}
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
				
				recv(newConnection, User[Counter].Name, sizeof(User[Counter].Name), 0);
				cout << "Connect new user her number: " << Counter << ", name: " << User[Counter].Name << endl;
				
				Counter++;
				User[i].Connection = newConnection;
				
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MessageHandler, (LPVOID)(i), 0, 0);
			
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
