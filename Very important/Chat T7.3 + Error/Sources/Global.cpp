#include <windows.h>

namespace Global
{
	HWND  	 	   hWnd;	
	HDC             hdc;
	HINSTANCE hInstance; 
	
	
	SOCKET Connection;
	
	int 		  Port;
    char 	 szPort[5] =      "Port";
	char 	    IP[16] = 		"IP";
    char 	 Name[256] = "Your name";
	char Password[256];
	char    empty[256];
	
	HFONT  		yhFont;
	HFONT  		ihFont;
	
	int     	yColor;
	int         iColor;
}
