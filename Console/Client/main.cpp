#include <winsock2.h>
#include <iostream>
using namespace std;

SOCKET Connection;

int 		  Port;
char 	   IP[256];
char Password[256];
char 	 Name[256];

void MessageHandler() 
{
	char msg[256];
	while(true)
	{
		recv(Connection, msg, sizeof(msg), 0);
		cout << msg << endl;
	}
}

int main(int argc, char* argv[]) 
{
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}
	
	cout << "Enter IP: ";
	cin >> IP;
	cout << "Enter Port: ";
	cin >> Port;
	/*cout << "Enter password to server: ";
	cin >> Password;*/
	cout << "Enter your name: ";
	cin >> Name;
	
	SOCKADDR_IN addr;
	int nSizeOfADDR      =  sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port 		 = 	 htons(Port);
	addr.sin_family 	 =       AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) 
	{
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	cout << "Connected!\n";
	
	
	//send(Connection, Password, sizeof(Password), 0);
	send(Connection, Name,     sizeof(Name),     0);
	
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MessageHandler, 0, 0, 0);

	char msg1[256];
	char msg [256];
	while(true) 
	{
		cin.getline(msg1, sizeof(msg1));
		wsprintf(msg, "%s%s%s", Name, ": ", msg1);
		
		send(Connection, msg, sizeof(msg), 0);
		Sleep(10);
	}

	system("pause");
	return 0;
}
