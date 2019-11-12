
#include <windows.h>                       //  Подключаем (заголовочный файл ) типы данных и библиотеки функций WinAPI  
#include <winsock2.h>

#include "Sources/Global.h"
using namespace Global;

#include "Sources/menu.h"

#define EDIT       1
#define BUTTONSEND 2
#define EXIT       3
#define REDIT      4

HWND 		  GEditBox;
HWND 		  REditBox;
HWND     		 bSend;
HWND     		 bExit;

COORDINATES oldsWindow;
COORDINATES    sWindow;

HBRUSH RBackgroundBrush
= CreateSolidBrush(0);

HBRUSH GBackgroundBrush
= CreateSolidBrush(RGB(25, 25, 25));

char Msg[256];

BOOL CALLBACK DialogFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void SendMessage()
{
	for(int i = 0; i < sizeof(Msg); i++)	
		Msg[i] = 0;
				
	char part[256];
	GetWindowText(GEditBox, part, sizeof(part));
	SetWindowText(GEditBox, Msg);
						
	wsprintf(Msg, "%s%s%s", Name, ": ", part);
	SetWindowText(REditBox, Msg);
	send(Connection, Msg, sizeof(Msg), 0);		
}

void MessageHandler() 
{
	char  msg[256];
	
	while(true)
		if(recv(Connection, msg, sizeof(msg), 0))
			SetWindowText(REditBox, msg);
}

bool Connect()
{
	SOCKADDR_IN addr;
	int nSizeOfADDR      =  sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port 		 = 	 htons(Port);
	addr.sin_family 	 =       AF_INET;	
	
	Connection = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) 
	{
		MessageBox(NULL, "Error: failed connect to server", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	else
	{
		//MessageBox(NULL, "Connect to Server", "INFO", MB_OK | MB_ICONINFORMATION);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MessageHandler, 0, 0, 0);
		return true;
	}
}

void DETCTS();

void INIT()
{	
	sWindow.x    =       370;
	sWindow.y    =       620;
	oldsWindow.x = sWindow.x;
	oldsWindow.y = sWindow.y;
	
	yColor = RGB(255, 51, 51);	
	iColor = RGB(255, 255, 255);
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData))
		MessageBox(NULL, "Error: failed load library Winsock", "Error", MB_OK | MB_ICONERROR);
}

