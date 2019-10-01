#include<Windows.h>
#include "Resource.h"
#include "MY_MATH.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#pragma comment (lib,"MY_MATH.lib")

//winmain 

int WINAPI WinMain(HINSTANCE hInsatance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX mywndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szMyAppName[] = TEXT("RAM");


	mywndclass.cbSize = sizeof(WNDCLASSEX);
	mywndclass.style = CS_HREDRAW | CS_VREDRAW;
	mywndclass.cbClsExtra = 0;
	mywndclass.cbWndExtra = 0;
	mywndclass.lpfnWndProc = WndProc;
	mywndclass.hInstance = hInsatance;
	mywndclass.hIcon = LoadIcon(hInsatance,MAKEINTRESOURCE(MY_ICON));
	mywndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	mywndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	mywndclass.lpszClassName = szMyAppName;
	mywndclass.lpszMenuName = NULL;
	mywndclass.hIconSm = LoadIcon(hInsatance, MAKEINTRESOURCE(MY_ICON));


	RegisterClassEx(&mywndclass);

	hwnd = CreateWindow(szMyAppName,
		TEXT("DECLSPEC IMPLICIT"),
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
	INT Num = 100, Result = 0;
	WCHAR buffer[255];
	switch (iMsg)
	{
	case WM_CREATE:
		Result = MY_MakeSquare(Num);
		wsprintf(buffer, TEXT("%d"), Result);
		MessageBox(hwnd, buffer, TEXT("SQUARE IS"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}