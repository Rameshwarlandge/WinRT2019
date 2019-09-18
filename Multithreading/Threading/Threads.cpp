#include<Windows.h>
#include "Threads.h"
#include<wchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

//winmain 

int WINAPI WinMain(HINSTANCE hInsatance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX mywndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szMyAppName[] = TEXT("MyApp");


	mywndclass.cbSize = sizeof(WNDCLASSEX);
	mywndclass.style = CS_HREDRAW | CS_VREDRAW;
	mywndclass.cbClsExtra = 0;
	mywndclass.cbWndExtra = 0;
	mywndclass.lpfnWndProc = WndProc;
	mywndclass.hInstance = hInsatance;
	mywndclass.hIcon = LoadIcon(hInsatance, MAKEINTRESOURCE(MY_ICON));
	mywndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	mywndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	mywndclass.lpszClassName = szMyAppName;
	mywndclass.lpszMenuName = NULL;
	mywndclass.hIconSm = LoadIcon(hInsatance, MAKEINTRESOURCE(MY_ICON));


	RegisterClassEx(&mywndclass);

	hwnd = CreateWindow(szMyAppName,
		TEXT("Threading"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInsatance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("4th Thread"), TEXT("THREAD"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID Param)
{
	HDC hdc;
	LONG i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
		for (i = 0; i < 4294967295; i++) 
		
		{
			wsprintf(str, TEXT("Thread One -> Increasing : %ld"), i);
			
			TextOut(hdc, 5, 5, str, lstrlen(str));
		}
		ReleaseDC((HWND)Param, hdc);
		return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID Param)
{

	HDC hdc;
	LONG i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 429496729; i >0 ; i--) 
	
	{
		wsprintf(str, TEXT("Thread two -> Decreasing : %ld"), i);

		TextOut(hdc,5,20,str,wcslen(str));
	}
	ReleaseDC((HWND)Param, hdc);
	return 0;
}

