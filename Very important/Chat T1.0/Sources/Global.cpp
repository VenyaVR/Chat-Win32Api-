#include <windows.h>

namespace Global
{
	HWND  	 	   hWnd;	
	HDC             hdc;
	HINSTANCE hInstance; 
	
	
	SOCKET Connection;
	
	int 		  Port;
	char 	   IP[256];
	char Password[256];
	char 	 Name[256];
}
