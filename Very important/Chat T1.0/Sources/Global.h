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
	extern char 	   IP[256];
	extern char  Password[256];
	extern char 	 Name[256]; 
}
