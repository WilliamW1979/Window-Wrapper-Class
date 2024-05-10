#pragma once
#ifndef WINDOW_WGW
#define WINDOW_WGW
#define LIBRARYFILENAME_WGW "Win"
#define ID_TIMER 60000
#include <windows.h>
#include <map>
#include <deque>
#include "WindowText.h"

// You don't need the WindowText.h, I added that because I got tired of writing lines and lines of code for getting and setting text to windows.

#if _M_IX86 && _DEBUG
#define ADD_WGW "_32_DEBUG"
#elif _M_IX86
#define ADD_WGW "_32"
#elif _DEBUG
#define ADD_WGW "_DEBUG"
#endif
#ifdef ADD_WGW
#pragma comment(lib, LIBRARYFILENAME_WGW ADD_WGW ".lib")
#else
#pragma comment(lib, LIBRARYFILENAME_WGW ".lib")
#endif


using std::string;
using std::map;
using std::deque;
typedef LRESULT WNDProc;
typedef LRESULT WindowMessage(HWND, WPARAM, LPARAM);
typedef map<UINT, WindowMessage*> WindowMessages;


class cWIN
{
	WNDCLASSEX wc = {};
	HWND hMain = {}, hParent = {};
	DWORD dStyle = WS_OVERLAPPEDWINDOW;
	string sWindowName = "William Glenn Ward's Window Wrapper";
	HACCEL hAccel = {};
	HMENU hMenu = {};
S	static map<HWND, cWIN*> WindowHandleMap;
	static deque<HWND> WindowList;
	WindowMessages WndMessages;

	LRESULT APIENTRY WindowProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT APIENTRY StaticWindowProc(HWND, UINT, WPARAM, LPARAM);

public:
	cWIN();
	cWIN(string WindowTitle);
	cWIN(WNDCLASSEX wndclass) { wc = wndclass; };
	~cWIN() {};

	bool RegisterWindow();
	bool Create();
	bool Create(int Left, int Top, int Width, int Height);
	bool Create(RECT rc);
	void HandleMessages();

	void SetWindowTitle(string Title) { sWindowName = Title; };
	void SetAccel(HACCEL Accel) { hAccel = hAccel; };
	void SetMenu(WORD Menu) { wc.lpszMenuName = MAKEINTRESOURCE(Menu); hMenu = (HMENU)MAKEINTRESOURCE(Menu); };
	void SetIcon(HICON Icon) { wc.hIcon = wc.hIconSm = Icon; };
	void SetCursor(HCURSOR Cursor) { wc.hCursor = Cursor; };
	void SetIcon(WORD IconResource) { wc.hIcon = wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IconResource), IMAGE_ICON, 0, 0, LR_CREATEDIBSECTION); };
	void SetCursor(WORD CursorResource) { wc.hCursor = (HCURSOR)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(CursorResource), IMAGE_CURSOR, 0, 0, LR_CREATEDIBSECTION); };
	void SetBackground(COLORREF Color) { wc.hbrBackground = CreateSolidBrush(Color); };
	void SetBackground(HBRUSH Color) { wc.hbrBackground = Color; };
	void SetWndExtra(int WndExtra) { wc.cbWndExtra = WndExtra; };
	void SetClsExtra(int ClsExtra) { wc.cbClsExtra = ClsExtra; };
	void SetFrameRate(unsigned int FramesPerSecond);
	void SetStyle(DWORD Style) { dStyle = Style; };
	void SetParentWindow(HWND Parent) { hParent = Parent; };
	void SetWindowTimer(unsigned int Milliseconds) { SetTimer(hMain, ID_TIMER, Milliseconds, NULL); };
	void SetWndProc(WNDPROC WndProc) { wc.lpfnWndProc = WndProc; };

	void AddProc(UINT msg, LRESULT(*Proc)(HWND, WPARAM, LPARAM)) { WndMessages[msg] = Proc; };
	void RemoveProc(UINT msg) { WndMessages.erase(msg); };
	void ClearProc() { WndMessages.clear(); };
	const HWND GetHWND() { return hMain; };

	cWIN &operator=(const cWIN &right);
	bool operator==(const cWIN &right);
	bool operator!=(const cWIN &right);
};

#endif