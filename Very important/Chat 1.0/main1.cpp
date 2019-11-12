
#include <windows.h>                       //  ���������� (������������ ���� ) ���� ������ � ���������� ������� WinAPI  

#include "Sources/Global.h"
using namespace Global;

#define EDIT       1
#define BUTTONSEND 2
#define EXIT       3

HWND 		  GEditBox;
HWND     		 bSend;
HWND     		 bExit;

COORDINATES oldsWindow;
COORDINATES    sWindow;

void INIT()
{
	sWindow.x    =       370;
	sWindow.y    =       620;
	oldsWindow.x = sWindow.x;
	oldsWindow.y = sWindow.y;
}

void ResizeOrChangeCoordinates()
{
	SetWindowPos(bSend, 0, 277 + (sWindow.x - oldsWindow.x), 560 + (sWindow.y - oldsWindow.y), 90, 28, 0);
	SetWindowPos(bExit, 0, 277 + (sWindow.x - oldsWindow.x), 588 + (sWindow.y - oldsWindow.y), 90, 28, 0);
	SetWindowPos(GEditBox, 0, 5, 560 + (sWindow.y - oldsWindow.y), 270 + (sWindow.x - oldsWindow.x), 56, 0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)                   // 1 - �������� ����.               
{																				                    	
	switch(message)
	{	
		case WM_CREATE: 
		{
			GEditBox = CreateWindow("EDIT", "Enter your message", 
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
				 0, 0, 0, 0, hWnd, (HMENU) EDIT,       hInstance, NULL);	
			
			bSend = CreateWindow("BUTTON", "Send", 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				 0, 0, 0, 0, hWnd, (HMENU) BUTTONSEND, hInstance, NULL);	
			
			bExit = CreateWindow("BUTTON", "Exit", 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				 0, 0, 0, 0, hWnd, (HMENU) EXIT,       hInstance, NULL);
		}
		break;
		
		case WM_COMMAND:
		{
			if(LOWORD(wParam) == EXIT)
				SendMessage(GetParent((HWND)lParam), WM_DESTROY, 0, 0);	
		}
		break;
		
		case WM_SIZE:
		{
			sWindow.x = LOWORD(lParam);
			sWindow.y = HIWORD(lParam);
			ResizeOrChangeCoordinates();	
		}
		break;
			                         
	    case WM_DESTROY:   PostQuitMessage(0);                //  ��������� ����������� ��������� ��� ��_�������������
		 	 			   break;
		 	 			   
		default:    	   return DefWindowProc(hWnd, message, wParam, lParam);    // ��������� OS ��������� ���������
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow)     // 2 - �������� ����. 
{
	INIT();
	
	MSG msg;                                // ������ ������� ��������� ��������� �� OS Windows ��� ������ ���������� 
	WNDCLASS WndClass;      // ������ ������� ������� ���������--- ������� ������������ ����� �������� ���� ���������� 	
			 WndClass.style         = 0;
			 WndClass.lpfnWndProc   = WndProc;                                             // ����� (���) ������� ����
			 WndClass.cbClsExtra    = 0;
			 WndClass.cbWndExtra    = 0;
			 WndClass.hInstance     = hInstance;                                            //   ���������� ����������
			 WndClass.hIcon		    = LoadIcon(hInstance, "MYICON");                             //   ��������� ������
			 WndClass.hCursor	    = LoadCursor(NULL, IDC_ARROW);                          //   ��������� ��� ������� 
			 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);              //   ���� ������� ���� �������
			 WndClass.lpszMenuName  = "xMENU";                                                 //   ��������� ��� ���� 
			 WndClass.lpszClassName = "dllBridge";                                 //   ��������� ���� ��� ������ ����  
	
	if(!RegisterClass(&WndClass)) return 0;    // ���� ����� �� ���������������, �� ������� (��������� �� �����������)
	
	hWnd = CreateWindow("dllBridge",                       // ������� ���� ������ dllBridge (��� ������ ���� ���������)
						"Chat (Client)",                                  // ��������� ���� (������� �� �������-����� ������)
						WS_OVERLAPPEDWINDOW,                                                             // ����� ����
						200,                                                 // ���������� X ������ �������� ���� ���� 
						100,              						             // ���������� Y ������ �������� ���� ���� 
					    sWindow.x,                        										   // ������� ���� (������)
					    sWindow.y,                        														 // ������
					    NULL,                        // ���������� ������������� ����  ( ��� �������� ���� ��������� :)
					    NULL,                                     // ����������  ���� ��� ������������� ��������� ����.
					    hInstance,                                                 // ���������� ���������� ����������
					    NULL);                      
	if(!hWnd) return 0;							        //  ���� ���� �� �������, �� ������� (��������� �� �����������)
	ShowWindow(hWnd, nCmdShow);						                                     //  ���������� ���� �� ������
	UpdateWindow(hWnd);								                                                 //  �������� ����       								  									   								   

	while(GetMessage(&msg,0,0,0))                                                         //  ���� ��������� ���������
	{	
		  TranslateMessage(&msg);                                   //  �������� � "�������������" ��������� � �������
		  DispatchMessage (&msg);
	} 

return msg.wParam;
}






















