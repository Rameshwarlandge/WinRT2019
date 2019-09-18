//Headers
#include<windows.h>
#include "resource.h"

#define MYTIMER	101

enum EColour
{
	RED = 1,
	GREEN,
	BLUE,
	CYNE,
	MAGENTA,
	YELLOW,
	WHITE,
	BLACK
};

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("MyWindow"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rc;
	static RECT rc_temp;
	HBRUSH hBrush;
	static UINT UTimer = 100;
	static INT iPaintFlag = RED;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, MYTIMER, UTimer, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		iPaintFlag++;
		if (iPaintFlag > 8)
		{
			iPaintFlag = 0;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		SetTimer(hwnd, MYTIMER, UTimer, NULL);
		break;

	case WM_CHAR:
		switch (wParam) {
		case 'H':
		case 'h':
			UTimer = UTimer + 100;
			break;

		case 'L':
		case 'l':
			UTimer = UTimer - 100;
			break;
		}


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		rc_temp.left = rc.left;
		rc_temp.top = rc.top;
		rc_temp.right = rc.right / 8;
		rc_temp.bottom = rc.bottom;

		switch (iPaintFlag) {
		case RED:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.left;
			rc_temp.top = rc_temp.top;
			rc_temp.right = rc_temp.right;
			rc_temp.bottom = rc_temp.bottom;
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case GREEN:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.left + rc_temp.right;
			rc_temp.right = rc_temp.right + rc_temp.right;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case BLUE:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.right * 2;
			rc_temp.right = rc_temp.right + rc_temp.left;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case CYNE:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.right * 3;
			rc_temp.right = rc_temp.right + rc_temp.left;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case MAGENTA:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.right * 4;
			rc_temp.right = rc_temp.right + rc_temp.left;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case YELLOW:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.right * 5;
			rc_temp.right = rc_temp.right + rc_temp.left;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case WHITE:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.right * 6;
			rc_temp.right = rc_temp.right + rc_temp.left;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		case BLACK:
			KillTimer(hwnd, MYTIMER);
			rc_temp.left = rc_temp.right * 7;
			rc_temp.right = rc_temp.right + rc_temp.left;
			rc_temp.top = rc.top;
			rc_temp.bottom = rc.bottom;
			hBrush = CreateSolidBrush(RGB(100, 50, 100));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc_temp, hBrush);
			SetTimer(hwnd, MYTIMER, UTimer, NULL);
			break;

		default:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}