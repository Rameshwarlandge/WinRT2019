//headers
#include<windows.h>
#include"resource.h"

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");

	//code
	//initialozation of WNDCLASSEX
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	//Register above Class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
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

	//message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HGDIOBJ PrevBitmap;
	static HBITMAP hBitMap;
	static HINSTANCE hInstance;
	static HDC cdc;
	BITMAP bitmap;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hBitMap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
		break;


	case WM_PAINT:
		//Get Changing Rectangle
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		cdc = CreateCompatibleDC(hdc);
		PrevBitmap = SelectObject(cdc, hBitMap);
		GetObject(hBitMap, sizeof(bitmap), &bitmap);
		StretchBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, cdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SRCCOPY);
		SelectObject(hdc, PrevBitmap);
		DeleteObject(cdc);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
