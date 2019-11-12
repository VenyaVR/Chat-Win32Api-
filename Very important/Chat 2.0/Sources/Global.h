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
}
