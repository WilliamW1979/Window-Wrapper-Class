#include "Win.h"

/*

This window wrapper class was created to make creating windows easier and automated.

Written by: William Glenn Ward
Email: WilliamW1979@netscape.net
GamerTag: WillWolf76

*/

map<HWND, cWIN*> cWIN::WindowHandleMap;
deque<HWND> cWIN::WindowList;


cWIN::cWIN()
{
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)StaticWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = sWindowName.c_str();
}

cWIN::cWIN(string WindowTitle)
{
	sWindowName = WindowTitle;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)StaticWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = sWindowName.c_str();
}

LRESULT APIENTRY cWIN::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (WndMessages.find(msg) != WndMessages.end())
		return WndMessages[msg](hWnd, wParam, lParam);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT APIENTRY cWIN::StaticWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	cWIN *temp;
	if (msg == WM_NCCREATE)
	{
		temp = (cWIN*)((CREATESTRUCT*)lParam)->lpCreateParams;
		WindowHandleMap[hWnd] = temp;
		if (temp)
			return temp->WindowProc(hWnd, msg, wParam, lParam);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	if (WindowHandleMap.find(hWnd) != WindowHandleMap.end())
		return WindowHandleMap[hWnd]->WindowProc(hWnd, msg, wParam, lParam);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool cWIN::Create()
{
	RECT rc = {};
	rc.left = rc.right = rc.top = rc.bottom = CW_USEDEFAULT;
	return Create(rc);
}
bool cWIN::Create(int Left, int Top, int Width, int Height)
{
	RECT rc = {};
	rc.left = Left;
	rc.right = Width;
	rc.top = Top;
	rc.bottom = Height;
	return Create(rc);
}

bool cWIN::Create(RECT rc)
{
	hMain = CreateWindow(sWindowName.c_str(), sWindowName.c_str(), dStyle, rc.left, rc.top, rc.right, rc.bottom, hParent, hMenu, GetModuleHandle(NULL), this);
	if (!hMain) return false;
	ShowWindow(hMain, SW_SHOWNORMAL);
	UpdateWindow(hMain);
	if (std::find(WindowList.begin(), WindowList.end(), hMain) == WindowList.end()) WindowList.push_back(hMain);
	return true;
}

bool cWIN::RegisterWindow()
{
	wc.lpszClassName = sWindowName.c_str();
	return RegisterClassEx(&wc);
};

void cWIN::HandleMessages()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		bool bTest = false;
		for (HWND temp : WindowList)
			if(temp != NULL)
				if (IsDialogMessage(temp, &msg))
					bTest = true;
		if (!bTest)
		{
			if (hAccel != NULL)
			{
				if (!TranslateAcceleratorA(hMain, hAccel, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}

void cWIN::SetFrameRate(unsigned int FramesPerSecond)
{
	if (FramesPerSecond == 0)
		SetTimer(hMain, ID_TIMER, 0, NULL);
	else
		SetTimer(hMain, ID_TIMER, (unsigned int)(1000/FramesPerSecond), NULL);
}

cWIN& cWIN::operator=(const cWIN& right)
{
	hMain = right.hMain;
	wc = right.wc;
	sWindowName = right.sWindowName;
	hAccel = right.hAccel;
	WindowHandleMap = right.WindowHandleMap;
	WndMessages = right.WndMessages;
	return *this;
}

bool cWIN::operator==(const cWIN& right)
{
	if (hMain == right.hMain && sWindowName == right.sWindowName && hAccel == right.hAccel && WindowHandleMap == right.WindowHandleMap && WndMessages == right.WndMessages)
		return true;
	return false;
}

bool cWIN::operator!=(const cWIN& right)
{
	return (!(*this == right));
}