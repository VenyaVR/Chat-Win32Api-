#include <windows.h>

namespace Global
{
	HWND  	 	   hWnd;	
	HDC             hdc;
	HINSTANCE hInstance; 
	
	
	SOCKET Connection;
	
	int 		  Port;
	char 	    IP[16];
	char Password[256];
	char 	 Name[256];
	char    empty[256];
	
	HFONT  		yhFont;
	HFONT  		ihFont;
	
	int     	yColor;
	int         iColor;
}