void ResizeOrChangeCoordinates()
{
	SetWindowPos(bSend, 0, 277 + (sWindow.x - oldsWindow.x), 560 + (sWindow.y - oldsWindow.y), 88,    28, 0);
	SetWindowPos(bExit, 0, 277 + (sWindow.x - oldsWindow.x), 588 + (sWindow.y - oldsWindow.y), 88,    28, 0);
	SetWindowPos(GEditBox, 0, 5, 560 + (sWindow.y - oldsWindow.y), 270 + (sWindow.x - oldsWindow.x),  56, 0);
	SetWindowPos(REditBox, 0, 5, 10, 360 + (sWindow.x - oldsWindow.x), 545 + (sWindow.y - oldsWindow.y), 0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)                   // 1 - смотрите ВЫШЕ.               
{				
	switch(message)
	{	
		case WM_CREATE: 
		{
			GEditBox = CreateWindow("EDIT", "Enter your message", 
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
				 0, 0, 0, 0, hWnd, (HMENU) EDIT, hInstance, NULL);	
			
		 	REditBox = CreateWindow("EDIT", "", 
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL
				 /*WS_SIZEBOX | WS_DLGFRAME*/  /* | ES_READONLY*/,
				 0, 0, 0, 0, hWnd, (HMENU) REDIT, hInstance, NULL);	
			
			
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
			if(LOWORD(wParam) == IDD_CtS)
				DialogBox(hInstance, "DETCTS", hWnd, DialogFunction);
			
			if(LOWORD(wParam) == BUTTONSEND)
				SendMessage();
			
			if(LOWORD(wParam) == EXIT)
				SendMessage(GetParent((HWND)lParam), WM_DESTROY, 0, 0);	
		}
		break;
		
		case WM_KEYDOWN:
			{
				if(wParam == 13)
					SendMessage();	
			}
			break;
		
		case WM_CTLCOLOREDIT:  
			
			if(REditBox == (HWND)lParam)    		                 		
		    {
				SetTextColor((HDC)wParam, RGB(150, 150, 150));
				SetBkColor  ((HDC)wParam, RGB(0, 0, 0));   
			    return (LRESULT)RBackgroundBrush; 
			}
			
			if(GEditBox == (HWND)lParam)    		                 		
		    {
				SetTextColor((HDC)wParam, RGB(180, 180, 180));
				SetBkColor  ((HDC)wParam, RGB(25, 25, 25));   
			    return (LRESULT)GBackgroundBrush; 
			}
		    
			break;  		
		
		case WM_SIZE:
		{
			sWindow.x = LOWORD(lParam);
			sWindow.y = HIWORD(lParam);
			ResizeOrChangeCoordinates();	
		}
		break;
			                         
	    case WM_DESTROY:   PostQuitMessage(0);                //  Принимаем однократное сообщение для ДЕ_инициализации
		 	 			   break;
		 	 			   
		default:    	   return DefWindowProc(hWnd, message, wParam, lParam);    // обработка OS остальных сообщений
	}
	return 0;
}

BOOL CALLBACK DialogFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CREATE: break;
		
		case WM_COMMAND: 
		{
			switch(LOWORD(wParam))
			{
				case IDCANCEL: EndDialog(hWnd, 0); break;
				
				case IDD_BCONNECTION: 
				{
					static short CounterConnect = 0;
					
					if(CounterConnect != 0)
					{
						MessageBox(hWnd, "Error: you are already connected to the server", "Error", MB_OK | MB_ICONERROR);
						EndDialog(hWnd, 0);
					}
					
					char Port[4];
					
					::Port = 1;
					
					GetDlgItemText(hWnd,       IDD_EDIP,       IP,       sizeof(IP));
					GetDlgItemText(hWnd,     IDD_EDPORT,     Port,     sizeof(Port));
										
					if(Connect() == true)
					{
						CounterConnect++;
						GetDlgItemText(hWnd,     IDD_EDNAME,     Name,     sizeof(Name));
						GetDlgItemText(hWnd, IDD_EDPASSWORD, Password, sizeof(Password));
						EndDialog(hWnd, 0);
					}
		
				}
				break;	
			}	
		}	
		break;
	}
	
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow)     // 2 - смотрите ВЫШЕ. 
{
	INIT();
	
	MSG msg;                                // Создаём элемент структуры сообщений от OS Windows для нашего приложения 
	WNDCLASS WndClass;      // Создаём элемент оконной структуры--- сначала регистрируем класс главного окна программы— 	
			 WndClass.style         = 0;
			 WndClass.lpfnWndProc   = WndProc;                                             // адрес (имя) функции окна
			 WndClass.cbClsExtra    = 0;
			 WndClass.cbWndExtra    = 0;
			 WndClass.hInstance     = hInstance;                                            //   Дескриптор приложения
			 WndClass.hIcon		    = LoadIcon(hInstance, "MYICON");                             //   Загружаем иконку
			 WndClass.hCursor	    = LoadCursor(NULL, IDC_ARROW);                          //   Загружаем тип курсора 
			 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);              //   Цвет заливки окна выбрали
			 WndClass.lpszMenuName  = "xMENU";                                                 //   Указываем имя меню 
			 WndClass.lpszClassName = "dllBridge";                                 //   Придумали сами имя класса окна  
	
	if(!RegisterClass(&WndClass)) return 0;    // если класс не зарегистрирован, то выходим (программа не запустилась)
	
	
	
	hWnd = CreateWindow("dllBridge",                       // Создаем окно класса dllBridge (имя класса сами придумали)
						"Chat (Client)",                                  // заголовок окна (надпись на верхней-синей полосе)
						WS_OVERLAPPEDWINDOW,                                                             // стиль окна
						200,                                                 // координата X левого верхнего угла окна 
						100,              						             // координата Y левого верхнего угла окна 
					    sWindow.x,                        										   // размеры окна (Ширина)
					    sWindow.y,                        														 // Высота
					    NULL,                        // Дескриптор родительского окна  ( нет главного окна программы :)
					    NULL,                                     // Дескриптор  меню или идентификатор дочернего окна.
					    hInstance,                                                 // Дескриптор экземпляра приложения
					    NULL);                      
	if(!hWnd) return 0;							        //  если окно не создано, то выходим (программа не запустилась)
	ShowWindow(hWnd, nCmdShow);						                                     //  отобразить окно на экране
	UpdateWindow(hWnd);								                                                 //  обновить окно       								  									   								   

	while(GetMessage(&msg,0,0,0))                                                         //  Цикл обработки сообщений
	{	
		  TranslateMessage(&msg);                                   //  Принятие и "проталкивание" сообщений в очереди
		  DispatchMessage (&msg);
	} 

return msg.wParam;
}






















