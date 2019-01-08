#include <stdio.h>
#include <windows.h>
//#include "main.cpp"
#define START_BUTTON 4
#define TUTORIAL_BUTTON 5
#define SETTING_BUTTON 6
#define EXIT_BUTTON 7

LRESULT CALLBACK WindowProcedure(HWND , UINT , WPARAM , LPARAM) ;
void loadImages() ; 
void AddControls(HWND) ;
void loadImages() ;
void setColor(unsigned short textColor , unsigned short backColor ) ; 
HWND hStart , hLogo ;
HMENU hMenu ;
HBITMAP hLogoImage , hStartImage , hInstructorImage , hExitImage ;

int WINAPI WinMain(HINSTANCE hinst , HINSTANCE hPrevInst , LPSTR args , int ncmdshow)
{
	WNDCLASSW wc = {0} ;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL , IDC_ARROW) ;
	wc.hInstance = hinst ;
	wc.lpszClassName = L"GameInterface" ;
	wc.lpfnWndProc = WindowProcedure ;
	
	if(!RegisterClassW(&wc))
		return -1 ;
	CreateWindowW(L"GameInterface" , L"Game" , WS_OVERLAPPEDWINDOW | WS_VISIBLE , 100 , 100 , 500 , 500 , NULL , NULL, NULL , NULL) ;
	MSG msg = {0} ;
	while(GetMessage((&msg) , NULL , NULL , NULL))
	{
		TranslateMessage(&msg) ;
		DispatchMessage(&msg) ;
		
	}
	return 0 ;
}
LRESULT CALLBACK WindowProcedure(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) 
{
	int val ; 
	//char** game = nullptr;//
	switch (msg)
	{
		case WM_COMMAND:
			switch(wp)
			{
				case START_BUTTON:
					//main(1, game);
					break ;
				case TUTORIAL_BUTTON:
					val = MessageBoxW(hWnd , L"Try attack your enemy by moving the gun and turning the mirror." , L"Tutorial" , MB_OK) ;
					break ;
				case EXIT_BUTTON:
					val = MessageBoxW(hWnd , L"Are you sure you want to exit?" , L"Wait!" , MB_YESNO | MB_ICONEXCLAMATION) ;
					if(val == IDYES)
					{
						DestroyWindow(hWnd) ;
					} 
					break ;
			}
		case WM_CREATE:
			loadImages() ;
			AddControls(hWnd) ;
			break ;
		case WM_DESTROY:
			PostQuitMessage(0) ;
			break ;
		default :
			return DefWindowProcW(hWnd , msg , wp , lp) ;
	}
}
void AddControls(HWND hWnd)
{
	hLogo = CreateWindowW(L"Static", NULL , WS_VISIBLE | WS_CHILD | SS_BITMAP , 175 , 50 , 150 , 150 , hWnd , (HMENU)START_BUTTON , NULL , NULL) ;
	SendMessageW(hLogo , STM_SETIMAGE , IMAGE_BITMAP , (LPARAM)hLogoImage); 
	CreateWindowW(L"Button", L"START", WS_VISIBLE | WS_CHILD, 175 , 200 , 150 , 38 , hWnd , (HMENU)START_BUTTON , NULL , NULL) ;
	CreateWindowW(L"Button", L"TUTORIAL" , WS_VISIBLE | WS_CHILD , 175 , 250 , 150 , 38 , hWnd , (HMENU)TUTORIAL_BUTTON , NULL , NULL) ;
	CreateWindowW(L"Button", L"SETTING" , WS_VISIBLE | WS_CHILD , 175 , 300 , 150 , 38 , hWnd , (HMENU)SETTING_BUTTON , NULL , NULL) ;  
	CreateWindowW(L"Button", L"EXIT" , WS_VISIBLE | WS_CHILD , 175 , 350 , 150 , 38 , hWnd , (HMENU)EXIT_BUTTON , NULL , NULL) ;
}
void loadImages()
{
	hLogoImage = (HBITMAP)LoadImageW(NULL , L"logo_2.bmp" , IMAGE_BITMAP , 0 , 0 , LR_LOADFROMFILE) ; 
	//hStartImage = (HBITMAP)LoadImageW(NULL , L"START.bmp" , IMAGE_BITMAP , 150 , 38 , LR_LOADFROMFILE) ;
}
