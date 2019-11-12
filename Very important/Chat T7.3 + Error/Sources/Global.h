#include <windows.h>

namespace Global
{
	struct COORDINATES
	{
		int x;
		int y;	
	};
	
	extern HWND  	 	   hWnd;	
	extern HDC             hdc;
	extern HINSTANCE hInstance;
	
	extern SOCKET Connection;
	
	extern int 		      Port;
	extern char 	 szPort[5];
	extern char 	    IP[16];
	extern char 	 Name[256];
	extern char  Password[256]; 
	extern char     empty[256];
	
	extern HFONT  		yhFont;
	extern HFONT  		ihFont;
	
	extern int     	yColor;
	extern int         iColor;
}
