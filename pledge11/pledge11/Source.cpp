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
	TCHAR str [255];



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
	
		//Set the text Colour
			SetTextColor(hdc, RGB(255, 0, 0));
			
			//Draw the actual text
			DrawText(hdc,TEXT("\n\n\n\n India is my country. \n All Indians are my Brothers and Sisters.\n love my country and I am proud of its rich and varied heritage. "),-1,&rc,DT_CENTER | DT_CENTER | DT_VCENTER	);

			//Set the text Colour
			SetTextColor(hdc, RGB(0, 255, 0));

			//Draw the actual text
			DrawText(hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n I shall always strive to be worthy of it.\nI shall give my parents, teachers and all elders respect and treat everyone with courtesy."), -1, &rc, DT_CENTER | DT_CENTER | DT_VCENTER);

			//Set the text Colour
			SetTextColor(hdc, RGB(0, 0, 255));

			//Draw the actual text
			DrawText(hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n To my country and my people, I pledge my devotion.\n In their well being and prosperity alone, lies my happiness. ."), -1, &rc, DT_CENTER | DT_CENTER | DT_VCENTER);


			EndPaint(hwnd, &ps);
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		}
		return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	}
