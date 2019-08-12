#include<Windows.h>
//#include"color.h"

enum EColor
{
RED=0,
GREEN,
BLUE,
YELLOW,
CYAN,
MAGENTA,
WHITE,
BLACK
};

//Global function Declaration 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable Declaration
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
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//create window
		hwnd = CreateWindow(szAppName,
		TEXT("Color"),
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

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return ((int)msg.wParam);
}
	LRESULT CALLBACK WndProc(HWND hwnd,UINT imsg,WPARAM wParam,LPARAM lParam)
	{

		HDC hdc, cdc;
		PAINTSTRUCT ps;
		RECT rc;
		static int iPainFlag = BLACK;
		HBRUSH hbrush;
		static HBITMAP hBitmap;
		HGDIOBJ PrevBitmap;
		BITMAP bitmap;

		//code
		switch (imsg)
		{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rc);
			cdc = CreateCompatibleDC(hdc);
			PrevBitmap = SelectObject(cdc, hBitmap);

			switch (iPainFlag)
			{
			case RED:
				hbrush = CreateSolidBrush(RGB(255, 0, 0));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;
			case GREEN:
				hbrush = CreateSolidBrush(RGB(0, 255, 0));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;

			case BLUE:
				hbrush = CreateSolidBrush(RGB(0, 0, 255));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;
			case CYAN:
				hbrush = CreateSolidBrush(RGB(0, 255, 255));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;
			case YELLOW:
				hbrush = CreateSolidBrush(RGB(255, 255, 0));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;
			case WHITE:
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;
			case MAGENTA:
				hbrush = CreateSolidBrush(RGB(255, 0, 255));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				break;
			default:GetObject(hBitmap, sizeof(bitmap), &bitmap);
				StretchBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, cdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
				SelectObject(hdc, PrevBitmap);
			}
			DeleteObject(cdc);
			EndPaint(hwnd, &ps);
			break;

		case WM_CHAR:
			switch (wParam)
			{
			case 'R':
			case 'r':
				iPainFlag = RED;
				break;

			case 'G':
			case 'g':
				iPainFlag = GREEN;
				break;
			case 'B':
			case 'b':
				iPainFlag = BLUE;
				break;
			case 'c':
			case 'C':
				iPainFlag = CYAN;
				break;
			case 'Y':
			case 'y':
				iPainFlag = YELLOW;
				break;
			case 'W':
			case 'w':
				iPainFlag = WHITE;
				break;
			case 'm':
			case 'M':
				iPainFlag = MAGENTA;
				break;
			default:
				iPainFlag = BLACK;
				break;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return (DefWindowProc(hwnd, imsg, wParam, lParam));
	}





